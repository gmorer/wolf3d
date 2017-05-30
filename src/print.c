/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/30 16:37:42 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	getlen_colorbisbis(t_calc c, t_env *env, int *len, double *place)
{
	double lol;

	if (c.side == 2 || c.side == 3)
		c.temp = (c.map.y - env->pos.y + (1 - c.step.y) * 0.5) / c.raydir.y;
	else
		c.temp = (c.map.x - env->pos.x + (1 - c.step.x) * 0.5) / c.raydir.x;
	*len = (int)(env->surface->w / c.temp);
	//if (*len > env->screen.y)
	//	*len = env->screen.x;
	lol = (c.side >=2 ? env->pos.x + c.temp * c.raydir.x : env->pos.y + c.temp
			* c.raydir.y) * 10;
	lol = lol / 10;
	lol -= (int)lol;
	*place = lol;
	env->calc = c;
	if (env->colormod == 1)
		return (c.side);
	else
		return ((env->map[c.map.x][c.map.y] - 1) % TEXTURE_MAX);
}

static int	getlen_colorbis(t_calc c, t_env *env, int *len, double *place)
{
	while (1)
	{
		if (c.dis.x < c.dis.y)
		{
			c.dis.x += c.delta.x;
			c.map.x += c.step.x;
			if (c.raydir.x < 0)
				c.side = 0;
			else
				c.side = 1;
		}
		else
		{
			c.dis.y += c.delta.y;
			c.map.y += c.step.y;
			if (c.raydir.y < 0)
				c.side = 2;
			else
				c.side = 3;
		}
		if (env->map[c.map.x][c.map.y] > 0)
			break ;
	}
	return (getlen_colorbisbis(c, env, len, place));
}

static	int	getlen_color(int i, t_env *env, int *len, double *place)
{
	t_calc		c;

	c.map.x = (int)env->pos.x;
	c.map.y = (int)env->pos.y;
	c.raydir.x = env->dir.x + env->plan.x * (2 * i / (double)env->surface->w - 1);
	c.raydir.y = env->dir.y + env->plan.y * (2 * i / (double)env->surface->w - 1);
	c.delta.x = sqrt(1 + (c.raydir.y * c.raydir.y) / (c.raydir.x * c.raydir.x));
	c.delta.y = sqrt(1 + (c.raydir.x * c.raydir.x) / (c.raydir.y * c.raydir.y));
	if (c.raydir.x < 0 && (c.step.x = -1))
		c.dis.x = (env->pos.x - c.map.x) * c.delta.x;
	else
	{
		c.step.x = 1;
		c.dis.x = (c.map.x + 1.0 - env->pos.x) * c.delta.x;
	}
	if (c.raydir.y < 0 && (c.step.y = -1))
		c.dis.y = (env->pos.y - c.map.y) * c.delta.y;
	else
	{
		c.step.y = 1;
		c.dis.y = (c.map.y + 1.0 - env->pos.y) * c.delta.y;
	}
	return (getlen_colorbis(c, env, len, place));
}

void			draw_texture(int i, int len, double place, t_env *env)
{
	double	real_place;
	int		temp;
	int		opt;

	opt = 0;
	if (!env->texture[(int)place] || !env->surface)
		return ;
	real_place = env->texture[(int)place]->w * (place - (int)place);
	real_place = real_place / OPT * OPT;
	SDL_BlitScaled(env->texture[(int)place],
			&(SDL_Rect){real_place, OPT - 1, 1, env->texture[(int)place]->h},
			env->surface, &(SDL_Rect){i, (-len / 2 + env->horizon), OPT, len});
}

void			draw_floor(t_env *env, int len, int y, double place)
{
	int tmp;
	int i;
	int len_save;
	int x;
	   tmp = 0;
	   i = 1;
	   len_save = len;
	   while ((x = tmp + (len_save / 2) + env->horizon) < env->surface->h && i < 20)
	   {
		   len += (len / 5) * 2;
		   tmp += len / 7;
		   i++;
	   }
}

void			ft_forline(t_env *env)
{
	int		i;
	int		len;
	t_color	color;
	int		tmp;
	double	place;

	i = 0;
	tmp = env->horizon;
	SDL_FillRect(env->surface, &(SDL_Rect){0, env->horizon, env->surface->w, env->surface->h}, 0xFF008000);
	SDL_FillRect(env->surface, &(SDL_Rect){0, 0, env->surface->w, env->horizon}, 0xFF000000);
	while (i <= env->surface->w)
	{
		tmp = getlen_color(i, env, &len, &place);
	//	SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
	//	SDL_RenderDrawLine(env->renderer, i, 0, i, (-len / 2 + env->horizon));
//		draw_vert_line(env, (t_int_coord){i, 0}, (-len / 2 + env->horizon), (t_color){0, 0, 0, 0});
		if (env->colormod != 2)
		{
			color = colorchoose(tmp, env);
			if (len < env->surface->h && env->shadow == 1)
			{
				color.r = color.r * len / env->surface->h;
				color.g = color.g * len / env->surface->h;
				color.b = color.b * len / env->surface->h;
			}
		//	SDL_FillRect(env->surface, &(SDL_Rect){i, len * -0.5 + env->horizon, i, len * 0.5 + env->horizon},
		//			(size_t)(color.b | color.g << 8 | color.r << 16 | 0xFF << 24));
			draw_vert_line(env, (t_int_coord){i, (-len / 2 + env->horizon)}, len, 
				(t_color){color.r, color.g, color.b, 255});
			//SDL_RenderDrawLine(env->renderer, i, (-len / 2 + env->horizon), i,
			//		(len / 2 + env->horizon));
			//if (i == env->screen.x / 2)
			//draw_floor(env, len, i, place);
		}
		else
		{
			draw_texture(i, len, tmp + place, env);
		}
		i = env->colormod == 2 ? i + OPT : i + 1;
	}
}
