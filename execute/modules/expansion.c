#include "exec.h"

char	*expand_helper(const char *str, t_context *ctx)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_strlen(str) == 1)
			{
				result = ft_strdup("$");
				break;
			}
			if (str[i + 1] == '?')
				result = expand_status(str, &i, result, ctx);
			else
				result = expand_env_var(str, &i, result, ctx);
			continue ;
		}
		result = expand_normal_str(str, &i, result);
	}
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
		// printf("%i\n", current->flag);
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
