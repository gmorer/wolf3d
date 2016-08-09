/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/03 16:23:01 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "input.h"
#include <stdio.h>

static int	ft_exit(t_env *env)
{
	(void)env;
	mlx_destroy_image(env->mlx, env->img);
	exit(0);
}

static int			ft_key_unpress(int key, t_env *env)
{
	if (key == UP)
		env->key.move = 0;
	if (key == DOWN)
		env->key.move = 0;
	if (key == RIGHT)
		env->key.turn = 0;
	if (key == LEFT)
		env->key.turn = 0;
	return (0);
}

static int			ft_key_press(int key, t_env *env)
{
	if (key == UP)
		env->key.move = 2;
	if (key == DOWN)
		env->key.move = -1;
	if (key == RIGHT)
		env->key.turn = -1;
	if (key == LEFT)
		env->key.turn = 1;
	if (key == ESC)
		ft_exit(env);
	if (key == SPACE && env->shadow == 0)
		env->shadow = 1;
	else if (key == SPACE && env->shadow == 1)
		env->shadow = 0;
	return (0);
}

static t_env	*ft_init(char *argv)
{
	t_env *env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	/*
	env->size.x = 0;
	env->plan.x = 0;
	env->plan.y = 0.5;
	env->dir.x = -1;
	env->dir.y = 0;
	env->key.turn = 0;
	env->key.move = 0;
	env->shadow = 0;
	env->oldtime = clock();
	*/
	*env = (t_env){NULL, NULL, NULL, NULL, clock(), (t_key){0, 0}, (t_double_coord){-1, 0}, (t_double_coord){0, 0}, (t_double_coord){0, 0.5},(t_int_coord){0, 0}, 0, NULL, 0, 0, 0};
	if (ft_parser(env, argv) == 0)
		return (NULL);
	if (!(env->mlx = mlx_init()))
		return (NULL);
	if (!(env->window = mlx_new_window(env->mlx, SCREEN_X, SCREEN_Y, "wolf3d")))
		return (NULL);
	if (!(env->img = mlx_new_image(env->mlx, SCREEN_X, SCREEN_Y)))
		return (NULL);
	return (env);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (0);
	if (!(env = ft_init(argv[1])))
		ft_putendl("parsing error");
	if (!env)
		return (1);
	ft_putendl("test");
	mlx_hook(env->window, 3, 2, ft_key_unpress, env);
	mlx_hook(env->window, 2, 1, ft_key_press, env);
	mlx_hook(env->window, 17, (1L << 17), ft_exit, env);
	mlx_loop_hook(env->mlx, ft_image_put, env);//case 2
	mlx_loop(env->mlx);
	return (0);
}
