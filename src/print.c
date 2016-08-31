/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/25 13:01:05 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf3d.h"

static t_color getlen_colorbisbis(t_calc c, t_env *env, int *len)
{
	if(c.side == 2 || c.side == 3)
		c.temp = (c.map.y - env->pos.y + (1 - c.step.y) / 2) / c.raydir.y;
	else
		c.temp = (c.map.x - env->pos.x + (1 - c.step.x) / 2) / c.raydir.x;
	if(c.temp > 1)	
		*len = (int)(env->screen.x / c.temp);
	else
		*len = env->screen.x;
	if (env->colormod == 1)
	{
		if(c.side == 0)
			c.color = MAGENTA;
		if(c.side == 1)
			c.color = GREY;
		if(c.side == 2)
			c.color = MAROON;
		if(c.side == 3)
			c.color = PURPLE;
	}
	else
		c.color = colorchoose((env->map[c.map.x][c.map.y] - 1) % 11);
	return (c.color);
}

static t_color getlen_colorbis(t_calc c, t_env *env, int *len)
{
	while(1)
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
		if (env->map[c.map.x][c.map.y] > 0 )
			break;
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
	if (c.raydir.x < 0)
	{
		c.step.x = -1;
		c.dis.x = (env->pos.x - c.map.x) * c.delta.x;
	}
	else
	{
		c.step.x = 1;	
		c.dis.x = (c.map.x + 1.0 - env->pos.x) * c.delta.x;
	}
	if (c.raydir.y < 0)
	{
		c.step.y = -1;
		c.dis.y = (env->pos.y - c.map.y) * c.delta.y;
	}
	else
	{
		c.step.y = 1;	
		c.dis.y = (c.map.y + 1.0 - env->pos.y) * c.delta.y;
	}
	return (getlen_colorbis(c, env, len));
}

static void	ft_print_line(t_env *env, t_color color, int len, int x)
{
	t_color *temp;
	t_int_coord coord;

	coord.x = x;
	coord.y = 0;
	temp = (t_color*)malloc(sizeof(t_color));
	*temp = BLACK;
	while (coord.y <= -len / 2 + env->screen.y / 2)
	{
		draw_pixel(env, env->img, coord, temp);
		coord.y++;
	}
	if(len < env->screen.y && env->shadow == 1)
	{
		color.r = color.r * len / env->screen.y;
		color.g = color.g * len / env->screen.y;
		color.b = color.b * len / env->screen.y;
	}
	while (coord.y <= len / 2 + env->screen.y / 2)
	{
		draw_pixel(env, env->img, coord, &color);
		coord.y++;
	}
	*temp = GREEN;
	while (coord.y <= env->screen.y)
	{
		if (env->shadow == 1)
		{
			temp->g = 128 * (coord.y - env->screen.y / 2) / (env->screen.y / 2);	
		}
		draw_pixel(env, env->img, coord, temp);
		coord.y++;
	}
	free(temp);
}

void	ft_forline(t_env *env)
{
	int		i;
	int		len;
	t_color	color;

	i = 0;
	while (i <= env->screen.x)
	{
		color = getlen_color(i, env, &len);
		ft_print_line(env, color, len, i);
		i++;
	}
}
