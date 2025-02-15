CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = pipex
SRC = src/pipex.c src/utils.c
SRCS = $(SRC)
OBJS = $(SRCS:.c=.o)
LIBFT_PATH = libft
LIBFT = -L$(LIBFT_PATH) -lft

OUT = $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) all
	$(CC) $(OBJS) $(LIBFT) -o $(OUT)

all: $(OUT)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: clean fclean re all
