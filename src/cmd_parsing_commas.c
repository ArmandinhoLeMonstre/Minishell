/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:13:12 by armitite          #+#    #+#             */
/*   Updated: 2024/11/15 17:12:39 by armitite         ###   ########.fr       */
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
		printf("%c char de la cmd\n", cmd_name[x]);
		h++;
		j--;
		x++;
	}
	printf(("la cmd %s\n"), cmd_name);
	printf(("la cmd %d\n"), h);
	cmd_name[x] = '\0';
	if (checker_node->cmd_string == NULL)
	{
		checker_node->cmd_string = ft_strdup(cmd_name);
	}
	else
		checker_node->cmd_string = ft_strjoin(checker_node->cmd_string, cmd_name);
}

int	cmd_check_commas(t_pipe_chain *checker_node, int *i, int h, int	keycode)
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
	printf("le j commas : %d\n", j);
	stock_cmd_commas(checker_node, h, j);
	return (1);
}