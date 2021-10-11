# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robriard <robriard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:21:40 by robriard          #+#    #+#              #
#    Updated: 2021/10/11 14:30:01 by robriard         ###   ########.fr        #
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
FALGS = -Wall -Wextra -Werror -pthread -lpthread

FILES =	main.c 				\
		daily_actions.c 	\
		medic.c 			\
		thread_manager.c 	\
		tools.c 			

SRCS = $(addprefix ./srcs/, $(FILES))
OBJS = ${SRCS:.c=.o}
DEP = $(OBJS:%.o=%.d)

-include $(DEP)
%.o: %.c
	@printf "\e[2K\r- $@ [🔄]"
	@$(CC) $(FLAGS) -MMD -o $@ -c $<
	@printf "\e[2K\r- $@ [✅]\n"

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS}  -o ${NAME}
	@echo "${GREEN}Compilation OK${RESET}"

all: ${NAME}

clean:
	@echo "${RED}deleting ojbects${RESET}"
	@${RM}	${OBJS} ${DEP}

fclean:  clean
	@echo "${RED}deleting executable${RESET}"
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 


# ✅ ❌ 🔄
