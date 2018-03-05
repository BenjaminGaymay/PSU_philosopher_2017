NAME	= philo

CC	= gcc

RM	= rm -f

SRCS	= ./src/main.c \
	  ./src/philo.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -I ./includes/
CFLAGS += -W -Wall -Wextra

LDFLAGS	= -Llib -lriceferee -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
