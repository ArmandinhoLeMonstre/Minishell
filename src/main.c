/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/22 20:17:41 by armitite         ###   ########.fr       */
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

// void handle_sigint(int sig) {
//     if (sig)
//         printf("a");
//     if (isatty(STDIN_FILENO)) {
//         // Print a new prompt line when Ctrl-C is pressed
//         printf("\nPrompt > ");
//         fflush(stdout);
//     }
// }

// // Signal handler for Ctrl-D (EOF, SIGTERM in this context)
// void handle_eof(int sig) {
//     if (sig)
//         printf("a");
//     if (isatty(STDIN_FILENO)) {
//         // Exit the shell when Ctrl-D is pressed
//         printf("\nExiting shell...\n");
//         exit(0);
//     }
// }

int	main(int ac, char **av, char **envp)
{
    char    *rl;
    int     pid;
    t_env	*env;
    char    **token;
 
    
	env = make_envlist(envp);
    if (av || ac)
        printf("Starting the prompt !\n");
    while (1)
    {
        rl = readline("Prompt > ");
        // signal(SIGINT, ft_main_sig_handler);
		// signal(SIGQUIT, SIG_IGN);
        token = ft_split(rl, ' ');
        if (ft_isbuiltin(token[0]) == 1 && ft_ispipe(rl) == 0)
        {
            //cd(token);
            ft_builtins(token, &env, 0, 0);
        }
        else
        {
            //ft_free2(token);
            envp = build_env(&env);
            pid = fork();
            if (pid == -1)
                exit(1);
            if (pid == 0)
            {
                if (quote_checker(rl) != 0)
                    return (printf("Error quotes\n"), exit(1), 2);
                pipe_noding(rl, envp);
                //printf("%s\n", rl);
            }
            wait(0);
            free(rl);
            ft_free2(token);
        }
    }
    return (0);
}

