/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:14 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/19 18:57:58 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*join_and_free(char *s1, char *s2, int free_s2)
{
	char	*result;
	char	*tmp;

	tmp = s1;
	result = ft_strjoin(s1, s2);
	free(tmp);
	if (free_s2)
		free(s2);
	return (result);
}

void	remove_quotes_helper(char *str, char quote, int i, int j)
{
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (quote == '\0')
			{
				quote = str[i];
				i++;
				continue ;
			}
			else if (str[i] == quote)
			{
				quote = '\0';
				i++;
				continue ;
			}
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	remove_quotes_helper(str, i, j, quote);
}

void	expand(t_ast_node *node, t_context *ctx)
{
	t_command_args	*current;
	t_infile_redir *ir;
	char			*tmp;

	ir = node->command_node->infile_redir; 
	while (ir)
	{
		if (ir->redirection_flag == F_HEREDOC)
		{
			handle_heredoc(node->command_node->infile_redir, ctx);
		}
		ir = ir->next;
	}
	current = node->command_node->command_args;
	while (current)
	{
		if (current->flag & (F_DOLLAR_IN_DQUOTES | F_SQUOTES | F_DQUOTES))
			remove_quotes(current->string);
		if (current->flag != F_SQUOTES)
		{
			tmp = expand_helper(current->string, ctx);
			free(current->string);
			current->string = tmp;
		}
		current = current->next;
	}
}

void	expand_ast(t_ast_node *node, char **envp, t_context *ctx)
{
	if (!node)
		return ;
	if (node->type == AST_PIPE)
	{
		expand_ast(node->pipe_node->left, envp, ctx);
		expand_ast(node->pipe_node->right, envp, ctx);
	}
	else
	{
		expand(node, ctx);
	}
}
