/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/23 17:44:52 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(char *str)
{
    int i;
    
    i = 0;
    if (!str)
        return (0);
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
    token = NULL;
    if (av || ac)
        printf("Starting the prompt !\n");
    while (1)
    {
        signal(SIGINT, ft_main_sig_handler);
		signal(SIGQUIT, SIG_IGN);
        rl = readline("Prompt > ");
        if (rl != NULL)
            token = ft_split(rl, ' ');
        else
            return (printf("exit\n"), exit(1), 2);
        if (ft_isbuiltin(token[0]) == 1 && ft_ispipe(rl) == 0)
            ft_builtins(token, &env, 0, 0);
        else
        {
            envp = build_env(&env);
            pid = fork();
            if (pid == -1)
                exit(1);
            if (pid == 0)
            {
                if (quote_checker(rl) != 0)
                    return (exit(1), 2);
                pipe_noding(rl, envp);
            }
            wait(0);
            if (rl != NULL)
                free(rl);
            if (token != NULL)
                ft_free2(token);
        }
    }
    return (0);
}

