/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:02:31 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/25 17:11:53 by gmorer           ###   ########.fr       */
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

void			draw_pixel(t_env *e, void *img, t_int_coord cor, t_color *color)
{
	if (outside_window(cor, e) == 0)
		return ;
	e->pixel_img = mlx_get_data_addr(img, &(e->bpp), &(e->s_line), &(e->ed));
	e->pixel_img[cor.x * e->bpp / 8 + 0 + cor.y * e->s_line] = (char)color->b;
	e->pixel_img[cor.x * e->bpp / 8 + 1 + cor.y * e->s_line] = (char)color->g;
	e->pixel_img[cor.x * e->bpp / 8 + 2 + cor.y * e->s_line] = (char)color->r;
	e->pixel_img[cor.x * e->bpp / 8 + 3 + cor.y * e->s_line] = (char)color->a;
}
