/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_executions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:27:17 by armitite          #+#    #+#             */
/*   Updated: 2024/11/17 19:11:09 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	else_exec_output(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->prev != NULL)
	{
		if (exec_nodes->prev->outfile != 0 || exec_nodes->prev->append != 0)
		{
			if (pipe(fd) == -1)
				exit(1);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
	}
	if (ft_strlen(exec_nodes->heredoc_chars) > 0)
	{
		dup2(exec_nodes->fd[0], 0);
		close(exec_nodes->fd[0]);
		close(exec_nodes->fd[1]);
	}
	if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
	{
		free_nodes(&exec_nodes);
		exit(1);
	}
}

void	pid_exec_output(t_pipe_chain *exec_nodes, int fd[2])
{
	int	std_out;
	
	std_out = dup(1);
	dup2(std_out, 1);
	if (exec_nodes->infile != 0)
	{
			if (exec_nodes->infile == -1)
				panic_parsing(exec_nodes, 0);
			dup2(exec_nodes->infile, 0);
			if (exec_nodes->prev && (exec_nodes->outfile == 0 && exec_nodes->append == 0))
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
			{
				free_nodes(&exec_nodes);
				exit(1);
			}
	}
	else
		else_exec_output(exec_nodes, fd);
}

void	else_exec_outfile(t_pipe_chain *exec_nodes, int fd[2])
{
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
	if (ft_strlen(exec_nodes->heredoc_chars) > 0)
	{
		dup2(exec_nodes->fd[0], 0);
		close(exec_nodes->fd[0]);
		close(exec_nodes->fd[1]);
	}
	close(fd[0]);
	close(fd[1]);
	if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
	{
		free_nodes(&exec_nodes);
		exit(1);
	}
}

void	pid_exec_outfile(t_pipe_chain *exec_nodes, int fd[2])
{
	
	if (exec_nodes->infile != 0)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		close(exec_nodes->infile);
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
		close(fd[0]);
	 	close(fd[1]);
		if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
		{
			free_nodes(&exec_nodes);
			exit(1);
		}
	}
	if (exec_nodes->infile == 0)
		else_exec_outfile(exec_nodes, fd);
}

void	pid_exec(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->infile != 0)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		close(exec_nodes->infile);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
		{
			free_nodes(&exec_nodes);
			exit(1);
		}
	}
	if (exec_nodes->infile == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		if (ft_strlen(exec_nodes->heredoc_chars) > 0)
		{
			dup2(exec_nodes->fd[0], 0);
			close(exec_nodes->fd[1]);
			close(exec_nodes->fd[0]);
		}
		if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
		{
			free_nodes(&exec_nodes);
			exit(1);
		}
	}
}
