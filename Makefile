# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2016/09/02 10:45:07 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
CFLAGSX =  -L/usr/include -lXext -lX11 -lm 
CFLAGS =  -L minilibx -lmlx -framework OpenGL -framework AppKit -Wextra -Wall -Werror
CPATH = src/
OPATH = obj/
HPATH = inc/ libft/ minilibx_macos/
INC = $(addprefix -I , $(HPATH))
CFILES = main.c\
		 ft_print.c\
		 get_next_line.c\
		 parser.c\
		 print.c\
		 move.c\
		 minimap.c\
		 getsize.c\
		 color.c\
		 draw_line.c
OFILES = $(CFILES:.c=.o)
HFILES = inc/get_next_line.h\
		 inc/wolf3d.h\
		 inc/input.h\
		 inc/color.h\
		 libft/libft.h
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
		$(CC)  $(INC) $< -c -o $@


clean:
		make -C minilibx clean
		make -C minilibx_macos clean
		make -C libft clean
		rm -f $(OBJ)

fclean: clean
		make -C libft fclean
		rm -f $(NAME)

re: fclean all
