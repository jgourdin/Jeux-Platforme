# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joinacio <joinacio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 05:43:41 by joinacio          #+#    #+#              #
#    Updated: 2017/12/04 17:50:42 by jgourdin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := SBOUB

OBJ := draw.c init.c input.c main.c map.c player.c animation.c monster.c font.c menu.c fireballs.c plateforme.c

all : $(NAME);

$(NAME): $(OBJS)
	make -C ./libft
	gcc -L./libft -lft `SDL-config --cflags --libs` -lSDL_ttf -lSDL_image -lSDL_mixer $(OBJ) -o $(NAME)

clean:
	rm -rf $(NAME);
	make -C ./libft clean

re: clean all
