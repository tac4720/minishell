#include "minishell.h"



int	interpret(char *line, t_context *context)
{
	t_token *tokens;
	tokens = input_scanner(line);
	while(tokens)
    {
        printf("%s\n", tokens->cmd->input);
        tokens = tokens->next;
    }
    return (0);
}


