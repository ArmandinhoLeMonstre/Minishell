/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:53:04 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 19:26:00 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_check(t_pipe_chain *checker_node, int h, int j, int redirect)
{
	if (redirect == 1)
		return (stock_file(checker_node, h, j, 1), 1);
	if (redirect == 2)
		return (stock_file(checker_node, h, j, 2), 1);
	if (redirect == 3)
		return (stock_file(checker_node, h, j, 3), 1);
	if (redirect == 4)
		return (stock_file(checker_node, h, j, 4), 1);
	return (0);
}

int	get_len_file(t_pipe_chain *checker_node, int *i)
{
	int	j;

	j = 0;
	while (checker_node->pipe_string[*i]
		&& checker_node->pipe_string[*i] != ' ')
	{
		if (checker_node->pipe_string[*i] == 34
			|| checker_node->pipe_string[*i] == 39)
		{
			(*i)++;
			break ;
		}
		if (ft_is_bash_char(checker_node->pipe_string[*i]))
		{
			(*i)--;
			break ;
		}
		j++;
		(*i)++;
	}
	return (j);
}

int	file_check(t_pipe_chain *checker_node, int *i, int h, int redirect)
{
	int	j;

	j = 0;
	(*i)++;
	while (checker_node->pipe_string[*i] == ' ')
		(*i)++;
	if (checker_node->pipe_string[*i] == 34
		|| checker_node->pipe_string[*i] == 39)
		(*i)++;
	j = get_len_file(checker_node, i);
	redirect_check(checker_node, h, j, redirect);
	return (0);
}
