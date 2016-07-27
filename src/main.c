/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/27 14:31:19 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int			ft_putmapint(t_env *env);

static int	ft_image_put(t_env *env)
{
	env->img = mlx_new_image(env->mlx, SCREEN_X, SCREEN_Y);
	ft_forline(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
	mlx_destroy_image(env->mlx, env->img);
	return (0);
}

static int	ft_key(int key, t_env *env)
{
	double	tmp;
	
	(void)key;
//	if (key == SHIFT)
//	else if (key == CTR && env->zoom > 1)
	if (key == UP && env->map[(int)(env->pos.x + env->dir.x * 0.1)]
			[(int)(env->pos.y + env->dir.y * 0.1)] == 0)
	{
		env->pos.x += env->dir.x * 0.1;
		env->pos.y += env->dir.y * 0.1;
		printf("x : %f\ny : %f\n", env->pos.x, env->pos.y);
	}
//	else if (key == DOWN)
	else if (key == LEFT)
	 {
		 tmp = env->dir.x;
		 env->dir.x = env->dir.x * cos(0.05) - env->dir.y * sin(0.05);
		 env->dir.y = tmp * sin(0.05) + env->dir.y * cos(0.05);
		 tmp = env->plan.x;
		 env->plan.x = env->plan.x * cos(0.05) - env->plan.y * sin(0.05);
		 env->plan.x = tmp * sin(0.05) + env->plan.y * cos(0.05);
	 }
	else if (key == RIGHT)
	{
		tmp = env->dir.x;
		env->dir.x = env->dir.x * cos(-0.05) - env->dir.y * sin(-0.05);
		env->dir.y = tmp * sin(-0.05) + env->dir.y * cos(-0.05);
		tmp = env->plan.x;
		env->plan.x = env->plan.x * cos(-0.05) - env->plan.y * sin(-0.05);
		env->plan.x = tmp * sin(-0.05) + env->plan.y * cos(-0.05);
	}
//	else if (key == KEY_W)
//	else if (key == KEY_S)
//	else if (key == KEY_A)
//	else if (key == KEY_D)
	else if (key == ESC)
		exit(0);
	else
		return (0);
	ft_putmapint(env);
	ft_image_put(env);
	return (0);
}

int			ft_putmapint(t_env *env)
{
	t_int_coord	i;

	i.x = 0;
	i.y = 0;
	while (i.y < env->size.y)
	{
		i.x = 0;
		while(i.x < env->size.x)
		{
			if (i.x == (int)(env->pos.x) && i.y == (int)(env->pos.y))
				ft_putchar('p');
			else
				ft_putnbr(env->map[i.y][i.x]);
			ft_putchar(' ');
			i.x++;
		}
		ft_putchar('\n');
		i.y++;
	}
	return (0);
}

static int	ft_exit(t_env *e)
{
	(void)e;
	exit(0);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (0);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (1);
	env->size.x = 0;
	env->pos.x = 3;
	env->pos.y = 3;
	env->plan.x = 0;
	env->plan.y = 0.66;
	env->dir.x = -1;
	env->dir.y = 0;
	ft_parser(env, argv[1]);
	ft_putmapint(env);
	env->mlx = mlx_init();
	env->window = mlx_new_window(env->mlx, SCREEN_X, SCREEN_Y, "wolf3d");
	mlx_expose_hook(env->window, ft_image_put, env);
	mlx_hook(env->window, 2, 3, ft_key, env);
	mlx_hook(env->window, 17, (1L << 17), ft_exit, env);
	mlx_loop(env->mlx);
	return (0);
}
