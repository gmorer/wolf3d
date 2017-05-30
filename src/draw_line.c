/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 12:03:51 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/30 16:26:17 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_draw_second_line(t_int_coord coord, t_env *env, int len,
		t_color color)
{
	t_color		temp;

	while (coord.y <= len / 2 + env->horizon)
	{
		draw_pixel(env, coord, color);
		coord.y++;
	}
	temp = GREEN;
	while (coord.y <= env->surface->h)
	{
		if (env->shadow == 1 && coord.y >= 0)
		{
			temp.g = 128 * (coord.y - env->horizon) /
				((env->surface->h - env->horizon));
		}
		draw_pixel(env, coord, temp);
		coord.y++;
	}
}

void		ft_print_line(t_env *env, t_color color, int len, int x)
{
	t_color		temp;
	t_int_coord	coord;

	coord.x = x;
	coord.y = 0;
	temp = BLACK;
	while (coord.y <= -len / 2 + env->horizon)
	{
		draw_pixel(env, coord, temp);
		coord.y++;
	}
	if (len < env->surface->h && env->shadow == 1)
	{
		color.r = color.r * len / env->surface->h;
		color.g = color.g * len / env->surface->h;
		color.b = color.b * len / env->surface->h;
	}
	ft_draw_second_line(coord, env, len, color);
}
