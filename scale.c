/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:32:48 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:32:49 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom_in(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x -= map->cx;
			map->lines[i].points[j].y -= map->cy;
			map->lines[i].points[j].x *= ZOOM;
			map->lines[i].points[j].y *= ZOOM;
			map->lines[i].points[j].x += map->cx;
			map->lines[i].points[j].y += map->cy;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	zoom_out(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x -= map->cx;
			map->lines[i].points[j].y -= map->cy;
			map->lines[i].points[j].x /= ZOOM;
			map->lines[i].points[j].y /= ZOOM;
			map->lines[i].points[j].x += map->cx;
			map->lines[i].points[j].y += map->cy;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	up_z(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].z *= 50;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	down_z(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].z /= 50;
			++j;
		}
		j = 0;
		++i;
	}
}

void		scale_map(t_env *e, int dir)
{
	if (dir == SCALE1)
		zoom_in(e->map);
	else if (dir == SCALE2)
		zoom_out(e->map);
	else if (dir == SCALE3)
		up_z(e->map);
	else if (dir == SCALE4)
		down_z(e->map);
}
