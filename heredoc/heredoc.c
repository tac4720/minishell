#include "../minishell.h"
#include <stdbool.h>
#include <signal.h>

static volatile sig_atomic_t	g_signal_flag;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_flag = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
}

static void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static bool	is_limiter_match(char *line, const char *limiter)
{
	size_t	len;
	size_t	limiter_len;

	if (!line)
		return (false);
	limiter_len = ft_strlen(limiter);
	len = ft_strlen(line);
	if (len == limiter_len + 1 && line[len - 1] == '\n')
		return (ft_strncmp(line, limiter, limiter_len) == 0);
	if (len == limiter_len && ft_strncmp(line, limiter, limiter_len) == 0)
		return (true);
	return (false);
}

void	here_doc(const char *limiter, int fd)
{
	char	*input;
	char	*line;

	line = "";
	setup_heredoc_signals();
	while (true)
	{
		input = readline("> ");
		if (g_signal_flag)
		{
			free(input);
			ft_putstr_fd("\n", STDERR_FILENO);
			break ;
		}
		if (!input)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file", 2);
			ft_putstr_fd(" (wanted `", 2); 
			ft_putstr_fd(limiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (is_limiter_match(input, limiter))
		{
			ft_putstr_fd(line, fd);
			free(input);
			break ;
		}
		line = ft_strjoin(line, input);
		line = ft_strjoin(line, "\n");
		free(input);
	}
	close(fd);
}

// int main(void)
// {
// 	here_doc("limiter", 0);
// }
