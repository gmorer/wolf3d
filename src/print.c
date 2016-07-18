/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/18 16:41:20 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf3d.h"

static	t_color	*getlen_color(int i, t_env *env, int *len)
{
	t_color *color;
	double	dirx;
	double	diry;
	int		carrex;
	int		carrey;
	double	disx;
	double	disy;
	int		mapx;
	int		mapy;
	int		side;

	mapx = (int)env->posx;
	mapy = (int)env->posy;
	dirx = env->anglex + env->planx * (2 * i / (double)SCREEN_X - 1);
	diry = env->angley + env->plany * (2 * i / (double)SCREEN_X - 1);
	if (dirx < 0)
	{
		carrex = -1;
		disx = (env->posx - mapx) * sqrt(1 + (diry * diry) / (dirx * dirx));
	}
	else
	{
		carrex = 1;	
		disx = (mapx + 1.0 - env->posx) * sqrt(1 + (diry * diry) / (dirx * dirx));
	}
	if (diry < 0)
	{
		carrey = -1;
		disy = (env->posy - mapx) * sqrt(1 + (dirx * dirx) / (diry * diry));
	}
	else
	{
		carrey = 1;	
		disy = (mapx + 1.0 - env->posy) * sqrt(1 + (dirx * dirx) / (diry * diry));
	}
	while(1)
	{
		if (disx < disy)
		{
			disx += sqrt(1 + (diry * diry) / (dirx * dirx));
			mapx += carrex;
			side = 0;
		}
		else
		{
			disy += sqrt(1 + (dirx * dirx) / (diry * diry));
			mapy += carrey;
			side = 0;
		}
		if (env->map[mapx][mapy] > 0)
			break;
	}
	if(side)
		*len = (int)((mapy - env->posy + (1 - carrey) / 2) / diry);
	else
		*len = (int)((mapx - env->posx + (1 - carrex) / 2) / dirx);/*
	ft_putnbr(carrey);
	ft_putchar('\n');
	ft_putnbr(carrex);
	ft_putchar('\n');
	ft_putnbr(dirx);
	ft_putchar('\n');
	ft_putnbr(diry);
	ft_putchar('\n');*/
	ft_putnbr(*len);
	ft_putchar('\n');
	color = (t_color*)malloc(sizeof(t_color));
	color->r = 0;
	color->g = 0;
	color->b = 0;
	return (color);
}

static void	ft_print_line(t_env *env, t_color *color, int len, int x)
{
	int y;
	t_color *temp;

	temp = (t_color*)malloc(sizeof(t_color));
	temp->r = 0;
	temp->g = 0;
	temp->b = 255;
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
	temp->r = 178; 
	temp->g = 34; 
	temp->b = 34; 
	while (y <= SCREEN_Y)
	{
		draw_pixel(env, x, y++, temp);
	}
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
