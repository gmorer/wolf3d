/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 12:56:52 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/21 13:18:26 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_color	colorchoose(int i)
{
	if (i == 0)
		return (WHITE);
	if (i == 1)
		return (RED);
	if (i == 2)
		return (BLUE);
	if (i == 3)
		return (YELLOW);
	if (i == 4)
		return (CYAN);
	if (i == 5)
		return (MAGENTA);
	if (i == 6)
		return (GREEN);
	if (i == 7)
		return (GREY);
	if (i == 8)
		return (MAROON);
	if (i == 9)
		return (PURPLE);
	if (i == 10)
		return (SILVER);
	return (BLACK);
}

int		ft_exit(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size.y + 2)
		free(env->map[i++]);
	free(env->map);
	SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->window);
	SDL_Quit();
	free(env);
	exit(0);
}
