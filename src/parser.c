/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 10:56:43 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/03 13:34:26 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_strstrlen(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

static int	ft_remp(t_env *env, char *str)
{
	int		fd;
	char	*line;
	int		i;
	int		y;
	char	**temp;

	i = 1;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		y = 0;
		temp = ft_strsplit(line, ' ');
		while (temp[y])
		{
			if (ft_strcmp(temp[y], "a") == 0)
			{
				env->pos.x = i;
				env->pos.y = y;
				env->map[i][y] = 0;
			}
			else
				env->map[i][y + 1] = ft_atoi(temp[y]);
			y++;
		}
		i++;
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
		if (len.x == 0)
			len.x = ft_strstrlen(ft_strsplit(line, ' '));
		else
			if(len.x != ft_strstrlen(ft_strsplit(line, ' ')))
				return (0);
		len.y++;
	}
	env->size = len;
	return (1);
}

int			ft_parser(t_env *env, char *str)
{
	int		i;

	i = 0;
	if (!ft_check(env, str))
		return (0);
	env->map = (int**)malloc(sizeof(int*) * ((unsigned long)env->size.y + 2));
	while (i < (env->size.y + 2))
	{
		env->map[i] = (int*)malloc(sizeof(int) * ((unsigned long)env->size.x + 2));
		i++;
	}
	i = 0;
	ft_putendl("test1");
	while (i < env->size.y + 2)
		env->map[i++][0] = 1;
	ft_putendl("test2");
	i = 0;
	while (i < env->size.y + 2)
		env->map[i++][env->size.x + 1] = 1;
	ft_putendl("test3");
	i = 0;
	while (i < env->size.x + 2)
		env->map[0][i++] = 1;
	ft_putendl("test4");
	i = 0;
	while (i < env->size.x + 2)
		env->map[env->size.y + 1][i++] = 1;
	ft_putendl("test5");
	ft_remp(env, str);
	if (env->pos.x == 0 || env->pos.y == 0)
		return (NULL);
	return (1);	
}
