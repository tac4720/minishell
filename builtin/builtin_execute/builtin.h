/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thashimo <thashimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:08:19 by thashimo          #+#    #+#             */
/*   Updated: 2025/03/02 18:49:11 by thashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../../minishell.h"

void		ft_cd(char **args, t_context *context);
void		ft_cd_p(char **args, t_context *context);
void		ft_echo(char **args, t_context *context);
void		ft_env(char **args, t_context *context);
void		ft_env_p(char **args, t_context *context);
void		ft_exit(char **args, t_context *context);
void		ft_exit_p(char **args, t_context *context);
void		ft_export(char **args, t_context *context);
void		ft_export_p(char **args, t_context *context);
void		ft_pwd(char **args, t_context *context);
void		ft_unset(char **args, t_context *context);
void		ft_unset_p(char **args, t_context *context);
void		free_commands(char **cmds);
void		free_and_exit(t_context *ctx, char **args, int status);
void		free_and_exit_p(t_context *ctx, char **args, int status);
long long	ft_atol(const char *nptr, int *of);
void		sort_list(char **list);
char		**hashmap_to_list(t_map *environ);
#endif
