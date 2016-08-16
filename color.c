/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:27:04 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:27:05 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_cross(char *buf)
{
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2 - 1, 0xffffff);
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2 - 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2 - 3, 0xffffff);
	draw_pixel(buf, WIDTH / 2 + 1, HEIGHT / 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2 + 2, HEIGHT / 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2 + 3, HEIGHT / 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2 + 1, 0xffffff);
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2 + 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2, HEIGHT / 2 + 3, 0xffffff);
	draw_pixel(buf, WIDTH / 2 - 1, HEIGHT / 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2 - 2, HEIGHT / 2, 0xffffff);
	draw_pixel(buf, WIDTH / 2 - 3, HEIGHT / 2, 0xffffff);
}

void	change_color(t_map *map)
{
	if (map->pal < 3)
		++map->pal;
	else
		map->pal = 1;
}

int		get_color(t_seg *seg, t_map *map)
{
	int		ch;
	int		cl;

	cl = 0xff;
	ch = 0xff;
	if (map->pal == 1)
	{
		ch = 0xff * ((seg->c1 + seg->c2) / 2) / 100;
		cl = 0xff - ch;
		return ((ch << 16) + cl);
	}
	else if (map->pal == 2)
	{
		ch = 0xff * ((seg->c1 + seg->c2) / 2) / 100;
		cl = 0xff - ch;
		return ((ch << 8) + cl);
	}
	else
	{
		ch = 0xff * ((seg->c1 + seg->c2) / 2) / 100;
		cl = 0xff - ch;
		return ((ch << 16) + (cl << 8));
	}
}

void	set_colors(t_map *map)
{
	int		i;
	int		j;
	double	var;

	i = 0;
	j = 0;
	var = map->maxz - map->minz;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			if (map->minz < 0)
				map->lines[i].points[j].color =
				(map->lines[i].points[j].z - map->minz) * (100 / var);
			else
				map->lines[i].points[j].color =
				map->lines[i].points[j].z * (100 / var);
			++j;
		}
		j = 0;
		++i;
	}
	map->pal = 1;
}
