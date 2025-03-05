/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:19 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/19 18:02:15 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_heredoc(t_infile_redir *ir, t_context *ctx)
{
	int		fd;
	char	*tmp;

	tmp = ft_strjoin("/tmp/", ir->filename);
	fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		free(tmp);
		exit(EXIT_FAILURE);
	}
	here_doc(ir->filename, fd, ctx);
	close(fd);
	// fd = open(tmp, O_RDONLY);
	// if (fd == -1)
	// {
	// 	free(tmp);
	// 	exit (EXIT_FAILURE);
	// }
	// dup2(fd, STDIN_FILENO);
	// close(fd);
	// unlink(tmp);
	free(tmp);
}

void	handle_input_redirect(t_infile_redir *ir, t_context *ctx)
{
	int		fd;
	char	*tmp;

	(void)(ctx);
	while (ir)
	{
		tmp = ft_strjoin("/tmp/", ir->filename);
		if (ir->redirection_flag == F_HEREDOC)
		{
			fd = open(tmp, O_RDONLY);
		}
		else
		{
			remove_quotes(ir->filename);
			fd = open(ir->filename, O_RDONLY);
		}
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(tmp);
		ir = ir->next;
	}
}

void	handle_output_redirect(t_outfile_redir *or)
{
	int	flags;
	int	fd;

	while (or)
	{
		flags = O_WRONLY | O_CREAT;
		if (or->redirection_flag == F_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		remove_quotes(or->filename);
		fd = open(or->filename, flags, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		or = or->next;
	}
}

void	handle_redirect(t_cmd *cmd, t_context *ctx)
{
	handle_input_redirect(cmd->infile_redir, ctx);
	handle_output_redirect(cmd->outfile_redir);
}
