/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac472 <tac472@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:31:30 by tac               #+#    #+#             */
/*   Updated: 2025/03/07 15:00:36 by tac472           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execute/exec.h"

void	here_doc_clean(char *line, int fd)
{
	free(line);
	close(fd);
	exit(0);
}

void	handle_eof(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(limiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	heredoc_process(t_infile_redir *ir, t_context *ctx)
{
	pid_t	pid;

	while (ir)
	{
		if (ir->redirection_flag == F_HEREDOC)
		{
			pid = fork();
			if (pid == 0)
				handle_heredoc(ir, ctx);
			setup();
			wait_for_child(ctx, pid);
		}
		ir = ir->next;
	}
}
