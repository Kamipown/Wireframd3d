/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 08:32:19 by pdelobbe          #+#    #+#             */
/*   Updated: 2016/04/20 08:32:21 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# include "libft/includes/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

# define GAP 10
# define ROT M_PI / 32
# define STEP 10
# define ZOOM 2

# define SCALE1 69
# define SCALE2 78
# define SCALE3 89
# define SCALE4 91

# define PAL 92

# define ESCAPE 53

# define TOP 126
# define RIGHT 124
# define BOTTOM 125
# define LEFT 123

# define ROTX1 86
# define ROTX2 83
# define ROTY1 87
# define ROTY2 84
# define ROTZ1 88
# define ROTZ2 85

typedef struct		s_seg
{
	int				x1;
	int				y1;
	int				z1;
	double			c1;
	int				x2;
	int				y2;
	int				z2;
	double			c2;
}					t_seg;

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	double			color;
}					t_point;

typedef struct		s_line
{
	t_point			*points;
	int				len;
}					t_line;

typedef struct		s_map
{
	t_line			*lines;
	int				len;
	int				width;
	int				height;
	int				cx;
	int				cy;
	int				maxz;
	int				minz;
	int				pal;
}					t_map;

typedef struct		s_img
{
	char			*buf;
	void			*data;
	int				bpp;
	int				size;
	int				endian;
}					t_img;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_map			*map;
}					t_env;

void				init(t_env *e, char *filename);

int					expose_hook(t_env *e);
int					key_hook(int k, t_env *e);

void				draw_pixel(char *buf, int x, int y, int color);
void				draw_map(t_env *e);

void				parse_file(t_map *map, char *filename);
int					get_color(t_seg *seg, t_map *map);
void				set_colors(t_map *map);
void				change_color(t_map *map);
void				draw_cross(char *buf);
void				rotate_map(t_env *e, int dir);
void				scale_map(t_env *e, int dir);
void				translate_map(t_env *e, int dir);

#endif
