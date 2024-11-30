/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/11/30 22:21:23 by armitite         ###   ########.fr       */
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

int empty_rl(char *rl)
{
    int i;

    i = 0;
    while (rl[i])
    {
        if (rl[i] != 32)
            return (0);
        else
            i++;
    }
    return (1);
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
        envp = build_env(&env);
        if (rl != NULL)
            token = ft_split(rl, ' ');
        else
            return (printf("exit\n"), exit(1), 2);
        if (ft_isbuiltin(token[0]) == 1 && ft_ispipe(rl) == 0)
            ft_builtins(token, &env, 0, 0);
        else
        {
            if (quote_checker(rl) == 0 && check_unavaible_chars(rl) == 0 && empty_rl(rl) == 0)
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
                    if (stack != NULL)
                    {
                        if (stack->infile != 0)
                        {
                            close(stack->infile);
                            free(stack->last_infile);
                        }
                        if (stack->outfile != 0)
                        {
                            close(stack->outfile);
                            free(stack->last_outfile);
                        }
                        if (stack->append != 0)
                        {
                            close(stack->append);
                            free(stack->last_append);
                        }
                        if (stack->cmd_string != NULL)
                            free(stack->cmd_string);
                        if (stack->cmd_path != NULL)
                            free(stack->cmd_path);
                        if (stack->cmd != NULL)
                            ft_free2(stack->cmd);
                        if (stack->heredoc_chars != NULL)
			                free(stack->heredoc_chars);
                        if (stack->pipe_string != NULL)
                            free(stack->pipe_string);
                        if (stack != NULL)
			                free_nodes(&stack);
                    }
                }
            }
        }
        add_history(rl);
        if (rl != NULL)
            free(rl);
        if (token != NULL)
            ft_free2(token);
        if (envp != NULL)
            ft_free2(envp);
        system("leaks minishell");
    }
    return (0);
}

