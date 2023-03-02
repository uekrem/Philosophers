NAME        := philo
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -fsanitize=thread -g

SRCS        :=      philo_read.c \
                          philo.c \
						  philo_write.c \
						  philo_thread.c \
						  philo_time.c \
						  philo_utils.c \
						
OBJS = $(SRCS:.c=.o)

RM		    := rm -rf

all:		$(NAME)

$(NAME): $(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $<

clean:
			@ $(RM) ./*.o

fclean: clean
			@ $(RM) $(NAME)

re:			fclean all
.PHONY:		all clean fclean re