/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/30 10:25:51 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

SDL_Surface		*load_txt(char *text, SDL_Color color, t_env *env)
{
	return (TTF_RenderText_Solid(env->font, text, color));
}


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
	clock_t			time;
	double			n;
	int				fps;
	char			*str;
	SDL_Surface*    text;

	time = clock();
	ft_forline(env);
	ft_minimap(env);
	ft_move(env);
	n = clock() - time;
	fps = (int)(1 / (n / CLOCKS_PER_SEC));
	if (fps > 0)
	{
		str = ft_itoa(fps);
		text = load_txt(str, (SDL_Color){255, 255, 255, 0}, env);
		SDL_BlitSurface(text, NULL, env->surface, &(SDL_Rect){0, 0, 80, 40});
		free(str);
	}
	return (1);
}
