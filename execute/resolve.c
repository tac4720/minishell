
#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

char	*get_all_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strlen(envp[i]) >= 5 && ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_splits(char **cmds, char **path)
{
	free_split(cmds);
	free_split(path);
}

char	*valid_command(char **cmds, char **path, char *tmp, char *full_path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			break;
		full_path = ft_strjoin(tmp, cmds[0]);
		free(tmp);
		if (!full_path)
			break;
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) != 0)
			{
				free_splits(cmds, path);
				perror("access");
				exit(126);
			}
			free_split(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*generate_path(char *cmd, char **envp)
{
	char	**path;
	char	*all_path;

	if (!cmd || !envp)
		return (NULL);
	all_path = get_all_path(envp);
	if (!all_path)
		return (NULL);
	path = ft_split(all_path, ':');
	if (!path)
		return (NULL);
	return (valid_command(&cmd, path, NULL, NULL));
}

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
		return (1);
	}
	if (builtin_execute(args, ctx))
		return (1);
	return (0);
}

static void	execute_command(char *full_path, char **cmds, char **envp, t_context *ctx)
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
		ctx->last_status = 0;
		return;
	}

	full_path = generate_path(cmds[0], envp);
	if (!full_path)
	{
		ft_putstr_fd(" command not found\n", 2);
		ctx->last_status = 127;
		exit(127);
	}

	execute_command(full_path, cmds, envp, ctx);
}

