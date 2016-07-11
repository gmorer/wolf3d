/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 13:15:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/11 18:06:59 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	t_color	*getlen_color(int i, t_env *env, int *len)
{
	t_color *color;

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
	ft_putendl("test1");
	while (y <= SCREEN_Y / 3)
	{
		draw_pixel(env, x, y, temp);
		y++;
	}
	ft_putendl("test2");
	while (y <= SCREEN_Y / 3 * 2)
	{
		draw_pixel(env, x, y++, color);
	}
	ft_putendl("test3");
	temp->r = 178; 
	temp->g = 34; 
	temp->b = 34; 
	while (y <= SCREEN_Y)
	{
		draw_pixel(env, x, y++, temp);
	}
	ft_putendl("test4");
}

void	ft_forline(t_env *env)
{
	int i;
	int	len;
	t_color *color;

	ft_putendl("lol1");
	i = 0;
	while (i <= SCREEN_X)
	{
		color = getlen_color(i, env, &len);
		ft_putendl("lol1.5");
		ft_print_line(env, color, len, i);
		i++;
		free(color);
	}
	ft_putendl("lol2");

}
