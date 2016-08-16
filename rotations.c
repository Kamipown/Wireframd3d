/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:32:35 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:32:37 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_z(t_map *map, int dir, int i, int j)
{
	double	beta;
	double	t;

	beta = (dir == ROTZ1) ? ROT : -ROT;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x -= map->cx;
			map->lines[i].points[j].y -= map->cy;
			t = map->lines[i].points[j].x;
			map->lines[i].points[j].x =
				map->lines[i].points[j].x * cos(beta) +
				map->lines[i].points[j].y * -sin(beta);
			map->lines[i].points[j].y =
				t * sin(beta) +
				map->lines[i].points[j].y * cos(beta);
			map->lines[i].points[j].x += map->cx;
			map->lines[i].points[j].y += map->cy;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	rotate_y(t_map *map, int dir, int i, int j)
{
	double	beta;
	double	t;

	beta = (dir == ROTY1) ? ROT : -ROT;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x -= map->cx;
			map->lines[i].points[j].y -= map->cy;
			t = map->lines[i].points[j].x;
			map->lines[i].points[j].x =
				map->lines[i].points[j].x * cos(beta) +
				map->lines[i].points[j].z * sin(beta);
			map->lines[i].points[j].z =
				t * -sin(beta)
				+ map->lines[i].points[j].z * cos(beta);
			map->lines[i].points[j].x += map->cx;
			map->lines[i].points[j].y += map->cy;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	rotate_x(t_map *map, int dir, int i, int j)
{
	double	beta;
	double	t;

	beta = (dir == ROTX1) ? ROT : -ROT;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x -= map->cx;
			map->lines[i].points[j].y -= map->cy;
			t = map->lines[i].points[j].y;
			map->lines[i].points[j].y =
				map->lines[i].points[j].y * cos(beta) +
				map->lines[i].points[j].z * -sin(beta);
			map->lines[i].points[j].z =
				t * sin(beta) +
				map->lines[i].points[j].z * cos(beta);
			map->lines[i].points[j].x += map->cx;
			map->lines[i].points[j].y += map->cy;
			++j;
		}
		j = 0;
		++i;
	}
}

void		rotate_map(t_env *e, int dir)
{
	if (dir == ROTX1 || dir == ROTX2)
		rotate_x(e->map, dir, 0, 0);
	else if (dir == ROTY1 || dir == ROTY2)
		rotate_y(e->map, dir, 0, 0);
	else if (dir == ROTZ1 || dir == ROTZ2)
		rotate_z(e->map, dir, 0, 0);
}
