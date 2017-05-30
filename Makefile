# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2017/05/30 15:19:34 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
UNAME = $(shell uname)
CC = clang
SDL = SDL2-2.0.5
HPATH = inc/ libft/inc/
SDL_FWK =  frameworks/SDL2.framework/Headers/\
		   frameworks/SDL2_ttf.framework/Headers/\
		   frameworks/SDL2_image.framework/Headers/
CPATH = src/
OPATH = obj/
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
		 draw_line.c\
		 texture.c
OFILES = $(CFILES:.c=.o)
HFILES = inc/get_next_line.h\
		 inc/wolf3d.h\
		 inc/input.h\
		 inc/color.h\
		 libft/inc/libft.h
OBJ = $(addprefix $(OPATH), $(OFILES))
ifeq ($(UNAME), Linux)
	CFLAGS = -g $(shell sdl2-config --libs) -lSDL2 -lSDL2_ttf -lSDL2_image -lm #-fsanitize=address
	SDL2_P		= 
endif
ifeq ($(UNAME), Darwin)
	CFLAGS = -framework SDL2 -framework SDL2_ttf\
			 -framework SDL2_image -F frameworks/
	HPATH += $(SDL_FWK) 
	SDL2_P		= -rpath @loader_path/frameworks/
	HFILES +=\
		  frameworks/SDL2.framework/headers/SDL.h\
		 frameworks/SDL2_ttf.framework/headers/SDL_ttf.h\
		 frameworks/SDL2_image.framework/headers/SDL_image.h
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft
		$(CC) $(OBJ) libft/libft.a  $(CFLAGS) -o $(NAME) $(SDL2_P)

debug: $(OBJ)
		make -C libft
		$(CC) -g $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) $(SDL2_P)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
		mkdir -p $(OPATH)
		$(CC) -g  $(INC) $< -c -o $@


clean:
		make -C libft clean
		rm -f $(OBJ)

fclean: clean
		make -C libft fclean
		rm -f $(NAME)

re: fclean all
