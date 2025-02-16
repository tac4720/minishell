#include "exec.h"

char	*get_env_value(const char *str, int *i)
{
	char	*var_name;
	int		start;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

char	*expand_env_var(const char *str, int *i, char *result, t_context *ctx)
{
	char	*var_name;
	char	*expand_str;

	(*i)++;
	var_name = get_env_value(str, i);
	expand_str = map_get(ctx->environ, var_name);
	free(var_name);
	if (expand_str)
	{
		result = join_and_free(result , expand_str, 0);
	}
	else
	{
		result = join_and_free(result, "", 0);
	}
	return (result);
}

char	*expand_normal_str(const char *str, int *i, char *result)
{
	char	*tmp;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	result = join_and_free(result, tmp, 1);
	return (result);
}
