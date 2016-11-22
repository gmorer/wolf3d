/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/22 11:00:05 by gmorer           ###   ########.fr       */
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
			
	if (env->key.move != 0 && env->map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * 0.05 *
					env->key.move)] == 0)
		env->pos.y += env->dir.y * 0.05 * env->key.move;
	if (env->key.turn == 1 || env->key.turn == -1)
	{/*
		tmp = env->dir.x;
		env->dir.x = env->dir.x * cos(0.05 * env->key.turn) - env->dir.y *
		sin(0.05 * env->key.turn);
		env->dir.y = tmp * sin(0.05 * env->key.turn) + env->dir.y * cos(0.05
	  * env->key.turn);
	  tmp = env->plan.x;
	  env->plan.x = env->plan.x * cos(0.05 * env->key.turn) - env->plan.y *
	  sin(0.05 * env->key.turn);
	  env->plan.y = tmp * sin(0.05 * env->key.turn) + env->plan.y * cos(0.05
	  * env->key.turn);*/
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
/*
   static int	print_fps(int fps, t_env *env)
   {
   SDL_Color	white;
   SDL_Surface	*fps_surface;
   SDL_Texture	*texture;

   white = {255, 255, 255};
   fps_surface = TTF_RenderText_Solid(env->font, ft_itoa(fps), white);
   texture = SDL_CreatTextureFromSurface(env->renderer, fpa_surface);
   }
   */
int			ft_image_put(t_env *env)
{
	clock_t	time;
	double	n;
	int		fps;

	time = clock();
	ft_forline(env);
	ft_minimap(env);/*
					   mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
					   mlx_put_image_to_window(env->mlx, env->window, env->minimap,
					   env->screen.x - 200, env->screen.y - 200);*/

	ft_move(env);
	n = clock() - time;
	fps = (int)(1 / (n / CLOCKS_PER_SEC));
	if (fps > 0)
	{
		//		print_fps(fps, env);
	}
	return (1);
}
