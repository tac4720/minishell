# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -lreadline
LDFLAGS = -lreadline
LIBFT_PATH = libft
LIBFTFLAGS = -L$(LIBFT_PATH) -lft
SRCS = readline.c interpret.c make_path.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH) all
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFTFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re