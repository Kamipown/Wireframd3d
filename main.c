/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdelobbe <pdelobbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 01:25:48 by pdelobbe          #+#    #+#             */
/*   Updated: 2015/04/14 01:48:38 by pdelobbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check(int argc)
{
	if (argc < 2)
	{
		ft_putendl("usage : ./fdf file");
		exit(0);
	}
	if (WIDTH < 1 || HEIGHT < 1)
	{
		ft_putendl("Error : Bad screen size.");
		exit(0);
	}
}

int			main(int argc, char *argv[])
{
	t_env	e;

	check(argc);
	init(&e, argv[1]);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_hook(e.win, 2, (1L << 0), key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
