# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
INCLUDES = -I. -I./builtin

# ライブラリ関連の設定
LIBFT_PATH = libft
LIBFTFLAGS = -L$(LIBFT_PATH) -lft

# ビルトインコマンドのソースファイル
BUILTIN_SRCS = builtin/builtin_execute/execute.c \
               builtin/cd/ft_cd.c \
               builtin/echo/ft_echo.c \
               builtin/env/ft_env.c \
               builtin/exit/ft_exit.c \
               builtin/export/ft_export.c \
               builtin/pwd/ft_pwd.c \
               builtin/unset/ft_unset.c

ENVIRON_SRCS = environ/hash_map.c

# メインプログラムのソースファイル
MAIN_SRCS = readline.c \
            interpret.c \
            make_path.c

# 全ソースファイルの結合
SRCS = $(MAIN_SRCS) $(BUILTIN_SRCS) $(ENVIRON_SRCS)

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# 依存関係ファイル
DEPS = $(OBJS:.o=.d)

# 実行ファイル名
NAME = minishell

# ビルドルール
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFTFLAGS)

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

# オブジェクトファイルの生成
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# 依存関係の読み込み
-include $(DEPS)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

