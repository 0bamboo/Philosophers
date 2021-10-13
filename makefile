# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 16:25:54 by abdait-m          #+#    #+#              #
#    Updated: 2021/10/13 20:59:03 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_SEM = philo_bonus

LIB = philo.a

LIB_SEM = sem_philo.a

MAIN = ./srcs/philo.c

MAIN_SEM = ./srcs/sem_philo.c

LIBFT = ./libft

LIBFT_LIB = $(LIBFT)/libft.a

FILES = ./srcs/parse.c ./srcs/error.c ./srcs/start.c ./srcs/tasks.c

FILES_SEM = ./srcs/parse.c ./srcs/sem_start.c ./srcs/sem_tasks.c ./srcs/sem_init.c

HEADER = ./header/philosophers.h

OBJECT = $(FILES:.c=.o)

OBJECT_SEM = $(FILES_SEM:.c=.o)

FLAGS = -Wextra -Werror -Wall -pthread

LIBFT_FILES = $(wildcard ./libft/*.c ./libft/*.h)

all: $(NAME)

$(NAME): $(LIBFT_FILES) $(OBJECT) $(HEADER) $(MAIN) $(FILES)
			@make -C $(LIBFT)
			@ar -rcs $(LIB) $(OBJECT)
			@gcc  $(FLAGS) $(MAIN) $(LIB) $(LIBFT_LIB) -o $(NAME)
			@echo "\n\033[35m Philo's program is created .\033[0m\n"

bonus: $(NAME_SEM)

$(NAME_SEM): $(LIBFT_FILES) $(OBJECT_SEM) $(HEADER) $(MAIN_SEM) $(FILES_SEM)
			@make -C $(LIBFT)
			@ar -rcs $(LIB_SEM) $(OBJECT_SEM)
			@gcc  $(FLAGS) $(MAIN_SEM) $(LIB_SEM) $(LIBFT_LIB) -o $(NAME_SEM)
			@echo "\n\033[35m Philo_bonus's program is created .\033[0m\n"
					

%.o:%.c $(HEADER)
			@gcc -c $< $(FLAGS) -o $@

clean:
			@make clean -C $(LIBFT)
			@rm -rf srcs/*.o $(LIB)
			@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
			@make fclean -C $(LIBFT)
			@rm -rf $(NAME) $(LIB) $(NAME) $(NAME_SEM) $(LIB_SEM)

re : fclean all