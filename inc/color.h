/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/02 11:59:02 by gmorer            #+#    #+#             */
/*   Updated: 2016/08/25 17:22:20 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# define BLACK (t_color){0, 0, 0, 0}
# define WHITE (t_color){0, 255, 255, 255}
# define RED (t_color){0, 255, 0, 0}
# define BLUE (t_color){0, 0, 0, 255}
# define YELLOW (t_color){0, 255, 255, 0}
# define CYAN (t_color){0, 0, 255, 255}
# define MAGENTA (t_color){0, 255, 0, 255}
# define GREEN (t_color){0, 0, 128, 0}
# define GREY (t_color){0, 128, 128, 128}
# define MAROON (t_color){0, 128, 0, 0}
# define PURPLE (t_color){0, 128, 0, 128}
# define SILVER (t_color){0, 192, 192, 192}

typedef struct		s_color
{
	double	a;
	int		r;
	int		g;
	int		b;
}					t_color;
#endif
