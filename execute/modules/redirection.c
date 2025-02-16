#include "exec.h"

 void handle_heredoc(t_infile_redir *ir)
{
    int fd;

    fd = open(ir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    here_doc(ir->filename, fd);
    close(fd);
    fd = open(ir->filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    unlink(ir->filename);
}

 void handle_input_redirect(t_infile_redir *ir)
{
    int fd;

    while (ir)
    {
        if (ir->redirection_flag == F_HEREDOC)
        {
            handle_heredoc(ir);
            ir = ir->next;
            continue;
        }
        fd = open(ir->filename, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        ir = ir->next;
    }
}

 void handle_output_redirect(t_outfile_redir *or)
{
    int flags;
    int fd;

    while (or)
    {
        flags = O_WRONLY | O_CREAT;
        if (or->redirection_flag == F_APPEND)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
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

void handle_redirect(t_cmd *cmd)
{
	if (cmd->infile_redir->redirection_flag == FILE_IN ||
		cmd->outfile_redir->redirection_flag == FILE_OUT)
	{
		remove_quotes(cmd->command_args->string);
	}
    handle_input_redirect(cmd->infile_redir);
    handle_output_redirect(cmd->outfile_redir);
}
