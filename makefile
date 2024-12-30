# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -lreadline
LDFLAGS = -lreadline
SRCS = readline.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re