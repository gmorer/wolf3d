/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 02:05:28 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/30 15:32:04 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*surface_from_bmp(char *path, t_env *env)
{
	SDL_Surface *surface;
	SDL_Surface	*surface2;

	surface = SDL_LoadBMP(path);
	if (!surface)
	{
		ft_putstr("error during texture loading : ");
		ft_putendl(SDL_GetError());
		return (NULL);
	}
	surface2 = SDL_CreateRGBSurface(0, TEXTURE_DIM, TEXTURE_DIM, 32, 0, 0, 0, 0);
	if (SDL_BlitScaled(surface, NULL, surface2, NULL) < 0)
	{
		printf("error for %s\n", path);
		SDL_GetError();
		SDL_FreeSurface(surface2);
		return (surface);
	}
	if (surface)
		SDL_FreeSurface(surface);
	return (surface2);
}

void		load_texture(t_env *env)
{
	bzero(env->texture, 10);
	env->texture[0] = surface_from_bmp("./res/stone.bmp", env);
	env->texture[1] = surface_from_bmp("./res/42.bmp", env);
	env->texture[2] = surface_from_bmp("./res/bomb.bmp", env);
	env->texture[3] = surface_from_bmp("./res/dirt.bmp", env);
	env->texture[4] = surface_from_bmp("./res/golum.bmp", env);
	env->texture[5] = surface_from_bmp("./res/matrix.bmp", env);
	env->texture[6] = surface_from_bmp("./res/sponge.bmp", env);
	env->texture[7] = surface_from_bmp("./res/tnt.bmp", env);
	env->texture[8] = surface_from_bmp("./res/tux.bmp", env);
	env->texture[9] = surface_from_bmp("./res/wood.bmp", env);
}
