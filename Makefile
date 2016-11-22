# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2016/11/22 11:58:26 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
SDL = SDL2-2.0.5
CFLAGSX =  -L/usr/include -lXext -lX11 -lm 
CFLAGS = -L libsdl/lib/ -lSDL2
CPATH = src/
OPATH = obj/
HPATH = inc/ libft/inc/ libsdl/include/SDL2
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
		 libft/inc/libft.h\
		 libsdl/include/SDL2/SDL.h
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft
		$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

linux : $(OBJ)
		make -C libft
		$(CC) $(CFLAGSX) $(OBJ) libft/libft.a  -o $(NAME)

install :
		./install_sdl.sh

debug: $(OBJ)
		make -C libft
		$(CC) -g $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
		mkdir -p $(OPATH)
		$(CC) $(INC) $< -c -o $@


clean:
		make -C libft clean
		rm -f $(OBJ)

fclean: clean
		make -C libft fclean
		rm -f $(NAME)

re: fclean all
