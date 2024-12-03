/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:45:10 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 09:40:40 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_exec_inredirect2(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->prev->outfile != 0 || exec_nodes->prev->append != 0)
	{
		if (exec_nodes->checker_in_here != 2
			&& exec_nodes->checker_in_here != 1)
		{
			if (pipe(fd) == -1)
				exit(1);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
	}
}

void	pid_exec_inredirect(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->checker_in_here == 1)
	{
		if (ft_strlen(exec_nodes->heredoc_chars) > 0)
		{
			dup2(exec_nodes->fd[0], 0);
			close(exec_nodes->fd[1]);
			close(exec_nodes->fd[0]);
		}
	}
	if (exec_nodes->checker_in_here == 2)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		close(exec_nodes->infile);
	}
	if (exec_nodes->prev != NULL)
	{
		pid_exec_inredirect2(exec_nodes, fd);
	}
}

void	pid_exec_bis(t_pipe_chain *exec_nodes, int fd[2])
{
	pid_exec_inredirect(exec_nodes, fd);
	if (exec_nodes->next != NULL
		&& (exec_nodes->checker != 3 && exec_nodes->checker != 2))
		dup2(fd[1], 1);
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
	if (exec_nodes->next != NULL && exec_nodes->prev != NULL)
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

void	while_loop2_bis(t_pipe_chain *exec_nodes, int fd[2])
{
	int	pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close (fd[0]);
		if (exec_nodes->cmd != NULL)
		{
			if (ft_isbuiltin(exec_nodes->cmd[0]) == 1)
				exit(0);
		}
		if (exec_nodes->cmd_path == NULL)
			panic_parsing(exec_nodes, 1);
		else
			pid_exec_bis(exec_nodes, fd);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

int	cmd_loop2_bis(t_pipe_chain *exec_nodes)
{
	int	fd[2];

	while (exec_nodes->next != NULL)
	{
		while_loop2_bis(exec_nodes, fd);
		exec_nodes = exec_nodes->next;
	}
	if (ft_strncmp(exec_nodes->cmd[0], "echo", INT_MAX) == 0
		&& (exec_nodes->append == 0 && exec_nodes->outfile == 0))
	{
		return ((echo_built(exec_nodes->cmd), 0), exit(0), 0);
	}
	if (exec_nodes->cmd == NULL)
		exit(1);
	if (exec_nodes->cmd != NULL)
	{
		if (ft_isbuiltin(exec_nodes->cmd[0]) == 1)
			exit(0);
	}
	if (exec_nodes->cmd_path == NULL)
	{
		panic_parsing(exec_nodes, 1);
	}
	pid_exec_bis(exec_nodes, fd);
	return (0);
}
