#include "../../minishell.h"
void	ft_cd(char **args, t_context *context);
void	ft_echo(char **args, t_context *context);
void	ft_env(char **args, t_context *context);
void	ft_exit(char **args, t_context *context);
void	ft_export(char **args, t_context *context);
void	ft_pwd(char **args, t_context *context);
void	ft_unset(char **args, t_context *context);
void    free_commands(char **cmds);
void	free_and_exit(t_context *ctx, char **args, int status);
