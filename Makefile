# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/07 21:38:57 by zytrams           #+#    #+#              #
#    Updated: 2019/05/14 16:43:08 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./lib/libft/

SRCS_LIST =	coolfdf.c \
			bresenham.c \
			reader.c \
			move.c	\
			3dmath.c \
			handlers.c \
			rotations.c \
			matrixmath.c \
			zoom.c \
			info.c \

OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))

MINILIB = $(MINILIB_DIRECTORY)libmlx.a
MINILIB_DIRECTORY = ./lib/minilibx/

all: $(NAME)

$(NAME): $(MINILIB) $(LIBFT) $(OBJS_LIST)
	$(CC) -o $(NAME) $(OBJS_LIST) -lmlx -framework OpenGL -framework AppKit -L lib/minilibx/ $(LIBFT) -g

$(OBJS_LIST):
	$(CC) -c $(SRCS_LIST) -I ./ -I lib/libft/includes -g

$(MINILIB):
	@$(MAKE) -sC $(MINILIB_DIRECTORY)

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@rm -rf *.o
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIB_DIRECTORY) clean


fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean

re: fclean all
