/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:02:31 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/30 16:22:45 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "color.h"

static int		outside_window(t_int_coord coord, t_env *env)
{
	if (!(coord.x > env->surface->w - 1 || coord.x < 0 || coord.y >
				env->surface->h - 1 || coord.y < 0))
		return (1);
	else
		return (0);
}

void			draw_pixel(t_env *env, t_int_coord cor, t_color color)
{
	unsigned long clr;
	if (outside_window(cor, env) == 0)
		return ;
	clr = color.b | (color.g << 8) | (color.r << 16) | (color.a << 24);
	*((unsigned *)(env->surface->pixels + cor.y * env->surface->pitch + cor.x *
				    env->surface->format->BytesPerPixel)) = clr;
}

void			draw_vert_line(t_env *env, t_int_coord cor, int len, t_color color)
{
	int		i;

	i = 0;
	if (cor.y < 0)
	{
		len += cor.y;
		cor.y = 0;
	}
	if (cor.y > env->surface->w)
		return ;
	while (i < len)
	{
		draw_pixel(env, (t_int_coord){cor.x, cor.y + i}, color);
		if (cor.y + i > env->surface->h)
			return ;
		i++;
	}

}

void			draw_hori_line(t_env *env, t_int_coord cor, int len, t_color color)
{
	int		i;

	i = 0;
	while (i < len)
	{
		draw_pixel(env, (t_int_coord){cor.y + i, cor.x}, color);
		i++;
	}
}
