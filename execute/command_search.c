#include "exec.h"

void	is_dir(const char *cmd)
{
	struct stat st;

	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(" Is a directory\n", 2);
			exit(126);
		}
		if (access(cmd, X_OK) != 0)
		{
			perror("access");
			exit(126);
		}
	}
}

int	check_other(char **args, t_context *ctx, char **envp)
{
	if (ft_strchr(args[0], '/'))
	{
		is_dir(args[0]);
		if (execve(args[0], args, envp) == -1)
		{
			if (errno == ENOENT)
				ft_putstr_fd(" No such file or directory\n", 2);
			else
				perror("execve");
			ctx->last_status = 127;
			exit(127);
		}
		ctx->last_status = 0;
		return (1);
	}
	if (builtin_execute(args, ctx))
		return (1);
	return (0);
}

void	execute_command_helper(char *full_path, char **cmds, char **envp, t_context *ctx)
{
	if (execve(full_path, cmds, envp) == -1)
	{
		free(full_path);
		exit(EXIT_FAILURE);
	}
	free(full_path);
}

void	ft_execvp(char **cmds, char **envp, t_context *ctx)
{
	char	*full_path;

	if (!cmds || !cmds[0] || !envp)
		exit(EXIT_FAILURE);

	if (check_other(cmds, ctx, envp))
	{
		return;
	}

	full_path = generate_path(cmds[0], envp);
	if (!full_path)
	{
		ft_putstr_fd(" command not found\n", 2);
		ctx->last_status = 127;
		exit(127);
	}
	execute_command_helper(full_path, cmds, envp, ctx);
}
