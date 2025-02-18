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


void	remove_quotes(char *str)
{
	int		i = 0;
	int		j = 0;
	char	quote = '\0';

	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (quote == '\0')
			{
				quote = str[i];
				i++;
				continue;
			}
			else if (str[i] == quote)
			{
				quote = '\0';
				i++;
				continue;
			}
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	expand(t_ast_node *node, t_context *ctx)
{
	t_command_args *current;
	char *expand_str;
	char *tmp;

	current = node->command_node->command_args;
	while (current)
	{
		if (current->flag & (F_DOLLAR_IN_DQUOTES | F_SQUOTES | F_DQUOTES))
			remove_quotes(current->string);
		if (current->flag != F_SQUOTES)
		{
			current->string = expand_helper(current->string, ctx);
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


