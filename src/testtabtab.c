#include "../include/minishell.h"

int	main()
{
	char *test;
	char *test2;
	char *test3;
	char **split;

	test = ft_strdup("alo1");
	test2 = ft_strdup("alo2");
	test3 = ft_strdup("alo3");
	printf("%s\n", test);
	split = ft_calloc(sizeof(char *), 3);
	split[0] = ft_strdup(test);
	split[1] = ft_strdup(test2);
	split[2] = ft_strdup(test3);
	int i;
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	// split[3] = ft_strdup("test");
	// split[4] = 0;
	// i = 0;
	// while (split[i])
	// {
	// 	printf("%s\n", split[i]);
	// 	i++;
	// }
}