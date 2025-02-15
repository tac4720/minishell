#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

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
			break ;
		full_path = ft_strjoin(tmp, cmds[0]);
		free(tmp);
		if (!full_path)
			break ;
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) != 0)
			{
				free_splits(cmds, path);
				perror("access");
				exit(126);
			}
			free_splits(cmds, path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_splits(cmds, path);
	return (NULL);
}

char	*generate_path(char *cmd, char **envp)
{
	char	**path;
	char	**cmds;

	if (!cmd || !envp)
		return (NULL);
	path = ft_split(get_all_path(envp), ':');
	if (!path)
		return (NULL);
	cmds = ft_split(cmd, ' ');
	if (!cmds)
	{
		free_split(path);
		return (NULL);
	}
	return (valid_command(cmds, path, NULL, NULL));
}

void is_dir(const char *cmd) {
    struct stat st;
    if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) != 0)
			{
				perror("access");
				exit(126);
			}
		}
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode)) 
	{
		ft_putstr_fd(" Is a directory", 2);
        exit(126);  // Bash と同じ挙動
    }
}

int	check_other(char **args, t_context *ctx, char **envp)
{
	if (ft_strchr(args[0], '/'))
	{
		is_dir(args[0]);	
		if (execve(args[0], args, envp) == -1)
		{
			perror("execve");
			ctx->last_status = 127;
			exit(127);	
			// ft_putstr_fd(" No such file or directory\n", 2);
		}
		return (1);
	}
	if (builtin_execute(args, ctx))
	 	return (1);
	return (0);
}


static void execute_command(char *full_path, char **cmds, char **envp, t_context *ctx)
{
    if (execve(full_path, cmds, envp) == -1)
    {
        free_split(cmds);
        free(full_path);
        exit(EXIT_FAILURE);
    }
    free_split(cmds);
    free(full_path);
}

void ft_execvp(char *cmd, char **envp, t_context *ctx)
{
    char    *full_path;
    char    **cmds;

    if (!cmd || !envp)
        exit(EXIT_FAILURE);
    cmds = ft_split(cmd, ' ');
    if (check_other(cmds, ctx, envp))
    {
        free_split(cmds);
        ctx->last_status = 0;
        return ;
    }
    full_path = generate_path(cmd, envp);
    if (!cmds)
        exit(EXIT_FAILURE);
    if (full_path == NULL)
    {
        ft_putstr_fd(" command not found", 2);
        free_split(cmds);
        ctx->last_status = 127;
        exit(127);
    }
    execute_command(full_path, cmds, envp, ctx);
}

// void ft_execvp(char *cmd, char **envp, t_context *ctx)
// {
// 	char	*full_path;
// 	char	**cmds;

// 	if (!cmd || !envp)
// 		exit(EXIT_FAILURE);
// 	cmds = ft_split(cmd, ' ');
// 	if (check_other(cmds, ctx, envp))
// 	{
// 		free_split(cmds);
// 		ctx->last_status = 0;
// 		return ;
// 	}
// 	full_path = generate_path(cmd, envp);
// 	if (!cmds)
// 		exit(EXIT_FAILURE);
// 	if (full_path == NULL)
// 	{
// 		ft_putstr_fd(" command not found", 2);
// 		free_split(cmds);
// 		ctx->last_status = 127;
// 		exit(127);
// 	}
// 	if (execve(full_path, cmds, envp) == -1)
// 	{
// 		free_split(cmds);
// 		free(full_path);
// 		exit(EXIT_FAILURE);
// 	}
// 	free_split(cmds);
// 	free(full_path);
// }

