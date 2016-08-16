/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:29:34 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:32:27 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_image(char *buf)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			draw_pixel(buf, i, j, 0x000000);
			++j;
		}
		++i;
	}
}

static void	draw_image(t_env *e)
{
	e->img->buf = mlx_get_data_addr(
		e->img->data,
		&e->img->bpp,
		&e->img->size,
		&e->img->endian);
	clear_image(e->img->buf);
	draw_map(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->data, 0, 0);
}

void		draw_pixel(char *buf, int x, int y, int color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		x *= 4;
		y *= 4;
		buf[(x++) + (y * WIDTH)] = color;
		buf[(x++) + (y * WIDTH)] = color >> 8;
		buf[(x) + (y * WIDTH)] = color >> 16;
	}
}

int			expose_hook(t_env *e)
{
	draw_image(e);
	return (0);
}

int			key_hook(int k, t_env *e)
{
	if (k == ESCAPE)
		exit(0);
	else if (k == TOP || k == BOTTOM || k == LEFT || k == RIGHT)
		translate_map(e, k);
	else if (k == ROTX1 || k == ROTX2
			|| k == ROTY1 || k == ROTY2
			|| k == ROTZ1 || k == ROTZ2)
		rotate_map(e, k);
	else if (k == SCALE1 || k == SCALE2
			|| k == SCALE3 || k == SCALE4)
		scale_map(e, k);
	else if (k == PAL)
		change_color(e->map);
	else
		return (0);
	mlx_clear_window(e->mlx, e->win);
	draw_image(e);
	return (0);
}
