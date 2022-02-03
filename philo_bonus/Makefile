SRCS		=	src/main.c

OBJS		=	${SRCS:.c=.o}

NAME		=	philo_bonus

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g

%.o: %.c
				$(CC) $(CFLAGS) -I./includes $< -c -o ${<:.c=.o}

all:			${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

bonus:			${BONUS_NAME}
			
clean:
				rm -f ${OBJS} 

fclean:			clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
