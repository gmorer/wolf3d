/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 17:08:43 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/30 16:23:35 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	print_player(t_env *env, t_int_coord count)
{
	t_color color;

	if ((count.y * env->size.y / 200 + 1) == (int)env->pos.x)
		if ((count.x * env->size.x / 200 + 1) == (int)env->pos.y)
		{
			color = BLUE;
			color.a = 150;
			count.x = count.x + (env->surface->w - 200);
			count.y = count.y + (env->surface->h - 200);
			draw_pixel(env, count, color);
		}
	return (1);
}

int			ft_minimap(t_env *env)
{
	t_int_coord count;
	t_color		color;

	count.y = 0;
	while (!(count.x = 0) && ++count.y < 200)
		while (count.x < 200)
		{
			if (env->map[count.y * env->size.y / 200 + 1][count.x *
					env->size.x / 200 + 1] != 0)
				color = (env->colormod == 1 ? WHITE : colorchoose(
							(env->map[count.y * env->size.y / 200 + 1]
								[count.x * env->size.x / 200 + 1] - 1) % 11, env));
			else
				color = BLACK;
			color.a = 150;
			count.x = count.x + (env->surface->w - 200);
			count.y = count.y + (env->surface->h - 200);
			draw_pixel(env, count, color);
			count.x = count.x - (env->surface->w - 200);
			count.y = count.y - (env->surface->h - 200);
			print_player(env, count);
			count.x++;
		}
	return (1);
}
