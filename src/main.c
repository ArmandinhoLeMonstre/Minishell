/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/18 13:02:24 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
	    if (str[i] == '|')
	    	return (1);
        i++;
    }
	return (0);
}

int	main(int ac, char **av, char **envp)
{
    char    *rl;
    int     pid;

    if (av || ac)
        printf("a");
    while (1)
    {
        rl = readline("Prompt > ");  // Initialisation correcte de rl avant son utilisation
        pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
            if (quote_checker(rl) == 0)
                printf("ok quote\n");
            else
                exit(1);
            pipe_noding(rl, envp);
            printf("%s\n", rl);
        }
        wait(0);
        free(rl);  // Libère le dernier rl avant de sortir de la boucle
    }
    return (0);
}

