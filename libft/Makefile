# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 15:48:22 by abdait-m          #+#    #+#              #
#    Updated: 2021/07/01 12:10:41 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = split_all_ws.c ft_strmapi.c ft_itoa.c ft_strtrim.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putchar_fd.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memmove.c \
		ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_putstr_fd.c ft_strlcat.c

OBJ = $(FILES:.c=.o)

FLG = -Wall -Wextra -Werror

all: $(NAME) 

$(NAME): $(OBJ) $(FILES)
		@ar rcs $(NAME) $(OBJ)
		@ranlib $(NAME) 

%.o:%.c
	@gcc  -c $< $(FLG)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
