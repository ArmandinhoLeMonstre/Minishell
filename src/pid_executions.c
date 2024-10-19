/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_executions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:27:17 by armitite          #+#    #+#             */
/*   Updated: 2024/10/16 14:32:09 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_exec_output(t_pipe_chain *exec_nodes, int fd[2])
{
	int	std_out = dup(1);
	
	dup2(std_out, 1);
	if (exec_nodes->infile == 0)
	{
		close(fd[0]);
		close(fd[1]);
		// if (exec_nodes->cmd_path == NULL)
		// {
		// 	return (ft_putstr_fd(exec_nodes->cmd[0], 2),
		// 		ft_putendl_fd(": command not found", 2));
		// 	//ft_free2(allpaths));
		// 	exit(1);
		// }
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
	if (exec_nodes->infile != 0)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		close(fd[0]);
	 	close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
}

void	pid_exec_outfile(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->infile == 0)
	{
		if (exec_nodes->checker == 2)
			dup2(exec_nodes->outfile, 1);
		if (exec_nodes->checker == 3)
			dup2(exec_nodes->append, 1);
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		close(fd[0]);
		close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
	if (exec_nodes->infile != 0)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		if (exec_nodes->checker == 2)
			dup2(exec_nodes->outfile, 1);
		if (exec_nodes->checker == 3)
			dup2(exec_nodes->append, 1);
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		close(fd[0]);
	 	close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
}

void	pid_exec(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->infile == 0)
	{
		dup2(fd[1], 1);
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		close(fd[0]);
		close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
	if (exec_nodes->infile != 0)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		dup2(fd[1], 1);
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		close(fd[0]);
	 	close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
}