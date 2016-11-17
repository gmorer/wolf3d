/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/17 10:54:39 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "input.h"
#include <stdio.h>

static int			ft_key_unpress(int key, t_env *env)
{
	if (key == KEY_W)
		env->key.move = 0;
	if (key == KEY_S)
		env->key.move = 0;
	if (key == KEY_D)
		env->key.turn = 0;
	if (key == KEY_A)
		env->key.turn = 0;
	return (0);
}

static int			ft_key_press(int key, t_env *env)
{
	if (key == KEY_W)
		env->key.move = 2;
	if (key == KEY_S)
		env->key.move = -1;
	if (key == KEY_D)
		env->key.turn = -1;
	if (key == KEY_A)
		env->key.turn = 1;
	if (key == ESC)
		ft_exit(env);
	if (key == SPACE && env->shadow == 0)
		env->shadow = 1;
	else if (key == SPACE && env->shadow == 1)
		env->shadow = 0;
	if (key == SHIFT && env->colormod == 0)
		env->colormod = 1;
	else if (key == SHIFT && env->colormod == 1)
		env->colormod = 0;/*
	if (key == KEY_W && env->horizon < env->screen.y)
		env->horizon += 5;
	if (key == KEY_S && env->horizon > 0)
		env->horizon -= 5;*/
	return (0);
}

static t_env		*ft_initenv(char *argv)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	*env = (t_env){NULL, NULL, NULL, NULL, NULL, (t_key){0, 0},
		(t_double_coord){-1, 0}, (t_double_coord){0, 0},
		(t_double_coord){0, 0.5},
		(t_int_coord){SCREEN_X, SCREEN_Y}, (t_int_coord){0, 0}, SCREEN_Y / 2,
		0, 0, NULL, 0, 0, 0};
	if (ft_parser(env, argv) == 0)
		return (NULL);
	return (env);
}

static int			ft_mouse(int x, int y, t_env *env)
{
	if (y > 0 && y < env->screen.y)
		env->horizon = ft_abs(y - env->screen.y);
	return (0);
}

static int			ft_initmlx(t_env **env)
{
	if (!((*env)->mlx = mlx_init()))
		return (0);
	if (!((*env)->window = mlx_new_window((*env)->mlx, (*env)->screen.x,
					(*env)->screen.y, "wolf3d")))
		return (0);
	if (!((*env)->img = mlx_new_image((*env)->mlx, (*env)->screen.x,
					(*env)->screen.y)))
		return (0);
	if (!((*env)->minimap = mlx_new_image((*env)->mlx, 200, 200)))
		return (0);
	return (1);
}

int					main(int argc, char **argv)
{
	t_env	*env;

	if (argc < 2 || argc > 3)
		return (0);
	if (!(env = ft_initenv(argv[1])))
		ft_putendl("parsing error");
	if (!env)
		return (1);
	if (argc == 3)
		if (getsize(&env, argv[2]) == 0)
			return (1);
	if (!env)
		return (1);
	if (ft_initmlx(&env) == 0)
		return (1);
	mlx_hook(env->window, 3, 2, ft_key_unpress, env);
	mlx_hook(env->window, 2, 1, ft_key_press, env);
	mlx_hook(env->window, 17, (1L << 17), ft_exit, env);
	mlx_hook(env->window, 6, (1L << 6), ft_mouse, env);
	mlx_loop_hook(env->mlx, ft_image_put, env);
	mlx_loop(env->mlx);
	return (0);
}
