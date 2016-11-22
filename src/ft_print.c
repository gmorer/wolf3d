/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:02:31 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/22 12:02:54 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "color.h"

static int		outside_window(t_int_coord coord, t_env *env)
{
	if (!(coord.x > env->screen.x - 1 || coord.x < 0 || coord.y >
				env->screen.y - 1 || coord.y < 0))
		return (1);
	else
		return (0);
}

void			draw_pixel(t_env *e, t_int_coord cor, t_color *color)
{
	if (outside_window(cor, e) == 0)
		return ;
	SDL_SetRenderDrawColor(e->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(e->renderer, cor.x, cor.y);
}
