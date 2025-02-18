#include "exec.h"

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

