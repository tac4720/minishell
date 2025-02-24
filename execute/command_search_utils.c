/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_search_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:46 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 21:10:44 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	free_and_error(char **cmds, char **path, char *full_path)
{
	free_splits(cmds, path);
	free(full_path);
	perror("access");
	exit(126);
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
				free_and_error(cmds, path, full_path);
			free_split(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*generate_path(char *cmd, char **envp, t_context *ctx)
{
	char	**path;
	char	*all_path;

	if (!cmd || !envp)
		return (NULL);
	// all_path = get_all_path(envp);
	all_path = ft_strjoin("PATH", map_get(ctx->environ, "PATH"));
	if (!all_path)
		return (NULL);
	path = ft_split(all_path, ':');
	if (!path)
		return (NULL);
	return (valid_command(&cmd, path, NULL, NULL));
}
