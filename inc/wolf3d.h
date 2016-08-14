/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:44:38 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/03 16:19:17 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define SCREEN_X 1440
# define SCREEN_Y 940
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include "mlx.h"
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

typedef struct		s_env
{
	char			*pixel_img;
	void			*mlx;
	void			*window;
	void			*img;
	void			*minimap;
	clock_t			oldtime;
	t_key			key;
	t_double_coord	dir;
	t_double_coord	pos;
	t_double_coord	plan;
	t_int_coord		size;
	int				shadow;
	int				**map;
	int				bpp;
	int				s_line;
	int				ed;
}					t_env;

int					**ft_read(char *argv, t_env *env);
int					ft_parser(t_env *env, char *str);
void				draw_pixel(t_env *env, void *img, t_int_coord coord, t_color *color);
void				ft_forline(t_env *env);
int					ft_image_put(t_env *env);
#endif
