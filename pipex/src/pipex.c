#include "pipex.h"

void	parent_process(int *p, char **argv, char **envp)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	dup2(p[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(p[1]);
	ft_execvp(argv[3], envp);
}

void	child_process(int *p, char **argv, char **envp)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	dup2(p[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(p[0]);
	ft_execvp(argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: <input> <cmd1> <cmd2> <output>\n", 2);
		return (EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		child_process(fd, argv, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
	}
	return (EXIT_SUCCESS);
}
