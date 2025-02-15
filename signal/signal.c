/*
インタラクティブモードと非インタラクティブモードの切り分けも必要。標準入力が端末かどうかをisattyでチェックして、シグナルハンドラを設定するかどうか決めるべき。
そうしないと、スクリプト実行時にもCtrl+Cのハンドリングがされてしまう
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <termios.h>
#include <sys/wait.h>
#include <errno.h>
#include "../environ/environ.h"
typedef struct s_context {
	pid_t           shell_pgid;
	struct termios  shell_tmodes; //端末の設定を保存
	int             last_status;//$?で使う
	int             is_interactive;//対話モードかどうか
	t_map            *environ;
} t_context;

int	interpret(char *line, t_context *context);

static volatile sig_atomic_t g_sigint = 0; 
//このグローバル変数は使ってもよい
//volatileはコンパイラに勝手に値の最適化をされないため
//sig_atomicはハンドラ内で安全にアクセスできる型

static void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(t_context *ctx)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (ctx->is_interactive)
	{
		sa.sa_handler = handle_sigint;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
//     t_context	ctx;
//     char		*input;

//     (void)argc;
//     (void)argv;
//     init_context(&ctx, envp);

//     while (1)
//     {
//         if (g_sigint)
//         {
//             rl_redisplay();
//             g_sigint = 0;
//         }

//         input = readline("minishell:)");

//         if (input == NULL)  // EOF (Ctrl+D)の場合
//         {
//             printf("\nExiting...\n");
//             break;
//         }
//         if (*input)
//         {
//             add_history(input);
//             interpret(input, &context); // 入力を解釈して実行
//         }
//         free(input);
//     }
//     return (ctx.last_status);
// }
