/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:44:38 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/30 05:10:17 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define SCREEN_X 1440
# define SCREEN_Y 940
# define TEXTURE_MAX 10
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include "SDL.h"
# include "get_next_line.h"
# include "libft.h"
# include "color.h"

typedef struct		s_double_coord
{
	double	x;
	double	y;
}					t_double_coord;

typedef struct		s_int_coord
{
	int	x;
	int	y;
}					t_int_coord;

typedef	struct		s_texture
{
	t_int_coord	coord;
	SDL_Texture	*texture;
}					t_texture;


typedef struct		s_key
{
	int		turn;
	int		move;
}					t_key;

typedef struct		s_block
{
	int			number;
	int			collide;
	int			isok;
	int			numberex;
	int			collideex;
	int			tp;
	t_int_coord tpto;
}					t_block;

typedef struct		s_calc
{
	t_color			color;
	t_double_coord	raydir;
	t_double_coord	dis;
	t_double_coord	delta;
	t_int_coord		step;
	t_int_coord		map;
	double			temp;
	int				side;
}					t_calc;

typedef struct		s_env
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
//	TTF_Font		*font;
	t_key			key;
	t_double_coord	dir;
	t_double_coord	pos;
	t_double_coord	plan;
	t_int_coord		screen;
	t_int_coord		size;
	int				horizon;
	int				colormod;
	int				shadow;
	int				**map;
	int				mouse;
	t_texture		*texture[TEXTURE_MAX];
}					t_env;

void				load_texture(t_env *env);
int					ft_minimap(t_env *env);
t_color				colorchoose(int i);
int					ft_exit(t_env *env);
int					getsize(t_env **env, char *argc);
int					**ft_read(char *argv, t_env *env);
int					ft_parser(t_env *env, char *str);
void				draw_pixel(t_env *env, t_int_coord coord, t_color *color);
void				ft_forline(t_env *env);
void				ft_print_line(t_env *env, t_color color, int len, int x);
int					ft_image_put(t_env *env);
#endif
