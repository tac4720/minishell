#include "../minishell.h"

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

