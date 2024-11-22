/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:18:39 by armitite          #+#    #+#             */
/*   Updated: 2024/11/22 21:02:42 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	panic_parsing(t_pipe_chain *node, int error_code)
{
	if (error_code == -1)
		return (free_nodes(&node), exit(1), 2);
	if (error_code == 0)
	{
		if (node->outfile != 0)
		{
			close(node->outfile);
			free(node->last_outfile);
		}
		if (node->append != 0)
		{
			close(node->append);
			free(node->last_append);
		}
		return (free(node->cmd_string), ft_free2(node->cmd),
			free(node->heredoc_chars), free(node->pipe_string),
			files_error(node, 0), 2);
	}
	if (error_code == 1)
	{
		ft_putstr_fd(node->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		if (node->infile != 0)
			close(node->infile);
		if (node->outfile != 0)
		{
			close(node->outfile);
			free(node->last_outfile);
		}
		if (node->append != 0)
		{
			close(node->append);
			free(node->last_append);
		}
		return (free(node->cmd_string), ft_free2(node->cmd),
			free(node->heredoc_chars), free(node->pipe_string),
			free_nodes(&node), exit(1), 2);
	}
	return (0);
}
