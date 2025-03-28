/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:23 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:23 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>
#include <signal.h>

void	handle_eof(char *limiter);

static void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
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

static char	*process_input_line(char **line, char *input)
{
	char	*tmp;

	tmp = ft_strjoin(*line, input);
	free(*line);
	*line = tmp;
	tmp = ft_strjoin(*line, "\n");
	free(*line);
	return (tmp);
}

void	here_doc(char *limiter, int fd)
{
	char	*input;
	char	*line;

	line = ft_strdup("");
	setup_heredoc_signals();
	while (!g_sigint)
	{
		input = readline("> ");
		if (!input)
		{
			handle_eof(limiter);
			break ;
		}
		if (is_limiter_match(input, limiter))
		{
			ft_putstr_fd(line, fd);
			free(input);
			break ;
		}
		line = process_input_line(&line, input);
		free(input);
	}
	here_doc_clean(line, fd);
}
