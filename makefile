# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 16:25:54 by abdait-m          #+#    #+#              #
#    Updated: 2021/09/29 14:59:26 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIB = philo.a

MAIN = ./srcs/philo.c

LIBFT = ./libft

LIBFT_LIB = $(LIBFT)/libft.a

FILES = ./srcs/parse.c ./srcs/error.c ./srcs/start.c

HEADER = ./header/philosophers.h

OBJECT = $(FILES:.c=.o)


FLAGS = -Wextra -Werror -Wall -pthread

LIBFT_FILES = $(wildcard ./libft/*.c ./libft/*.h)

all: $(NAME)

$(NAME): $(LIBFT_FILES) $(OBJECT) $(HEADER) $(MAIN) $(FILES)
			@make -C $(LIBFT)
			@ar -rcs $(LIB) $(OBJECT)
			@gcc  $(FLAGS) $(MAIN) $(LIB) $(LIBFT_LIB) -o $(NAME)
			@echo "\n\033[35m Philo's program is created .\033[0m\n"
					

%.o:%.c $(HEADER)
			@gcc -c $< $(FLAGS) -o $@

clean:
			@make clean -C $(LIBFT)
			@rm -rf srcs/*.o $(LIB)
			@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
			@make fclean -C $(LIBFT)
			@rm -rf $(NAME) $(LIB) $(NAME)

re : fclean all