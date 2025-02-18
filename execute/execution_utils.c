/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:06:53 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:32 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_string_empty(const char *str)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp != ' ' && *tmp != '\t')
			return (0);
		tmp++;
	}
	return (1);
}

void	free_commands(char **cmds)
{
	int	idx;

	if (cmds == NULL)
		return ;
	idx = 0;
	while (cmds[idx])
	{
		free(cmds[idx]);
		idx++;
	}
	free(cmds);
}

char	**remove_helper(char **cmds, int count)
{
	int		idx;
	int		new_idx;
	char	**new_cmds;

	new_cmds = malloc((count + 1) * sizeof(*new_cmds));
	if (new_cmds == NULL)
		return (NULL);
	idx = 0;
	new_idx = 0;
	while (cmds[idx])
	{
		if (is_string_empty(cmds[idx]) == false)
		{
			new_cmds[new_idx] = ft_strdup(cmds[idx]);
			if (new_cmds[new_idx] == NULL)
				return (free_commands(new_cmds), NULL);
			new_idx++;
		}
		idx++;
	}
	new_cmds[new_idx] = NULL;
	return (new_cmds);
}

char	**remove_empty_commands(char **cmds)
{
	int		idx;
	int		new_idx;
	int		count;
	char	**new_cmds;

	count = 0;
	idx = 0;
	while (cmds[idx])
		if (is_string_empty(cmds[idx++]) == false)
			count++;
	return (remove_helper(cmds, count));
}

void	reverse_commands(t_ast_node **cmds, int count)
{
	int			i;
	t_ast_node	*temp;

	i = 0;
	while (i < count / 2)
	{
		temp = cmds[i];
		cmds[i] = cmds[count - 1 - i];
		cmds[count - 1 - i] = temp;
		i++;
	}
}
