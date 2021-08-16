# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robriard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:21:40 by robriard          #+#    #+#              #
#    Updated: 2021/07/13 13:19:01 by robriard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef RESET
BLACK		:= $(shell tput -Txterm setaf 0)
RED			:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)
endif

NAME = philo
CC = gcc
FALGS = -Wall -Wextra -Werror

FILES =	main.c

SRCS = $(addprefix ./srcs/, $(FILES))
OBJS = ${SRCS:.c=.o}

all: ${OBJS}
	@${CC} ${FLAGS} ${OBJS}  -o ${NAME}
	@echo "${GREEN}Compilation OK${RESET}"

clean:
	@echo "${RED}deleting ojbects${RESET}"
	@${RM}	${OBJS}

fclean:  clean
	@echo "${RED}deleting executable${RESET}"
	@${RM} ${NAME}

re: fclean all clean

.PHONY: all clean fclean re 
