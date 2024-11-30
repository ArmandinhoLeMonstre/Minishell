/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:13:12 by armitite          #+#    #+#             */
/*   Updated: 2024/11/30 22:06:02 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stock_cmd_commas(t_pipe_chain *checker_node, int h, int j)
{
	int		x;
	char	*cmd_name;

	x = 0;
	cmd_name = malloc(sizeof(char) * (j + 1));
	while (j > 0)
	{
		cmd_name[x] = checker_node->pipe_string[h];
		h++;
		j--;
		x++;
	}
	cmd_name[x] = '\0';
	if (checker_node->cmd_string == NULL)
	{
		checker_node->cmd_string = ft_strdup(cmd_name);
		//checker_node->cmd_string = cmd_name;
	}
	else
	{
		checker_node->cmd_string = ft_strjoin(checker_node->cmd_string, " ");
		checker_node->cmd_string
			= ft_strjoin(checker_node->cmd_string, cmd_name);
	}
	free(cmd_name);
}

int	cmd_check_commas(t_pipe_chain *checker_node, int *i, int h, int keycode)
{
	int	j;

	j = 0;
	if (keycode == 1)
	{
		while (checker_node->pipe_string[*i] != 34)
		{
			j++;
			(*i)++;
		}
	}
	else
	{
		while (checker_node->pipe_string[*i] != 39)
		{
			j++;
			(*i)++;
		}
	}
	stock_cmd_commas(checker_node, h, j);
	return (1);
}
