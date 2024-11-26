/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/26 20:56:53 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exitcode;

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

int check_unavaible_chars(char *rl)
{
    if (ft_strchr(rl, ';') != 0)
        return (printf("';' is not a valid char\n"), 1);
    if (ft_strchr(rl, '\\') != 0)
        return (printf("'\\' is not a valid char\n"), 1);
    return (0);
}

int	main(int ac, char **av, char **envp)
{
    char    *rl;
    int     pid;
    t_env	*env;
    t_pipe_chain	*stack;
    char    **token;
    int status;
 
    
    status = 0;
	env = make_envlist(envp);
    if (av || ac)
        printf("Starting the prompt !\n");
    while (1)
    {
        token = NULL;
        stack = NULL;
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
            if (quote_checker(rl) == 0 && check_unavaible_chars(rl) == 0)
            {
                if (pipe_noding(&stack, &env, rl, envp) != 2)
                {    
                    pid = fork();
                    if (pid == -1)
                        exit(1);
                    if (pid == 0)
                    {
                        shell_exec2(&stack, 0);
                    }
                    waitpid(pid, &status, 0);
                    if (g_exitcode == 0)
                        g_exitcode = status / 256;
                    wait(0);
                }
            }
        }
        add_history(rl);
        if (rl != NULL)
            free(rl);
        if (token != NULL)
            ft_free2(token);
    }
    return (0);
}

