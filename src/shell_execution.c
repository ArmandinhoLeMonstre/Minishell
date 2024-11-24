/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:22:56 by armitite          #+#    #+#             */
/*   Updated: 2024/11/24 15:52:16 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_outfile_number(t_pipe_chain *exec_nodes)
{
	int	i;
	int	j;
	
	i = 0;
	j = stack_len(exec_nodes);
	while (i < j)
	{
		i++;
		if (exec_nodes->outfile != 0 || exec_nodes->append != 0)
			return (i);
		exec_nodes = exec_nodes->next;
	}
	return (-5);
}

void	while_loop2(t_pipe_chain *exec_nodes, int fd[2])
{
	int pid;
	
	//t_env	*env;
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		 if (ft_isbuiltin(exec_nodes->cmd[0]) == 1)
        {
			exit(1);
        }
		if (exec_nodes->cmd_path == NULL)
		{
			panic_parsing(exec_nodes, 1);
		}
		else
			pid_exec(exec_nodes, fd);
		exit(1);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

int	cmd_loop2(t_pipe_chain *exec_nodes)
{
	int	fd[2];
	
	t_env	*env;
	while (exec_nodes->next != NULL)
	{
		while_loop2(exec_nodes, fd);	
		exec_nodes = exec_nodes->next;
	}
	if (exec_nodes->cmd == NULL)
		exit(1);
	if (ft_isbuiltin(exec_nodes->cmd[0]) == 1)
	{
		ft_builtins(exec_nodes->cmd, &env, 0, 0);
		exit(1);
	}
	if (exec_nodes->cmd_path == NULL)
	{
		panic_parsing(exec_nodes, 1);
	}
	pid_exec_output(exec_nodes, fd);
	return (0);
}
int cmd_loop(t_pipe_chain *exec_nodes, int x)
{
	int	fd[2];
	int	j;

	j = get_outfile_number(exec_nodes);
	while (x < j - 1)
	{
		while_loop2(exec_nodes, fd);
		exec_nodes = exec_nodes->next;
		x++;
	}
	if (exec_nodes->cmd_path == NULL)
		panic_parsing(exec_nodes, 1);
	if (exec_nodes->checker == 2)
	{
		dup2(exec_nodes->outfile, 1);
		close(exec_nodes->outfile);
	}
	if (exec_nodes->checker == 3)
	{
		dup2(exec_nodes->append, 1);
		close(exec_nodes->append);
	}
	pid_exec_outfile(exec_nodes, fd);
	return (x);
}

int	shell_exec2(t_pipe_chain *exec_nodes, int j)
{
	int	x;
	int	pid;
	
	while (exec_nodes)
	{	
		j = get_outfile_number(exec_nodes);
		if (j > 0)
		{
			pid = fork();
			if (pid == -1)
				exit(1);
			x = 0;
			if (pid == 0)
			{
				cmd_loop(exec_nodes, 0);
			}
			while (x < j)
			{
				exec_nodes = exec_nodes->next;
				x++;
			}
		}
		else
		{
			cmd_loop2(exec_nodes);
		}
		j = 0;
	}
	return (0);
}
