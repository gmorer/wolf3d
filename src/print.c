/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/27 13:49:09 by gmorer           ###   ########.fr       */
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
	int		hit;

	side = 0;
	hit = 0;
	map.x = (int)env->pos.x;
	map.y = (int)env->pos.y;
	raydir.x = env->dir.x + env->plan.x * (2 * i / (double)SCREEN_X - 1);
	raydir.y = env->dir.y + env->plan.y * (2 * i / (double)SCREEN_X - 1);
	delta.x = sqrt(1 + (raydir.y * raydir.y) / (raydir.x * raydir.x));
	delta.y = sqrt(1 + (raydir.x * raydir.x) / (raydir.y * raydir.y));
	if (raydir.x < 0)
	{
		step.x = -1;
		dis.x = (map.x - env->pos.x) * delta.x;
	}
	else
	{
		step.x = 1;	
		dis.x = (env->pos.x + 1.0 - map.x) * delta.x;
	}
	if (raydir.y < 0)
	{
		step.y = -1;
		dis.y = (map.y - env->pos.x) * delta.y;
	}
	else
	{
		step.y = 1;	
		dis.y = (env->pos.y + 1.0 - map.y) * delta.y;
	}
	while(hit == 0)
	{
		if (dis.x < dis.y)
		{
			dis.x += delta.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			dis.y += delta.y;
			map.y += step.y;
			side = 1;
		}
		if (env->map[map.x][map.y] > 0)
			hit = 1;
	}
	if(side)
		temp =(map.y - env->pos.y + (1 - step.y) / 2) / raydir.y;
	else
		temp = (map.x - env->pos.x + (1 - step.x) / 2) / raydir.x;
	if(*len != 0)
		*len = (int)(SCREEN_X / temp);
	color = (t_color*)malloc(sizeof(t_color));
	if(side)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
	return (color);
}

static void	ft_print_line(t_env *env, t_color *color, int len, int x)
{
	int y;
	t_color *temp;

	temp = (t_color*)malloc(sizeof(t_color));
	temp->r = 255;
	temp->g = 0;
	temp->b = 0;
	y = 0;
	while (y <= -len / 2 + SCREEN_Y / 2)
	{
		draw_pixel(env, x, y, temp);
		y++;
	}
	while (y <= len / 2 + SCREEN_Y / 2)
	{
		draw_pixel(env, x, y++, color);
	}
	temp->r = 0; 
	temp->g = 255; 
	temp->b = 0; 
	while (y <= SCREEN_Y)
	{
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
