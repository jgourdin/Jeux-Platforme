# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 10:06:08 by jgourdin          #+#    #+#              #
#    Updated: 2017/09/08 06:45:27 by jgourdin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ./includes

LIB = -L. -lmalib

SRCS = get_next_line.c ft_realloc.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
	   ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strclr.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
	   ft_strdup.c ft_striter.c ft_striteri.c ft_strlcat.c ft_strjoin.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncpy.c ft_strnequ.c ft_strncmp.c \
	   ft_strnew.c ft_strnstr.c ft_strequ.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
	   ft_isgraph.c ft_ispunct.c ft_isspace.c ft_isupper.c ft_isxdigit.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c

OBJS = $(SRCS:.c=.o)

DIR_HEADER = -I./

all: $(NAME)

$(NAME): $(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)

$(OBJS): $(SRCS)
		@$(CC) $(FLAG) -c $(SRCS) $(DIR_HEADER)

clean:
		@rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all
