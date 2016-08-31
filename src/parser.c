/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 10:56:43 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/31 12:16:24 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_strstrlen(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_remp(t_env *env, char *str)
{
	int			fd;
	char		*line;
	t_int_coord i;
	char		**temp;

	i.x = 1;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		i.y = 0;
		temp = ft_strsplit(line, ' ');
		while (temp[i.y])
		{
			if (ft_strcmp(temp[i.y], "a") == 0 && (env->pos.x = i.x))
			{
				env->pos.y = i.y;
				env->map[i.x][i.y + 1] = 0;
			}
			else
				env->map[i.x][i.y + 1] = ft_atoi(temp[i.y]);
			i.y++;
		}
		i.x++;
	}
	return (1);
}

static int	ft_check(t_env *env, char *file)
{
	int				fd;
	char			*line;
	t_int_coord		len;

	len.y = 0;
	len.x = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (len.x < ft_strstrlen(ft_strsplit(line, ' ')))
			len.x = ft_strstrlen(ft_strsplit(line, ' '));
		len.y++;
	}
	env->size = len;
	return (1);
}

int			ft_parser(t_env *env, char *str)
{
	int		i;
	int		x;

	i = 0;
	if (!ft_check(env, str))
		return (0);
	env->map = (int**)malloc(sizeof(int*) * ((unsigned long)env->size.y + 2));
	while (i < (env->size.y + 2))
	{
		x = 0;
		env->map[i] = (int*)malloc(sizeof(int) *
				((unsigned long)env->size.x + 2));
		while (x < env->size.x + 2)
			env->map[i][x++] = 1;
		i++;
	}
	ft_remp(env, str);
	if (env->pos.x == 0 || env->pos.y == 0)
		return (NULL);
	return (1);
}
