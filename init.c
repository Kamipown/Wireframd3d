/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:33:11 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:33:12 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(t_env *e, char *filename)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "Fdf");
	e->img = (t_img *)malloc(sizeof(t_img));
	e->img->data = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->map = (t_map *)malloc(sizeof(t_map));
	parse_file(e->map, filename);
}
