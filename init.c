/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tac <tac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:07:31 by thashimo          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:25 by tac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environment(t_map *env, char **envp)
{
	char	*eq_pos;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			name = ft_substr(envp[i], 0, eq_pos - envp[i]);
			value = ft_strdup(eq_pos + 1);
			if (!name || !value)
			{
				free(name);
				free(value);
				continue ;
			}
			map_set(env, name, value);
			free(name);
			free(value);
		}
		i++;
	}
}

void	init_context(t_context *ctx, char **envp)
{
	ctx->shell_pgid = getpid();
	ctx->is_interactive = isatty(STDIN_FILENO);
	ctx->last_status = 0;
	ctx->environ = map_new();
	ctx->env = envp;
	init_environment(ctx->environ, envp);
	tcgetattr(STDIN_FILENO, &ctx->shell_tmodes);
	setup_signals(ctx);
}
