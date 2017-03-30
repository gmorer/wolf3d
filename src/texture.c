/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 02:05:28 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/30 05:39:51 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_texture	*texture_from_bmp(char *path, t_env *env)
{
	t_texture	*rslt;
	SDL_Texture	*texture;
	SDL_Surface *surface;
	rslt = (t_texture*)malloc(sizeof(t_texture));
	surface = SDL_LoadBMP(path);
	if (!surface || !rslt)
	{
		ft_putstr("error during texture loading : ");
		ft_putendl(SDL_GetError());
		return (NULL);
	}
	rslt->coord.x = surface->h;
	rslt->coord.y = surface->w;
	texture = SDL_CreateTextureFromSurface(env->renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		ft_putendl("error during texture loading");
		ft_putendl(SDL_GetError());
		return (NULL);
	}
	rslt->texture = texture;
	return (rslt);
}

void		load_texture(t_env *env)
{
	bzero(env->texture, 10);
	env->texture[0] = texture_from_bmp("./res/stone.bmp", env);
	env->texture[1] = texture_from_bmp("./res/42.bmp", env);
	env->texture[2] = texture_from_bmp("./res/bomb.bmp", env);
	env->texture[3] = texture_from_bmp("./res/dirt.bmp", env);
	env->texture[4] = texture_from_bmp("./res/golum.bmp", env);
	env->texture[5] = texture_from_bmp("./res/matrix.bmp", env);
	env->texture[6] = texture_from_bmp("./res/sponge.bmp", env);
	env->texture[7] = texture_from_bmp("./res/tnt.bmp", env);
	env->texture[8] = texture_from_bmp("./res/tux.bmp", env);
	env->texture[9] = texture_from_bmp("./res/wood.bmp", env);
}
