CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
INCLUDES = -I.

LIBFT_PATH = libft
LIBFTFLAGS = -L$(LIBFT_PATH) -lft

BUILTIN_SRCS =  builtin/builtin_execute/execute.c \
               builtin/cd/ft_cd.c \
               builtin/echo/ft_echo.c \
               builtin/env/ft_env.c \
               builtin/exit/ft_exit.c \
			   builtin/exit/ft_atol.c \
               builtin/export/ft_export.c \
               builtin/pwd/ft_pwd.c \
               builtin/unset/ft_unset.c \
			   builtin/env/sort.c

ENVIRON_SRCS = environ/item.c \
               environ/map_create.c \
               environ/map_get_put.c \
               environ/map_unset.c \
               environ/map_utils.c \

MAIN_SRCS = readline.c \
            init.c \
            errors/errors.c \
            errors/error_in_parse.c \
            errors/error_in_parse_2.c \
            errors/free_map.c \
            errors/check_open_close.c \
            tokenizer/tokenizer.c \
            tokenizer/get_word_token.c \
            tokenizer/get_operator_token.c \
            parse/parse_command.c \
            parse/parse_command_2.c \
            parse/parse_pipes.c \
            parse/parse_redir.c \
            parse/add_infile_redir_node.c \
            parse/add_outfile_redir_node.c \
            parse/parse.c \
            execute/command_search.c \
            execute/command_search_utils.c \
            execute/execution.c \
            execute/execution_utils.c \
            execute/execution_utils2.c \
            execute/execution_utils3.c \
            execute/expantion.c \
            execute/expantion_utils.c \
            execute/redirection.c \
            signal/signal.c \
			heredoc/heredoc.c \
			heredoc/heredoc_utils.c 

SRCS = $(MAIN_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS)

OBJS = $(SRCS:.c=.o)

DEPS = $(OBJS:.o=.d)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFTFLAGS)

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
