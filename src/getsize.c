/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 17:55:04 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/16 18:26:44 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	*getstart(char *c, int len)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		result[i] = c[i];
		i++;
	}
	result[len] = '\0';
	ft_putendl(result);
	return (result);
}

static int	sizecheck(t_env **env)
{
	if ((*env)->screen.x < 500 ||
		(*env)->screen.x > 1920 ||
		(*env)->screen.y < 500 ||
		(*env)->screen.y > 1080)
	{
		(*env)->screen.x = SCREEN_X;
		(*env)->screen.y = SCREEN_Y;
		return (1);
	}
	return (0);
}


int		getsize(t_env **env, char *argc)
{
	int	i;
	int count;
	int len;

	ft_putendl(argc);
	count = 0;
	i = 0;
	while (argc[i])
	{
		if (argc[i] == 'x')
		{
			count++;
			len = i;
		}
		else if(ft_isdigit(argc[i]) != 1)
			return (0);
		i++;
	}
	if (count != 1)
		return (0);
	(*env)->screen.x = ft_atoi(getstart(argc, len));
	(*env)->screen.y = ft_atoi(argc + len + 1);
	sizecheck(env);
	return (1);
}
