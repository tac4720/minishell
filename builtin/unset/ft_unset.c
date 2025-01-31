#include "../builtin_execute/builtin.h"
#include <stdio.h>
#include <stdbool.h>

static bool	is_valid_identifier(const char *str)
{
	if (str[0] == '\0' || (!(str[0] >= 'A' && str[0] <= 'Z')
			&& !(str[0] >= 'a' && str[0] <= 'z') && str[0] != '_'))
		return (false);
	while (*str)
	{
		if (!((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')
				|| (*str >= '0' && *str <= '9') || *str == '_'))
			return (false);
		str++;
	}
	return (true);
}

int	ft_unset(char **args, t_context *context)
{
	t_map	*env;
	int		status;
	int		i;

	env = context->environ;
	status = 0;
	if (args[1] == NULL)
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			fprintf(stderr, "unset: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		else
			map_unset(env, args[i]);
		i++;
	}
	return (status);
}
