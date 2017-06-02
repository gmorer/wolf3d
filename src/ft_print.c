/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:02:31 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/01 10:37:30 by gmorer           ###   ########.fr       */
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

SDL_Surface		*background(t_env *env)
{
	SDL_Surface		*rslt;
	int				i;

	rslt = SDL_CreateRGBSurface(0, env->screen.x, env->screen.y * 2, 32, 0, 0, 0, 0);
	SDL_FillRect(rslt, &(SDL_Rect){0, 0, env->screen.x, env->screen.y}, 0xFF000000);
	i = env->screen.y;
	while (i < env->screen.y * 2)
	{
		SDL_FillRect(rslt, &(SDL_Rect){0, i, env->screen.x, i}, (size_t)(0x00 | 0x00 << 16 |
				((int)(128 * ((i - env->screen.y)) / ((env->screen.y - env->horizon)))) << 8 |
				0xFF << 24));
		i++;
	}
	return (rslt);
}
