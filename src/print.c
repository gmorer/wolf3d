/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/03 16:21:49 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf3d.h"

static	t_color	*getlen_color(int i, t_env *env, int *len)
{
	t_color *color;
	t_double_coord	raydir;
	t_double_coord	dis;
	t_double_coord	delta;
	t_int_coord		step;
	t_int_coord		map;
	double			temp;
	int		side;

	map.x = (int)env->pos.x;
	map.y = (int)env->pos.y;
	raydir.x = env->dir.x + env->plan.x * (2 * i / (double)SCREEN_X - 1);
	raydir.y = env->dir.y + env->plan.y * (2 * i / (double)SCREEN_X - 1);
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
		*len = (int)(SCREEN_X / temp);
	else
		*len = SCREEN_X;
	color = (t_color*)malloc(sizeof(t_color));
	if(side == 0)
		*color = MAGENTA;
	if(side == 1)
		*color = GREY;
	if(side == 2)
		*color = MAROON;
	if(side == 3)
		*color = PURPLE;
	return (color);
}

static void	ft_print_line(t_env *env, t_color *color, int len, int x)
{
	int y;
	t_color *temp;

	temp = (t_color*)malloc(sizeof(t_color));
	y = 0;
	*temp = BLACK;
	while (y <= -len / 2 + SCREEN_Y / 2)
	{
		draw_pixel(env, x, y, temp);
		y++;
	}
	if(len < SCREEN_Y && env->shadow == 1)
	{
		color->r = color->r * len / SCREEN_Y;
		color->g = color->g * len / SCREEN_Y;
		color->b = color->b * len / SCREEN_Y;
	}
	while (y <= len / 2 + SCREEN_Y / 2)
	{
		draw_pixel(env, x, y++, color);
	}
	*temp = YELLOW;
	while (y <= SCREEN_Y)
	{
		if (env->shadow == 1)
		{
			temp->r = 255 * (y - SCREEN_Y / 2) / (SCREEN_Y / 2);	
			temp->g = 255 * (y - SCREEN_Y / 2) / (SCREEN_Y / 2);	
		}
		draw_pixel(env, x, y++, temp);
	}
	free(temp);
}

void	ft_forline(t_env *env)
{
	int		i;
	int		len;
	t_color	*color;

	i = 0;
	while (i <= SCREEN_X)
	{
		color = getlen_color(i, env, &len);
		ft_print_line(env, color, len, i);
		i++;
		free(color);
	}
}
