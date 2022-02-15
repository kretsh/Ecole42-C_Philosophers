# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cowen <cowen@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 18:13:29 by cowen             #+#    #+#              #
#    Updated: 2021/11/25 22:53:18 by cowen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = 	main.c parse_utils.c philo_processes_utils.c philo_processes.c\

HEADER = philo_processes.h

OBJS = $(patsubst %.c, %.o, $(SRCS))

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.PHONY	: 	all clean fclean re

all		:	$(NAME)

${NAME}	:	${OBJS} $(HEADER)
			@ $(CC) $(CFLAGS) ${OBJS} -o ${NAME}
			@printf "\e[38;5;226m./$@ successfully build\n"

%.o 	: 	%.c $(HEADER) 		
			@ $(CC) $(CFLAGS) -c $< -o $@
			
clean	: 		
			@ ${RM} ${OBJS}
			@ printf "\e[38;5;121m.o files deleted\n"

fclean	:		clean
			@ ${RM} ${NAME}
			@ printf "\e[38;5;121mBinaries deleted\n"
	
re		:	fclean all
