/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in_commas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:14:28 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 16:40:15 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tab34(const char *rl, t_get_tab_data *data, int *tab)
{
	data->i++;
	while (rl[data->i] != 34)
	{
		if (rl[data->i] == '|')
		{
			tab[data->index] = data->i;
			data->index++;
		}
		data->i++;
	}
	return (data->i);
}

int	*get_tab(const char *rl, int *tab)
{
	t_get_tab_data	data;

	data.i = 0;
	data.index = 0;
	while (rl[data.i])
	{
		if (rl[data.i] == 39)
		{
			data.i++;
			while (rl[data.i] != 39)
			{
				if (rl[data.i] == '|')
				{
					tab[data.index] = data.i;
					data.index++;
				}
				data.i++;
			}
		}
		if (rl[data.i] == 34)
			get_tab34(rl, &data, tab);
		data.i++;
	}
	return (tab);
}

void	ft_strdup_utils(t_strdup2_data *data,
	t_pipe_chain *checker_node, int *tab)
{
	if (data->i + data->total == tab[data->index])
	{
		checker_node->pipe_string[data->i] = '|';
		data->index++;
	}
	else
		checker_node->pipe_string[data->i]
			= checker_node->pipe_string[data->i];
	data->i++;
}

char	*ft_strdup2(t_pipe_chain *checker_node, int *tab, int j)
{
	t_strdup2_data	data;

	data.total = 0;
	data.index = 0;
	data.x = 0;
	while (data.x < j)
	{
		data.i = 0;
		if (checker_node->prev != NULL)
			data.total = data.total
				+ ft_strlen(checker_node->prev->pipe_string) + 1;
		while (checker_node->pipe_string[data.i])
		{
			ft_strdup_utils(&data, checker_node, tab);
		}
		checker_node = checker_node->next;
		data.x++;
	}
	return (NULL);
}
