/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:22:56 by armitite          #+#    #+#             */
/*   Updated: 2024/11/20 16:16:55 by armitite         ###   ########.fr       */
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

int cmd_loop(t_pipe_chain *exec_nodes)
{
	int	pid;
	int	fd[2];
	int	x;
	int	j;

	x = 0;
	j = get_outfile_number(exec_nodes);
	while (x < j - 1)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			if (exec_nodes->cmd_path == NULL)
			{
				if (exec_nodes->infile != 0)
					close(exec_nodes->infile);
				return (free_nodes(&exec_nodes), exit(1), 2);
			}
			pid_exec(exec_nodes, fd);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);	
		}
		exec_nodes = exec_nodes->next;
		x++;
	}
	if (exec_nodes->cmd_path == NULL)
	{
		if (exec_nodes->infile != 0)
			close(exec_nodes->infile);
		if (exec_nodes->outfile != 0)
		{
			close(exec_nodes->outfile);
			free(exec_nodes->last_outfile);
		}
		return (free(exec_nodes->cmd_string), ft_free2(exec_nodes->cmd), 
					free(exec_nodes->heredoc_chars), free(exec_nodes->pipe_string), 
						free_nodes(&exec_nodes), exit(1), 2);
	}
	pid_exec_outfile(exec_nodes, fd);
	return (x);
}

int	cmd_loop2(t_pipe_chain *exec_nodes)
{
	int	pid;
	int	fd[2];
	int	x;

	x = 0;
	while (exec_nodes->next != NULL)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			if (exec_nodes->cmd_path == NULL)
			{
				if (exec_nodes->infile != 0)
				{
					close(exec_nodes->infile);
					free(exec_nodes->last_infile);
				}
				return (free(exec_nodes->cmd_string), ft_free2(exec_nodes->cmd), 
							free(exec_nodes->heredoc_chars), free(exec_nodes->pipe_string), 
								free_nodes(&exec_nodes), exit(1), 2);
			}
			pid_exec(exec_nodes, fd);
			exit(1);
		}
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);	
		exec_nodes = exec_nodes->next;
		x++;
	}
	if (exec_nodes->cmd_path == NULL)
	{
		if (exec_nodes->infile != 0)
		{
			close(exec_nodes->infile);
			free(exec_nodes->last_infile);
		}
		return (free(exec_nodes->cmd_string), ft_free2(exec_nodes->cmd), 
					free(exec_nodes->heredoc_chars), free(exec_nodes->pipe_string), 
						free_nodes(&exec_nodes), exit(1), 2);
	}
	pid_exec_output(exec_nodes, fd);
	return (x);
}

int	shell_exec2(t_pipe_chain *exec_nodes)
{
	int	x;
	int	j;
	int	pid;
	
	j = 0;
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
				cmd_loop(exec_nodes);
			while (x < j)
			{
				exec_nodes = exec_nodes->next;
				x++;
			}
		}
		else
			cmd_loop2(exec_nodes);
		j = 0;
	}
	return (0);
}
