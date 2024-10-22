#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	int	pid;
	(void)ac;

	pid = fork();
	if (pid == 0)
		execve("/bin/cat", &av[1], envp);
	wait(0);
}