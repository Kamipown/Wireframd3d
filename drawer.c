/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:32:04 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:32:08 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	link_horizontal(t_env *e, t_seg *seg, char *buf)
{
	int		x;
	int		y;
	int		dx;
	int		dy;

	dx = seg->x2 - seg->x1;
	dy = seg->y2 - seg->y1;
	if (seg->x1 < seg->x2)
	{
		x = seg->x1;
		while (x < seg->x2)
		{
			y = seg->y1 + dy * (x - seg->x1) / dx;
			draw_pixel(buf, x, y, get_color(seg, e->map));
			++x;
		}
	}
}

static void	link_vertical(t_env *e, t_seg *seg, char *buf)
{
	int		x;
	int		ymin;
	int		ymax;
	int		dx;
	int		dy;

	dx = seg->x2 - seg->x1;
	dy = seg->y2 - seg->y1;
	if (seg->y1 < seg->y2)
	{
		ymin = seg->y1;
		ymax = seg->y2;
	}
	else
	{
		ymin = seg->y2;
		ymax = seg->y1;
	}
	while (ymin < ymax)
	{
		x = seg->x1 + dx * (ymin - seg->y1) / dy;
		draw_pixel(buf, x, ymin, get_color(seg, e->map));
		++ymin;
	}
}

static void	link_points(t_env *e, t_seg *seg, char *buf)
{
	int		temp;

	if (seg->x1 > seg->x2)
	{
		temp = seg->x1;
		seg->x1 = seg->x2;
		seg->x2 = temp;
		temp = seg->y1;
		seg->y1 = seg->y2;
		seg->y2 = temp;
	}
	if (abs(seg->x2 - seg->x1) >= abs(seg->y2 - seg->y1))
		link_horizontal(e, seg, buf);
	else
		link_vertical(e, seg, buf);
}

static void	segment(t_env *e, int i, int j, int s)
{
	t_seg	seg;

	seg.x1 = e->map->lines[i].points[j].x;
	seg.y1 = e->map->lines[i].points[j].y;
	seg.z1 = e->map->lines[i].points[j].z;
	seg.c1 = e->map->lines[i].points[j].color;
	if (s)
	{
		seg.x2 = e->map->lines[i].points[j + 1].x;
		seg.y2 = e->map->lines[i].points[j + 1].y;
		seg.z2 = e->map->lines[i].points[j + 1].z;
		seg.c2 = e->map->lines[i].points[j + 1].color;
	}
	else
	{
		seg.x2 = e->map->lines[i + 1].points[j].x;
		seg.y2 = e->map->lines[i + 1].points[j].y;
		seg.z2 = e->map->lines[i + 1].points[j].z;
		seg.c2 = e->map->lines[i + 1].points[j].color;
	}
	link_points(e, &seg, e->img->buf);
}

void		draw_map(t_env *e)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < e->map->len)
	{
		while (j < e->map->lines[i].len)
		{
			if (j < e->map->lines[i].len - 1)
				segment(e, i, j, 1);
			if (i < e->map->len - 1)
				if (j < e->map->lines[i + 1].len)
					segment(e, i, j, 0);
			++j;
		}
		j = 0;
		++i;
	}
	draw_cross(e->img->buf);
}
