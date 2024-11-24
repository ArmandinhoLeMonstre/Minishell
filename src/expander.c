/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:59 by armitite          #+#    #+#             */
/*   Updated: 2024/11/24 16:41:30 by armitite         ###   ########.fr       */
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
				while (checker_node->pipe_string[i] != ' '
					&& checker_node->pipe_string[i] != 34)
					i++;
				i--;
			}
		}
		i++;
		(*total)++;
	}
	return (i);
}

void	parse_string_expander(t_pipe_chain *checker_node, t_expander_data *data)
{
	while (checker_node->pipe_string[data->i])
	{
		if (checker_node->pipe_string[data->i] == '$')
		{
			if (checker_node->pipe_string[data->i + 1] == '?')
			{
				data->i++;
				data->total++;
			}
			else if (check_dollars(checker_node, data->i) == 1)
			{
				data->total = data->total + ft_strlen(data->user);
				data->i = data->i + 4;
			}
			else
			{
				while (checker_node->pipe_string[data->i] != ' '
					&& checker_node->pipe_string[data->i] != 34)
					data->i++;
				data->i--;
			}
		}
		if (checker_node->pipe_string[data->i] == 34)
			data->i = commas34(checker_node, data->i, &data->total, data->user);
		data->i++;
		data->total++;
	}
}

void	expander(t_pipe_chain *checker_node)
{
	t_expander_data	data;

	data.x = 0;
	data.total = 0;
	data.j = stack_len(checker_node);
	data.user = get_user(checker_node);
	printf("la taille : %ld\n", ft_strlen(checker_node->pipe_string));
	while (data.x < data.j)
	{
		data.i = 0;
		data.verif = 0;
		parse_string_expander(checker_node, &data);
		clean_string(checker_node, data.total, data.user);
		checker_node = checker_node->next;
		data.x++;
	}
	free(data.user);
}
