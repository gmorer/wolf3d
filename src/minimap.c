/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 17:08:43 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/07 11:23:18 by gmorer           ###   ########.fr       */
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
			count.x = count.x + (env->screen.x - 200);
			count.y = count.y + (env->screen.y - 200);
			draw_pixel(env, count, &(color));
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
								[count.x * env->size.x / 200 + 1] - 1) % 11));
			else
				color = BLACK;
			color.a = 150;
			count.x = count.x + (env->screen.x - 200);
			count.y = count.y + (env->screen.y - 200);
			draw_pixel(env, count, &(color));
			count.x = count.x - (env->screen.x - 200);
			count.y = count.y - (env->screen.y - 200);
			print_player(env, count);
			count.x++;
		}
	return (1);
}
