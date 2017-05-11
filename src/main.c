/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 11:37:05 by gmorer            #+#    #+#             */
/*   Updated: 2017/05/11 14:09:20 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "input.h"
#include <stdio.h>

static int			ft_key_unpress(int key, t_env *env)
{
	if (key == SDLK_w)
		env->key.move = 0;
	if (key == SDLK_s)
		env->key.move = 0;
	if (key == SDLK_d)
		env->key.turn = 0;
	if (key == SDLK_a)
		env->key.turn = 0;
	return (0);
}

static int			ft_key_press(int key, t_env *env)
{
	if (key == SDLK_w)
		env->key.move = 2;
	if (key == SDLK_s)
		env->key.move = -1;
	if (key == SDLK_d)
		env->key.turn = -1;
	if (key == SDLK_a)
		env->key.turn = 1;
	if (key == SDLK_ESCAPE)
		ft_exit(env);
	if (key == SDLK_SPACE && env->shadow == 0)
		env->shadow = 1;
	else if (key == SDLK_SPACE && env->shadow == 1)
		env->shadow = 0;
	if (key == SDLK_LSHIFT && env->colormod != 2)
		env->colormod++;
	else if (key == SDLK_LSHIFT && env->colormod == 2)
		env->colormod = 0;
	if (key == SDLK_RSHIFT && env->mouse == 1)
	{
		SDL_SetRelativeMouseMode(0);
		env->mouse = 0;
	}
	else if (key == SDLK_RSHIFT && env->mouse == 0)
	{
		SDL_SetRelativeMouseMode(1);
		env->mouse = 1;
	}
	return (0);
}

static t_env		*ft_initenv(char *argv)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	*env = (t_env){NULL, NULL, NULL, (t_key){0, 0},
		(t_double_coord){-1, 0}, (t_double_coord){0, 0},
		(t_double_coord){0, 0.5},
		(t_int_coord){SCREEN_X, SCREEN_Y}, (t_int_coord){0, 0}, SCREEN_Y / 2,
		0, 0, 0, 1};
	if (ft_parser(env, argv) == 0)
		return (NULL);
	return (env);
}

static int			ft_initsdl(t_env **env)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	(*env)->window = SDL_CreateWindow("wolf3d",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			(*env)->screen.x, (*env)->screen.y, SDL_WINDOW_RESIZABLE);
	(*env)->renderer = SDL_CreateRenderer((*env)->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRelativeMouseMode(1);
	SDL_SetRenderDrawBlendMode((*env)->renderer, SDL_BLENDMODE_BLEND);
	(*env)->font = TTF_OpenFont("res/DejaVuSansMono.ttf", 38);
	return (1);
}

static int			ft_mouse(SDL_Event *event, t_env *env)
{
	double	tmp;

	tmp = 0;
	if (event->motion.yrel < 0 && env->horizon -
			event->motion.yrel < env->screen.y)
		env->horizon -= event->motion.yrel;
	if (event->motion.yrel > 0 && env->horizon - event->motion.yrel > 0)
		env->horizon -= event->motion.yrel;
	tmp = env->dir.x;
	env->dir.x = env->dir.x * cos(event->motion.xrel * -0.001) -
		env->dir.y * sin(event->motion.xrel * -0.001);
	env->dir.y = tmp * sin(event->motion.xrel * -0.001) + env->dir.y *
		cos(event->motion.xrel * -0.001);
	tmp = env->plan.x;
	env->plan.x = env->plan.x * cos(event->motion.xrel * -0.001) -
		env->plan.y * sin(event->motion.xrel * -0.001);
	env->plan.y = tmp * sin(event->motion.xrel * -0.001) + env->plan.y *
		cos(event->motion.xrel * -0.001);
	return (1);
}

int					main(int argc, char **argv)
{
	t_env		*env;
	SDL_Event	event;

	if (argc != 2)
	{
		ft_putendl_fd("usage: wolf3d [map]", STDERR_FILENO);
		return (0);
	}
	if (!(env = ft_initenv(argv[1])))
		ft_putendl("parsing error");
	if (!env)
		return (1);
	if (argc == 3)
		if (getsize(&env, argv[2]) == 0)
			return (1);
	if (!env)
		return (1);
	if (ft_initsdl(&env) == 0)
		return (1);
	load_texture(env);
	while (42)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				ft_exit(env);
			if (event.type == SDL_KEYDOWN)
				ft_key_press(event.key.keysym.sym, env);
			if (event.type == SDL_KEYUP)
				ft_key_unpress(event.key.keysym.sym, env);
			if (event.type == SDL_WINDOWEVENT && event.window.event
					== SDL_WINDOWEVENT_RESIZED)
			{
				env->screen.x = event.window.data1;
				env->screen.y = event.window.data2;
			}
			if (event.type == SDL_MOUSEMOTION)
				ft_mouse(&event, env);
		}
		SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 0);
		SDL_RenderClear(env->renderer);
		ft_image_put(env);
		SDL_RenderPresent(env->renderer);
	}
	return (0);
}
