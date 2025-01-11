CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = pipex
SRC = src/pipex.c src/utils.c
SRCS = $(SRC)
OBJS = $(SRCS:.c=.o)
LIBFT_PATH = libft
LIBFT = -L$(LIBFT_PATH) -lft

OUT = $(NAME)

B_SRCS = src/pipex_bonus.c src/utils.c

M_OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

OBJS = $(M_OBJS)
ifdef WITH_BONUS
OBJS = $(B_OBJS)
endif


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) all
	$(CC) $(OBJS) $(LIBFT) -o $(OUT)

all: $(OUT)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

bclean:
	rm -f $(B_OBJS)

fclean: clean bclean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean


b:
	make WITH_BONUS=1


re: fclean all

.PHONY: clean fclean re all b
