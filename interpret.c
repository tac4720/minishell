#include "minishell.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

int	interpret(char *line, t_context *context)
{
	extern char	**environ;
	char		**argv;
    char        *tmp;
	pid_t		pid;
	int			wstatus;
	t_token *token;

	pid = fork();
	token = tokenize(line);
	t_token *current = token;
	int cnt = 0;
	while (current)
	{
		// printf("%s\n",current->word);
		current=current->next;
		cnt++;
	}
	argv = malloc(sizeof(char *) * cnt);
	current = token;
	int i = 0;
	while (current)
	{
		argv[i] = strdup(current->word);
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{

		if (builtin_execute(argv, context))
		{
			return (0);
		}
        if(strchr(line, '/') == NULL)
        {
            tmp = line;
            line = make_path(argv[0]);
            free(tmp);
            execve(line, argv, environ);
        }
		// child process
		execve(line, argv, environ);
		fatal_error("execve");
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
    return (0);
}
