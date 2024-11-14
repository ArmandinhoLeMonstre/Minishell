/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/14 12:01:25 by armitite         ###   ########.fr       */
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

    printf("%s\n", envp[1]);
    printf("%s\n", av[1]);
    printf("%d\n", ac);

    while (1)
    {
        rl = readline ("Prompt > ");  // Initialisation correcte de rl avant son utilisation
        // if (quote_checker(rl) == 0)
        //     printf("ok quote");
        // else
        //     exit(1);
        // while (ft_strncmp(rl, "exit", 5) != 0)
        // {
            //if (ft_ispipe(rl) != 0)
        // if (ft_strncmp(rl, "exit", 5) != 0)
        //     exit(1);
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
        //     free(rl);  // N'oublie pas de libérer la mémoire allouée par readline
        //     rl = readline ("Prompt > ");  // Nouvelle saisie utilisateur
        // }
        free(rl);  // Libère le dernier rl avant de sortir de la boucle
    }
    return (0);
}
