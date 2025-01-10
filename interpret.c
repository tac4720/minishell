#include "minishell.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

int	interpret(char *line, t_context *context)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};
    char        *tmp;
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{

		if (builtin_execute(line, context))
		{
			return (0);
		}
        if(strchr(line, '/') == NULL)
        {
            tmp = line;
            line = make_path(line);
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
