SRCS		=	main.c time_utils.c philo.c logger.c parser.c

OBJS		=	${SRCS:.c=.o}

NAME		=	philo_bonus

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror #-g3 -fsanitize=address

all:			${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			
clean:
				rm -f ${OBJS} 

fclean:			clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
