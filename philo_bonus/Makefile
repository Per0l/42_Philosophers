SRCS		=	src/main.c src/time_utils.c src/philo.c src/logger.c src/parser.c

OBJS		=	${SRCS:.c=.o}

NAME		=	philo_bonus

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -pthread -fsanitize=address

%.o: %.c
				$(CC) $(CFLAGS) -I./includes $< -c -o ${<:.c=.o}

all:			${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			
clean:
				rm -f ${OBJS} 

fclean:			clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
