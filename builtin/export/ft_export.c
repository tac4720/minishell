#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../builtin_execute/builtin.h"
#include <stdbool.h>

/*
変数名の先頭文字：アルファベットまたは_

2文字目以降：アルファベット、数字、_

=を含む場合は値部分を無視して検証
	*/

static bool	is_valid_identifier(const char *name)
{
	if (name[0] == '\0')
		return (false);
	if (!(name[0] >= 'A' && name[0] <= 'Z') && !(name[0] >= 'a' && name[0] <= 'z') && name[0] != '_')
		return (false);
	for (int i = 1; name[i]; i++)
	{
		if (!(name[i] >= 'A' && name[i] <= 'Z')
			&& !(name[i] >= 'a' && name[i] <= 'z')
			&& !(name[i] >= '0' && name[i] <= '9')
			&& name[i] != '_')
			return (false);
	}
	return (true);
}

static char	*escape_value(const char *value)
{
	size_t	len;
	char	*escaped;
	size_t	j;

	len = strlen(value);
	escaped = malloc(len * 2 + 1);
	if (!escaped)
		return (NULL);
	j = 0;
	for (size_t i = 0; value[i]; i++)
	{
		if (value[i] == '"' || value[i] == '\\' || value[i] == '$')
			escaped[j++] = '\\';
		escaped[j++] = value[i];
	}
	escaped[j] = '\0';
	return (escaped);
}

static void	print_exported_variables(t_map *env)
{
	t_item	*current;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		current = env->table[i];
		while (current)
		{
			if (current->name)
			{
				printf("declare -x %s", current->name);
				if (current->value)
				{
					char *escaped = escape_value(current->value);
					printf("=\"%s\"", escaped);
					free(escaped);
				}
				else
					printf("=\"\"");
				printf("\n");
			}
			current = current->next;
		}
	}
}

int	ft_export(char **args, t_context *context)
{
	t_map	*env;
	int		status;
	int		i;
	char	*equal;

	env = context->environ;
	status = 0;
	if (!args[1])
		print_exported_variables(env);
	else
	{
		i = 1;
		while (args[i])
		{
			equal = strchr(args[i], '=');
			char *name = equal ? strndup(args[i], equal - args[i]) : strdup(args[i]);
			if (!is_valid_identifier(name))
			{
				fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
				status = 1;
			}
			else if (equal)
				map_put(env, args[i]);
			else if (!map_get(env, name))
				map_put(env, ft_strjoin(name, "="));
			free(name);
			i++;
		}
	}
	return (status);
}
