/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:44:38 by gmorer            #+#    #+#             */
/*   Updated: 2016/07/18 10:08:11 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# ifdef __APPLE__
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
#  define ESC 53
#  define SHIFT 258
#  define CTR 269
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define SPACE 49
# endif
# ifndef __APPLE__
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
#  define ESC 65307
#  define SHIFT 65506
#  define CTR 65508
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define SPACE 32
# endif
# define SCREEN_X 1920
# define SCREEN_Y 1080
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct		s_color
{
	int		r;
	int		g;
	int		b;
}					t_color;

typedef struct		s_env
{
	char	*pixel_img;
	void	*mlx;
	void	*window;
	void	*img;
	double	anglex;
	double	angley;
	double	posx;
	double	posy;
	double	planx;
	double	plany;
	int		**map;
	int		bpp;
	int		s_line;
	int		ed;
	int		sizex;
	int		sizey;
}					t_env;

int					**ft_read(char *argv, t_env *env);
int					ft_parser(t_env *env, char *str);
void				draw_pixel(t_env *env, int x, int y, t_color *color);
void				ft_forline(t_env *env);
#endif
