/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:18:39 by armitite          #+#    #+#             */
/*   Updated: 2024/11/30 19:18:15 by armitite         ###   ########.fr       */
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
		if (node->cmd_string != NULL)
			free(node->cmd_string);
		if (node->cmd_path != NULL)
			free(node->cmd_path);
		if (node->cmd != NULL)
			ft_free2(node->cmd);
		if (node->heredoc_chars != NULL)
			free(node->heredoc_chars);
		if (node->pipe_string != NULL)
			free(node->pipe_string);
		if (node != NULL)
			free_nodes(&node);
		return (files_error(node, 0), 2);
	}
	if (error_code == 1)
	{
		if (node->cmd)
		{
			ft_putstr_fd(node->cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
		if (node->infile != 0)
		{
			close(node->infile);
			free(node->last_infile);
		}
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
		if (node->cmd_string != NULL)
			free(node->cmd_string);
		if (node->cmd_path != NULL)
			free(node->cmd_path);
		if (node->cmd != NULL)
			ft_free2(node->cmd);
		if (node->heredoc_chars != NULL)
			free(node->heredoc_chars);
		if (node->pipe_string != NULL)
			free(node->pipe_string);
		if (node != NULL)
			free_nodes(&node);
		return (exit(127), 2);
	}
	return (0);
}
