/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:57 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 19:14:36 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exitcode;

int first_check(char *rl, t_env	*env)
{
    char    **token;

    token = NULL;
    if (rl != NULL)
        token = ft_split(rl, ' ');
    else
        return (printf("exit\n"), exit(1), 2);
    if (ft_isbuiltin(token[0]) == 1 && ft_ispipe(rl) == 0)
        ft_builtins(token, &env, 0, 0);
    if (token != NULL)
        ft_free2(token);
    return (0);
}

int main_checks_ok(t_pipe_chain	*stack, t_env *env, char *rl, char **envp)
{
    int     pid;
    int     status;
    
    status = 0;
    if (pipe_noding(&stack, &env, rl, envp) != 2)
    {    
        pid = fork();
        signal(SIGINT, ft_exec_sig_handler);
        signal(SIGQUIT, ft_exec_sig_handler);
        if (pid == -1)
            exit(1);
        if (pid == 0)
        {
            cmd_loop2_bis(stack);
        }
        waitpid(pid, &status, 0);
        if (g_exitcode == 0)
            g_exitcode = status / 256;
        if (stack != NULL)
        {
            free_nodes(&stack);
        }
    }
    return (0);
}

int	main(int ac, char **av, char **envp)
{
    char    *rl;
    t_env	*env;
    t_pipe_chain	*stack;

	env = make_envlist(envp);
    if (av || ac)
        printf("Starting the prompt !\n");
    while (1)
    {
        stack = NULL;
        signal(SIGINT, ft_main_sig_handler);
		signal(SIGQUIT, SIG_IGN);
        rl = readline("Prompt > ");
        envp = build_env(&env);
        first_check(rl, env);
        if (quote_checker(rl) == 0 && check_unavaible_chars(rl) == 0 && empty_rl(rl) == 0)
            main_checks_ok(stack, env, rl, envp);
        add_history(rl);
        if (rl != NULL)
            free(rl);
        if (envp != NULL)
            ft_free2(envp);
    }
    return (0);
}
