# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2016/07/06 18:03:28 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = clang
CFLAGSX =  -L/usr/include -lXext -lX11 -lmlx -lm 
CFLAGS = -Weverything -L minilibx -lmlx -framework OpenGL -framework AppKit
CPATH = src/
OPATH = obj/
HPATH = inc/ libft/ minilibx/
INC = $(addprefix -I , $(HPATH))
CFILES = main.c\
		 ft_print.c
OFILES = $(CFILES:.c=.o)
HFILES = inc/wolf3d.h libft/libft.h
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft
		make -C minilibx_macos
		$(CC) $(CFLAGS) $(OBJ) libft/libft.a minilibx_macos/libmlx.a -o $(NAME)

linux : $(OBJ)
		make -C libft
		make -C minilibx
		$(CC) $(CFLAGSX) $(OBJ) libft/libft.a minilibx/libmlx.a -o $(NAME)


debug: $(OBJ)
		make -C libft
		make -C minilibx
		make -C minilibx_macos
		$(CC) -g $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
		mkdir -p $(OPATH)
		$(CC) $(CFLAGS) $(INC) $< -c -o $@


clean:
		make -C minilibx clean
		make -C minilibx_macos clean
		make -C libft clean
		rm -f $(OBJ)

fclean: clean
		make -C libft fclean
		rm -f $(NAME)

re: fclean all
