/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/19 18:03:56 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	getlen_colorbisbis(t_calc c, t_env *env, int *len, double *place)
{
	double lol;

	if (c.side == 2 || c.side == 3)
		c.temp = (c.map.y - env->pos.y + (1 - c.step.y) / 2) / c.raydir.y;
	else
		c.temp = (c.map.x - env->pos.x + (1 - c.step.x) / 2) / c.raydir.x;
	*len = (int)(env->screen.x / c.temp);
	lol = (c.side >=2 ? env->pos.x + c.temp * c.raydir.x : env->pos.y + c.temp * c.raydir.y) * 10;
	lol = lol / 10;
	lol -= (int)lol;
	*place = lol;
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
	c.raydir.x = env->dir.x + env->plan.x * (2 * i / (double)env->screen.x - 1);
	c.raydir.y = env->dir.y + env->plan.y * (2 * i / (double)env->screen.x - 1);
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
	real_place = env->texture[(int)place]->coord.x * (place - (int)place);
	SDL_RenderCopy(env->renderer, env->texture[(int)place]->texture,
			&(SDL_Rect){real_place, OPT - 1, 1, env->texture[(int)place]->coord.y},
			&(SDL_Rect){i, (-len / 2 + env->horizon), OPT, len});
	if (env->shadow == 1)
	{
		if (len > env->screen.y)
			temp = 0;
		else
		{
			temp = len * 255 / env->screen.y;
			temp = abs(255 - temp);
			temp = temp - 255;
		}
		SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, temp);
		while (opt < OPT)
		{
			SDL_RenderDrawLine(env->renderer, i + opt, (-len / 2 + env->horizon), i + opt,
						(len / 2 + env->horizon));
			opt++;
		}
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
	while (tmp <= env->screen.y)
	{
		SDL_SetRenderDrawColor(env->renderer, 0, env->shadow == 1 ? (128 * (tmp - env->horizon)
					/ ((env->screen.y - env->horizon))) : 128 , 0, 255);
		SDL_RenderDrawLine(env->renderer, 0, tmp, env->screen.x, tmp);
		tmp++;
	}
	while (i <= env->screen.x)
	{
		tmp = getlen_color(i, env, &len, &place);
		SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(env->renderer, i, 0, i, (-len / 2 + env->horizon));
		if (env->colormod != 2)
		{
			color = colorchoose(tmp, env);
			if (len < env->screen.y && env->shadow == 1)
			{
				color.r = color.r * len / env->screen.y;
				color.g = color.g * len / env->screen.y;
				color.b = color.b * len / env->screen.y;
			}
			SDL_SetRenderDrawColor(env->renderer, color.r, color.g, color.b, 255);
			SDL_RenderDrawLine(env->renderer, i, (-len / 2 + env->horizon), i,
					(len / 2 + env->horizon));
		}
		else
		{
			draw_texture(i, len, tmp + place, env);
		}
		i = env->colormod == 2 ? i + OPT : i + 1;
	}
}
