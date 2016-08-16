/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:32:43 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:32:44 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translate_top(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].y -= STEP;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	translate_bottom(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].y += STEP;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	translate_left(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x -= STEP;
			++j;
		}
		j = 0;
		++i;
	}
}

static void	translate_right(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x += STEP;
			++j;
		}
		j = 0;
		++i;
	}
}

void		translate_map(t_env *e, int dir)
{
	if (dir == TOP)
		translate_top(e->map);
	else if (dir == BOTTOM)
		translate_bottom(e->map);
	else if (dir == LEFT)
		translate_left(e->map);
	else if (dir == RIGHT)
		translate_right(e->map);
}
