/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkajiwar <dkajiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:51:26 by dkajiwar          #+#    #+#             */
/*   Updated: 2025/02/19 14:48:38 by dkajiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H
# include "environ/environ.h"
# include <termios.h>
# define OPERATORS	"<>|"

typedef struct s_context		t_context;
typedef enum e_token_type		t_token_type;
typedef enum e_ast_node_type	t_ast_node_type;
typedef struct s_ast_node		t_ast_node;
typedef struct s_pipe			t_pipe;
typedef struct s_command_args	t_command_args;
typedef struct s_operator		t_operator;
typedef struct s_redir			t_redir;
typedef enum e_flags			t_flags;
typedef struct s_token			t_token;
typedef struct s_env			t_env;
typedef struct s_stack			t_stack;
typedef struct s_shell			t_shell;
typedef struct s_outfile_redir	t_outfile_redir;
typedef struct s_infile_redir	t_infile_redir;
typedef enum e_command_flags	t_command_flags;

typedef struct s_exec_info
{
	int		count;
	int		i;
	char	**envp;
}	t_exec_info;

typedef enum e_token_type {
	HEREDOC,
	APPEND,
	FILE_IN,
	FILE_OUT,
	ENV_PARAM,
	PIPE_OP,
	WORD,
	ERROR
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	int				flag;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_context{
	int				last_status;
	pid_t			shell_pgid;
	struct termios	shell_tmodes;
	int				is_interactive;
	t_map			*environ;
	t_exec_info		*info;
	char			**env;
	t_ast_node		*root_node;
	t_token			*token_list_top;
	char			*readline;
	int				is_in_pipeline;
}	t_context;

typedef struct s_command_args
{
	char			*string;
	t_command_args	*next;
	int				flag;	
}	t_command_args;

typedef struct s_cm
{
	int				in_fd;
	int				out_fd;
	int				num_of_words;
	t_command_args	*command_args;
	t_infile_redir	*infile_redir;
	t_outfile_redir	*outfile_redir;
}	t_cmd;

typedef enum e_ast_node_type
{
	AST_PIPE,
	AST_COMMAND
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type	type;
	t_cmd			*command_node;
	t_pipe			*pipe_node;
}	t_ast_node;

typedef struct s_pipe
{
	int			in_fd;
	int			out_fd;
	t_ast_node	*left;
	t_ast_node	*right;
}	t_pipe;

typedef enum e_flags
{
	F_DOLLAR			= 1 << 0,
	F_SQUOTES			= 1 << 1,
	F_DQUOTES			= 1 << 2,
	F_ASSIGNMENT		= 1 << 3,
	F_DOLLAR_IN_DQUOTES		= 1 << 4,
	F_EXPANDED			= 1 << 5,
	F_DEL_QUOTES		= 1 << 6
}	t_flags;

typedef enum e_redir_flags
{
	F_NO_REDIR = 1 << 0,
	F_INFILE = 1 << 1,
	F_OUTFILE = 1 << 2,
	F_HEREDOC = 1 << 3,
	F_APPEND = 1 << 4
}	t_redir_flags;

typedef struct s_infile_redir
{
	char			*filename;
	t_redir_flags	redirection_flag;
	t_infile_redir	*next;
}	t_infile_redir;

typedef struct s_outfile_redir
{
	char			*filename;
	t_redir_flags	redirection_flag;
	t_outfile_redir	*next;
}	t_outfile_redir;

#endif