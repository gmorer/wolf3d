/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/07 11:19:22 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

static int	ft_move(t_env *env)
{
	double	tmp;

	if (env->key.move != 0 && env->map[(int)(env->pos.x + env->dir.x * 0.05 *
				env->key.move)][(int)env->pos.y] == 0)
		env->pos.x += env->dir.x * 0.05 * env->key.move;
	if (env->key.move != 0 && env->map[(int)env->pos.x][(int)(env->pos.y +
				env->dir.y * 0.05 *
					env->key.move)] == 0)
		env->pos.y += env->dir.y * 0.05 * env->key.move;
	if (env->key.turn == 1 || env->key.turn == -1)
	{
		if (env->map[(int)(env->pos.x - env->plan.x *
					0.1 * env->key.turn)][(int)(env->pos.y)] == 0)
		{
			env->pos.x -= env->plan.x * 0.1 * env->key.turn;
		}
		if (env->map[(int)(env->pos.x)][(int)(env->pos.y -
					env->plan.y * 0.1 * env->key.turn)] == 0)
		{
			env->pos.y -= env->plan.y * 0.1 * env->key.turn;
		}
	}
	return (0);
}

int			ft_image_put(t_env *env)
{
	ft_forline(env);
	ft_minimap(env);
	ft_move(env);
	return (1);
}
