/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/16 13:45:34 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf3d.h"

static	t_color	getlen_color(int i, t_env *env, int *len)
{
	t_color color;
	t_double_coord	raydir;
	t_double_coord	dis;
	t_double_coord	delta;
	t_int_coord		step;
	t_int_coord		map;
	double			temp;
	int		side;

	map.x = (int)env->pos.x;
	map.y = (int)env->pos.y;
	raydir.x = env->dir.x + env->plan.x * (2 * i / (double)env->screen.x - 1);
	raydir.y = env->dir.y + env->plan.y * (2 * i / (double)env->screen.x - 1);
	delta.x = sqrt(1 + (raydir.y * raydir.y) / (raydir.x * raydir.x));
	delta.y = sqrt(1 + (raydir.x * raydir.x) / (raydir.y * raydir.y));
	if (raydir.x < 0)
	{
		step.x = -1;
		dis.x = (env->pos.x - map.x) * delta.x;
	}
	else
	{
		step.x = 1;	
		dis.x = (map.x + 1.0 - env->pos.x) * delta.x;
	}
	if (raydir.y < 0)
	{
		step.y = -1;
		dis.y = (env->pos.y - map.y) * delta.y;
	}
	else
	{
		step.y = 1;	
		dis.y = (map.y + 1.0 - env->pos.y) * delta.y;
	}
	while(1)
	{
		if (dis.x < dis.y)
		{
			dis.x += delta.x;
			map.x += step.x;
			if (raydir.x < 0)
				side = 0;
			else
				side = 1;
		}
		else
		{
			dis.y += delta.y;
			map.y += step.y;
			if (raydir.y < 0)
				side = 2;
			else
				side = 3;
		}
		if (env->map[map.x][map.y] > 0 )
			break;
	}
	if(side == 2 || side == 3)
		temp = (map.y - env->pos.y + (1 - step.y) / 2) / raydir.y;
	else
		temp = (map.x - env->pos.x + (1 - step.x) / 2) / raydir.x;
	if(temp > 1)	
		*len = (int)(env->screen.x / temp);
	else
		*len = env->screen.x;
	if (env->colormod == 1)
	{
		if(side == 0)
			color = MAGENTA;
		if(side == 1)
			color = GREY;
		if(side == 2)
			color = MAROON;
		if(side == 3)
			color = PURPLE;
	}
	else
		//color = env->colortab[env->map[map.x][map.y] % 9 + 1];
		color = GREY;
	return (color);
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
