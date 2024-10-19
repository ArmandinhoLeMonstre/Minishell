#include "minishell.h"

int	main(int ac, char **av)
{

	if (execve(filename1, av1, envp) == -1)
	{
		printf("error\n");
	}
}