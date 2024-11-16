/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_executions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:27:17 by armitite          #+#    #+#             */
/*   Updated: 2024/11/16 15:03:40 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_exec_output(t_pipe_chain *exec_nodes, int fd[2])
{
	int	std_out = dup(1);
	
	dup2(std_out, 1);
	//fd[0] = 0;
	if (exec_nodes->infile != 0)
	{
		if (exec_nodes->cmd[1] != NULL) //&& exec_nodes->cmd[1][0] == '-')
		{//write(1, "je test\n", 7);
			if (exec_nodes->infile == -1)
				panic_parsing(exec_nodes, 0);
			dup2(exec_nodes->infile, 0);
			// close(fd[0]);
			// close(fd[1]);
			execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
		}
		if (exec_nodes->cmd[1] == NULL)
		{
			if (exec_nodes->infile == -1)
				panic_parsing(exec_nodes, 0);
			dup2(exec_nodes->infile, 0);
			// close(fd[0]);
			// close(fd[1]);
			execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
		}
	}
	else
	{
		// close(fd[0]);
		// close(fd[1]);
		if (ft_strlen(exec_nodes->heredoc_chars) > 0)
		{
			//write(1, "ds le strlen\n", 10);
			write(2, "salav\n", 6);
			dup2(exec_nodes->fd[0], 0);
			close(exec_nodes->fd[0]);
			close(exec_nodes->fd[1]);
		}
		if (exec_nodes->prev != NULL)
		{
			if (exec_nodes->prev->outfile != 0)
			{
				ft_putendl_fd("outfile roor ?", 2);
				//ft_putendl_fd("\0", fd[1]);
				if (pipe(fd) == -1)
					exit(1);
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
			}
		}
		//write(2, "je test8\n", 9);
		//printf("le fd : %d\n", exec_nodes->fd[0]);
		// if (exec_nodes->prev != NULL)
		// 	dup2(fd[0], 0);
		//write(1, "au h\n", 5);
		// if (exec_nodes->cmd_path == NULL)
		// {
		// 	return (ft_putstr_fd(exec_nodes->cmd[0], 2),
		// 		ft_putendl_fd(": command not found", 2));
		// 	//ft_free2(allpaths));
		// 	exit(1);
		// }
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
	close(fd[0]); // a supp
}

void	pid_exec_outfile(t_pipe_chain *exec_nodes, int fd[2])
{
	
	if (exec_nodes->infile != 0 && exec_nodes->cmd[1] == NULL)
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
		// close(fd[0]);
	 	// close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
	if (exec_nodes->infile == 0)
	{	
		printf("%s\n", exec_nodes->cmd_string);
		write(1, "ds pas infile du outfile\n", 25);
		if (exec_nodes->checker == 2)
		{
			dup2(exec_nodes->outfile, 1);
			//close(exec_nodes->outfile);
		}
		if (exec_nodes->checker == 3)
			dup2(exec_nodes->append, 1);
		if (ft_strlen(exec_nodes->heredoc_chars) > 0)
		{
			//close(fd[0]);
			//write(1, "ds le strlen\n", 10);
			dup2(exec_nodes->fd[0], 0);
			close(exec_nodes->fd[0]);
			close(exec_nodes->fd[1]);
		}
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		//close(fd[0]);
		//close(fd[1]);
		if (execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp) == -1)
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
}

void	pid_exec(t_pipe_chain *exec_nodes, int fd[2])
{
	if (exec_nodes->infile != 0 && exec_nodes->cmd[1] == NULL)
	{
		if (exec_nodes->infile == -1)
			panic_parsing(exec_nodes, 0);
		dup2(exec_nodes->infile, 0);
		dup2(fd[1], 1);
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		// close(fd[0]);
	 	// close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
	if (exec_nodes->infile == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		if (ft_strlen(exec_nodes->heredoc_chars) > 0)
		{
			//close(fd[0]);
			//write(1, "ds le strlen\n", 10);
			write(2, "salab\n", 6);
			dup2(exec_nodes->fd[0], 0);
			close(exec_nodes->fd[1]);
			close(exec_nodes->fd[0]);
		}
		// close(exec_nodes->outfile);
		// close(exec_nodes->infile);
		// close(fd[0]);
		// close(fd[1]);
		execve(exec_nodes->cmd_path, exec_nodes->cmd, exec_nodes->envp);
	}
}