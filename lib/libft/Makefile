# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:34:56 by zytrams           #+#    #+#              #
#    Updated: 2019/05/04 22:07:21 by zytrams          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -c -Wall -Wextra -Werror

OBJS_DIRECTORY = ./objs/
SRCS_DIRECTORY = ./srcs/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = libft.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
INCLUDES = -I$(HEADERS_DIRECTORY)

SRCS_LIST = ft_toupper.c ft_tolower.c ft_strstr.c ft_strrchr.c ft_strnstr.c ft_strncpy.c ft_memset.c ft_lstreduce.c\
	ft_strncmp.c ft_strncat.c ft_strlcat.c ft_strdup.c ft_strcpy.c ft_strchr.c ft_strcat.c ft_memmove.c \
	ft_memcmp.c ft_memchr.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_memccpy.c \
	ft_memcpy.c ft_strlen.c ft_strcmp.c ft_isdigit.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	ft_strsplit.c ft_itoa.c ft_itoa_base.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putnbr_fd.c ft_putendl_fd.c ft_lstnew.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstdel.c ft_lstadd.c ft_isblank.c \
	ft_isspace.c ft_strcapitalize.c ft_islower.c get_next_line.c

SRCS = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))

all: $(NAME)

$(NAME): $(OBJS_DIRECTORY) $(OBJS)
	@ar rc libft.a $(OBJS)
	@ranlib libft.a

$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)
	@echo "$(NAME): $(OBJS_DIRECTORY) was created"

$(OBJS_DIRECTORY)%.o: $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf libft.a

re: fclean all
