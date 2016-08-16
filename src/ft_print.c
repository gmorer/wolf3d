/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:02:31 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/16 13:55:36 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "color.h"

static int		outside_window(t_int_coord coord)
{
	if (!(coord.x > SCREEN_X - 1 || coord.x < 0 || coord.y > SCREEN_Y - 1 || coord.y < 0))
		return (1);
	else
		return (0);
}

void			draw_pixel(t_env *e, void *img, t_int_coord coord, t_color *color)
{
	if (outside_window(coord) == 0)
		return ;
	e->pixel_img = mlx_get_data_addr(img, &(e->bpp), &(e->s_line), &(e->ed));
	e->pixel_img[coord.x * e->bpp / 8 + 0 + coord.y * e->s_line] = (char)color->b;
	e->pixel_img[coord.x * e->bpp / 8 + 1 + coord.y * e->s_line] = (char)color->g;
	e->pixel_img[coord.x * e->bpp / 8 + 2 + coord.y * e->s_line] = (char)color->r;
	e->pixel_img[coord.x * e->bpp / 8 + 3 + coord.y * e->s_line] = (char)color->a;
}
