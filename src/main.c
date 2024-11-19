/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/19 18:29:42 by armitite         ###   ########.fr       */
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
    char    **token;

    if (av || ac)
        printf("Starting the prompt !\n");
    while (1)
    {
        rl = readline("Prompt > ");
        token = ft_split(rl, ' ');
        if (ft_isbuiltin(token[0]) == 1)
        {
            printf("ici");
            cd(token);
        }
        else
        {
            pid = fork();
            if (pid == -1)
                exit(1);
            if (pid == 0)
            {
                if (quote_checker(rl) != 0)
                    return (printf("Error quotes\n"), exit(1), 2);
                pipe_noding(rl, envp);
                printf("%s\n", rl);
            }
            wait(0);
            free(rl);
        }
    }
    return (0);
}

