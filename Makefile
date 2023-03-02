
NAME        := philo
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -fsanitize=thread -g

SRCS        :=      philo_read.c \
                          philo.c \
						  philo_write.c \
						  philo_thread.c \
						  philo_time.c \
						  philo_utils.c \
						

OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}


RM		    := rm -f

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}


all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re


