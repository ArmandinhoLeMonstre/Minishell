/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:59 by armitite          #+#    #+#             */
/*   Updated: 2024/11/18 11:40:31 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollars(t_pipe_chain *checker_node, int i)
{
	i++;
	if (ft_strncmp(checker_node->pipe_string + i, "USER", 4) == 0)
		return (1);
	return (0);
}

int	commas34(t_pipe_chain *checker_node, int i, int *total, char *user)
{
	i++;
	(*total)++;
	while (checker_node->pipe_string[i] != 34)	
	{
		if (checker_node->pipe_string[i] == '$')
		{
			if (check_dollars(checker_node, i) == 1)
			{
				(*total) = (*total) + ft_strlen(user);							
				i = i + 4;
			}
			else
			{
				while (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != 34)
					i++;
				i--;
			}					
		}
		i++;
		(*total)++;
	}
	return (i);
}

void	expander(t_pipe_chain *checker_node)
{
	t_expander_data data;

	data.x = 0;
	data.total = 0;
	data.j = stack_len(checker_node);
	data.user = get_user(checker_node);
	while (data.x < data.j)
	{
		data.i = 0;
		data.verif = 0;
		while (checker_node->pipe_string[data.i])
		{
			if (checker_node->pipe_string[data.i] == 34)
				data.i = commas34(checker_node, data.i, &data.total, data.user);
			data.i++;
			data.total++;
		}
		checker_node->pipe_string = ft_strdup(clean_string(checker_node, data.total, data.user));
		checker_node = checker_node->next;
		data.x++;
	}
}
