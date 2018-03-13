# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joinacio <joinacio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 05:43:41 by joinacio          #+#    #+#              #
#    Updated: 2017/12/04 18:03:24 by jgourdin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := Editor

OBJ := draw.c init.c input.c main.c map.c font.c

all : $(NAME);

$(NAME): $(OBJS)
	make -C ./libft
	gcc -L./libft -lft `SDL-config --cflags --libs` -lSDL_ttf $(OBJ) -o $(NAME)

clean:
	rm -rf $(NAME);
	make -C ./libft clean

re: clean all
