/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:02:31 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/27 12:46:38 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		outside_window(int x, int y)
{
	if (!(x > SCREEN_X - 1 || x < 0 || y > SCREEN_Y - 1 || y < 0))
		return (1);
	else
		return (0);
}

void			draw_pixel(t_env *e, int x, int y, t_color *color)
{/*
	ft_putendl("je pose un pixel1");
	ft_putnbr(x);
	ft_putendl("");
	ft_putnbr(y);
	ft_putendl("");
	ft_putnbr(color->r);
	ft_putendl("");
	ft_putnbr(color->g);
	ft_putendl("");
	ft_putnbr(color->b);
	ft_putendl("");
*/
	if (outside_window(x, y) == 0)
		return ;
	e->pixel_img = mlx_get_data_addr(e->img, &(e->bpp), &(e->s_line), &(e->ed));
	e->pixel_img[x * e->bpp / 8 + y * e->s_line] = (char)color->r;
	e->pixel_img[x * e->bpp / 8 + 1 + y * e->s_line] = (char)color->g;
	e->pixel_img[x * e->bpp / 8 + 2 + y * e->s_line] = (char)color->b;
//	ft_putendl("je pose un pixel2");
}
/*
int				ft_print(t_env *env)
{
	(void)env;
	return (0);
}*/
