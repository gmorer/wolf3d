/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/18 16:39:20 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	if (key == UP && env->map[(int)(env->posx + env->anglex * 0.1)][(int)(env->posy + env->angley * 0.1)] == 0)
	{
		env->posx += env->anglex * 0.1;
		env->posy += env->angley * 0.1;
		printf("x : %f\ny : %f\n", env->posx, env->posy);
	}
//	else if (key == DOWN)
	else if (key == LEFT)
	 {
		 tmp = env->anglex;
		 env->anglex = env->anglex * cos(-0.05) - env->angley * sin(-0.05);
		 env->angley = tmp * sin(-0.05) + env->angley * cos(-0.05);
		 tmp = env->planx;
		 env->planx = env->planx * cos(-0.05) - env->plany * sin(-0.05);
		 env->planx = tmp * sin(-0.05) + env->plany * cos(-0.05);
		 //ft_putendl("yolo");
	 }
	else if (key == RIGHT)
	{
		 tmp = env->anglex;
		 env->anglex = env->anglex * cos(0.05) - env->angley * sin(0.05);
		 env->angley = tmp * sin(0.05) + env->angley * cos(0.05);
		 tmp = env->planx;
		 env->planx = env->planx * cos(0.05) - env->plany * sin(0.05);
		 env->planx = tmp * sin(0.05) + env->plany * cos(0.05);
	}
//	else if (key == KEY_W)
//	else if (key == KEY_S)
//	else if (key == KEY_A)
//	else if (key == KEY_D)
	else if (key == ESC)
		exit(0);
	else
		return (0);
	ft_image_put(env);
	return (0);
}

static int	ft_putmapint(t_env *env)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < env->sizey)
	{
		x = 0;
		while(x < env->sizex)
		{
			ft_putnbr(env->map[y][x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		y++;
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
	env->sizex = 0;
	env->posx = 3;
	env->posy = 3;
	env->planx = 0;
	env->plany = 1;
	env->anglex = -1;
	env->angley = 0;
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
