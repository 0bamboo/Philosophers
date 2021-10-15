# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 16:25:54 by abdait-m          #+#    #+#              #
#    Updated: 2021/10/15 10:24:14 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SEM = philo_bonus

LIB_SEM = sem_philo.a

MAIN_SEM = ./srcs/sem_philo.c

FILES_SEM = ./srcs/parse.c ./srcs/sem_start.c ./srcs/sem_tasks.c ./srcs/sem_init.c ./srcs/sem_create.c \
			./srcs/ft_strdup.c ./srcs/ft_strlen.c ./srcs/ft_strtrim.c ./srcs/ft_substr.c

HEADER = ./header/philosophers.h

OBJECT_SEM = $(FILES_SEM:.c=.o)

FLAGS = -Wextra -Werror -Wall -pthread

all: $(NAME_SEM)

$(NAME_SEM): $(OBJECT_SEM) $(HEADER) $(MAIN_SEM) $(FILES_SEM)
			@ar -rcs $(LIB_SEM) $(OBJECT_SEM)
			@gcc  $(FLAGS) $(MAIN_SEM) $(LIB_SEM) -o $(NAME_SEM)
			@echo "\n\033[35m Philo_bonus's program is created .\033[0m\n"
					

%.o:%.c $(HEADER)
			@gcc -c $< $(FLAGS) -o $@

clean:
			@rm -rf srcs/*.o $(LIB)
			@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
			@rm -rf $(NAME_SEM) $(LIB_SEM)

re : fclean all