/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 10:56:43 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/02 12:28:06 by gmorer           ###   ########.fr       */
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

	i = 0;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		y = 0;
		temp = ft_strsplit(line, ' ');
		while (temp[y])
		{
			env->map[i][y] = ft_atoi(temp[y]);
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
	env->map = (int**)malloc(sizeof(int*) * (unsigned long)env->size.y);
	while (i < env->size.x)
	{
		env->map[i] = (int*)malloc(sizeof(int) * (unsigned long)env->size.x);
		i++;
	}
	ft_remp(env, str);
	return (1);	
}
