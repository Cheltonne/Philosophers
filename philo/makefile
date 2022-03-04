NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FLAGS = -pthread
RM = rm -f

FILES = philo \
	     init \
	     helpers \
		 time_fcts

SRCS =	$(addsuffix .c, $(FILES))

OBJS =	$(addsuffix .o, $(FILES))

.c.o:	$(SRCS)
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(FLAGS)

all: $(NAME)

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
