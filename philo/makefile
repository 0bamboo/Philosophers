# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 16:25:54 by abdait-m          #+#    #+#              #
#    Updated: 2021/10/15 10:26:50 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIB = philo.a

MAIN = ./srcs/philo.c

FILES = ./srcs/parse.c ./srcs/error.c ./srcs/start.c ./srcs/tasks.c \
		./srcs/ft_strdup.c ./srcs/ft_strlen.c ./srcs/ft_strtrim.c ./srcs/ft_substr.c

HEADER = ./header/philosophers.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall -pthread

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER) $(MAIN) $(FILES)
			@ar -rcs $(LIB) $(OBJECT)
			@gcc  $(FLAGS) $(MAIN) $(LIB) -o $(NAME)
			@echo "\n\033[35m Philo's program is created .\033[0m\n"


%.o:%.c $(HEADER)
			@gcc -c $< $(FLAGS) -o $@

clean:
			@rm -rf srcs/*.o $(LIB)
			@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
			@rm -rf $(NAME) $(LIB)

re : fclean all