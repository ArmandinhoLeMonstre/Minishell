/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:18:39 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 18:00:02 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	files_error(t_pipe_chain *checker_node, int c)
{
	if (c == 0)
	{
		ft_putstr_fd(checker_node->last_infile, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free_nodes(&checker_node);
		exit(1);
	}
}

int	panic_parsing(t_pipe_chain *node, int error_code)
{
	if (error_code == -1)
		return (free_nodes(&node), exit(1), 2);
	if (error_code == 0)
	{
		return (files_error(node, 0), 2);
	}
	if (error_code == 1)
	{
		if (node->cmd)
		{
			ft_putstr_fd(node->cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
		if (node != NULL)
			free_nodes(&node);
		return (exit(127), 2);
	}
	return (0);
}
