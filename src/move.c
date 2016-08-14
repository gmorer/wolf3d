/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/03 15:49:37 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_move( t_env *env)
{
	double	tmp;

	if (env->key.move != 0 && env->map[(int)(env->pos.x + env->dir.x * 0.05 * env->key.move)]
			[(int)(env->pos.y + env->dir.y * 0.05 * env->key.move)] == 0)
	{
		env->pos.x += env->dir.x * 0.05 * env->key.move;
		env->pos.y += env->dir.y * 0.05 * env->key.move;
	}
	if (env->key.turn == 1 || env->key.turn == -1)
	{
		tmp = env->dir.x;
		env->dir.x = env->dir.x * cos(0.05 * env->key.turn) - env->dir.y * sin(0.05 * env->key.turn);
		env->dir.y = tmp * sin(0.05 * env->key.turn) + env->dir.y * cos(0.05 * env->key.turn);
		tmp = env->plan.x;
		env->plan.x = env->plan.x * cos(0.05 * env->key.turn) - env->plan.y * sin(0.05 * env->key.turn);
		env->plan.y = tmp * sin(0.05 * env->key.turn) + env->plan.y * cos(0.05 * env->key.turn);
	}
	return (0);
}

int			ft_image_put(t_env *env)
{
	ft_forline(env);
	ft_minimap(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
	mlx_put_image_to_window(env->mlx, env->window, env->minimap, SCREEN_X - 200, SCREEN_Y - 200);
	ft_move(env);
	return (1);
}
