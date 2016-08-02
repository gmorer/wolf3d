/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/02 14:54:44 by gmorer           ###   ########.fr       */
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
		env->key.up = 0;
	if (key == DOWN)
		env->key.down = 0;
	if (key == RIGHT)
		env->key.turn = 0;
	if (key == LEFT)
		env->key.turn = 0;
	return (0);
}

static int			ft_key_press(int key, t_env *env)
{
	if (key == UP)
		env->key.up = 1;
	if (key == DOWN)
		env->key.down = 1;
	if (key == RIGHT)
		env->key.turn = -1;
	if (key == LEFT)
		env->key.turn = 1;
	if (key == ESC)
		ft_exit(env);
	ft_image_put(env);
	return (0);
}

static t_env	*ft_init(char *argv)
{
	t_env *env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->size.x = 0;
	env->pos.x = 3;
	env->pos.y = 3;
	env->plan.x = 0;
	env->plan.y = 0.66;
	env->dir.x = -1;
	env->dir.y = 0;
	env->key.up = 0;
	env->key.down = 0;
	env->key.turn = 0;
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
		return (1);
	mlx_expose_hook(env->window, ft_image_put, env);
	mlx_hook(env->window, 3, 2, ft_key_unpress, env);
	mlx_hook(env->window, 2, 1, ft_key_press, env);
	mlx_hook(env->window, 17, (1L << 17), ft_exit, env);
	//mlx_loop_hook(env->window, ft_image_put, env);
	mlx_loop(env->mlx);
	return (0);
}
