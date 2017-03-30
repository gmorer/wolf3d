/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/30 02:14:34 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_color	getlen_colorbisbis(t_calc c, t_env *env, int *len)
{
	double lol;

	if (c.side == 2 || c.side == 3)
		c.temp = (c.map.y - env->pos.y + (1 - c.step.y) / 2) / c.raydir.y;
	else
		c.temp = (c.map.x - env->pos.x + (1 - c.step.x) / 2) / c.raydir.x;
	*len = (int)(env->screen.x / c.temp);
	lol = (c.side >=2 ? env->pos.x + c.temp * c.raydir.x : env->pos.y + c.temp * c.raydir.y) * 10;
	//lol -= floor((lol));
	lol = lol / 10;
	lol -= (int)lol;
	lol = fabs(1 - 2 * lol);
	printf("%f\n", lol);
	*len += lol * 10;
	if (env->colormod == 1)
	{
		if (c.side == 0)
			c.color = MAGENTA;
		if (c.side == 1)
			c.color = GREY;
		if (c.side == 2)
			c.color = MAROON;
		if (c.side == 3)
			c.color = PURPLE;
	}
	else
		c.color = colorchoose((env->map[c.map.x][c.map.y] - 1) % TEXTURE_MAX);
	return (c.color);
}

static t_color	getlen_colorbis(t_calc c, t_env *env, int *len)
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
	return (getlen_colorbisbis(c, env, len));
}

static	t_color	getlen_color(int i, t_env *env, int *len)
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
	return (getlen_colorbis(c, env, len));
}

void			ft_forline(t_env *env)
{
	int		i;
	int		len;
	t_color	color;
	int		tmp;

	i = 0;
	if (env->shadow == 1)
	{
		tmp = env->horizon;
		while (tmp <= env->screen.y)
		{
			SDL_SetRenderDrawColor(env->renderer, 0, 128 * (tmp - env->horizon)
					/ ((env->screen.y - env->horizon)), 0, 255);
			SDL_RenderDrawLine(env->renderer, 0, tmp, env->screen.x, tmp);
			tmp++;
		}
	}
	while (i <= env->screen.x)
	{
		color = getlen_color(i, env, &len);
		if (len < env->screen.y && env->shadow == 1)
		{
			color.r = color.r * len / env->screen.y;
			color.g = color.g * len / env->screen.y;
			color.b = color.b * len / env->screen.y;
		}
		SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(env->renderer, i, 0, i, (-len / 2 + env->horizon));
		SDL_SetRenderDrawColor(env->renderer, color.r, color.g, color.b, 255);
		SDL_RenderDrawLine(env->renderer, i, (-len / 2 + env->horizon), i,
				(len / 2 + env->horizon));
		if (env->shadow == 0)
		{
			SDL_SetRenderDrawColor(env->renderer, 0, 128, 0, 255);
			SDL_RenderDrawLine(env->renderer, i, (len / 2 + env->horizon), i,
					env->screen.y);
		}
		i++;
	}
}
