/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:25:49 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:25:51 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

static void	set_center(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map->len)
	{
		while (j < map->lines[i].len)
		{
			map->lines[i].points[j].x += WIDTH / 2 - map->width / 2;
			map->lines[i].points[j].y += HEIGHT / 2 - map->height / 2;
			++j;
		}
		j = 0;
		++i;
	}
	map->cx = WIDTH / 2;
	map->cy = HEIGHT / 2;
}

static void	parse_point(t_map *map, int index_l, int index_p, int z)
{
	map->lines[index_l].points[index_p].x = index_p * GAP;
	map->lines[index_l].points[index_p].y = index_l * GAP;
	if (z * 2 > map->maxz)
		map->maxz = z * 2;
	else if (z * 2 < map->minz)
		map->minz = z * 2;
	map->lines[index_l].points[index_p].z = z * 2;
}

static void	parse_line(t_map *map, char *str, int index_l)
{
	int		index_p;
	char	**points;

	index_p = 0;
	while (str[index_p])
	{
		if (!ft_isdigit(str[index_p]) && str[index_p] != '-')
			str[index_p] = ' ';
		++index_p;
	}
	points = ft_strsplit(str, ' ');
	index_p = 0;
	while (points[index_p])
		++index_p;
	if ((index_p * GAP - GAP) > map->width)
		map->width = index_p * GAP - GAP;
	map->lines[index_l].len = index_p;
	map->lines[index_l].points = (t_point *)malloc(sizeof(t_point) * index_p);
	index_p = 0;
	while (points[index_p])
	{
		parse_point(map, index_l, index_p, ft_atoi(points[index_p]));
		++index_p;
	}
}

static void	init_map(t_map *map, char *filename)
{
	int		fd;
	int		nl;
	int		len;
	char	c;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr(filename);
		ft_putendl(": No such file or directory");
		exit(0);
	}
	nl = 0;
	len = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			++nl;
		++len;
	}
	if (c != '\n' && len > 0)
		++nl;
	close(fd);
	map->len = nl;
	map->height = nl * GAP - GAP;
	map->lines = (t_line *)malloc(sizeof(t_line) * nl);
}

void		parse_file(t_map *map, char *filename)
{
	int		fd;
	int		index_l;
	char	*str;
	int		n;

	map->width = 0;
	map->height = 0;
	map->maxz = 0;
	map->minz = 0;
	init_map(map, filename);
	if ((fd = open(filename, O_RDONLY)) != -1)
	{
		index_l = 0;
		while ((n = get_next_line(fd, &str)) == 1)
		{
			parse_line(map, str, index_l);
			++index_l;
		}
	}
	close(fd);
	set_center(map);
	set_colors(map);
}
