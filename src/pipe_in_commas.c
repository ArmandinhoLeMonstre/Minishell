/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in_commas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:14:28 by armitite          #+#    #+#             */
/*   Updated: 2024/11/22 21:05:31 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pipe_number(const char *rl, int *i, int *nbr)
{
	if (rl[*i] == 39)
	{
		(*i)++;
		while (rl[*i] != 39)
		{
			if (rl[*i] == '|')
				(*nbr)++;
			(*i)++;
		}
	}
	if (rl[*i] == 34)
	{
		(*i)++;
		while (rl[*i] != 34)
		{
			if (rl[*i] == '|')
				(*nbr)++;
			(*i)++;
		}
	}
}

int	pipe_numbers(const char *rl)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (rl[i])
	{
		if (rl[i] == 39 || rl[i] == 34)
			get_pipe_number(rl, &i, &nbr);
		i++;
	}
	return (nbr);
}

int	change_pipe34(char *rl, t_change_pipe_data *data, int *tab)
{
	data->rl2[data->i] = rl[data->i];
	data->i++;
	while (rl[data->i] != 34)
	{
		if (rl[data->i] == '|')
		{
			data->rl2[data->i] = 'a';
			tab[data->index] = data->i;
			data->index++;
		}
		else
			data->rl2[data->i] = rl[data->i];
		data->i++;
	}
	return (data->i);
}
int	change_pipe39(char *rl, t_change_pipe_data *data, int *tab)
{
	data->rl2[data->i] = rl[data->i];
	data->i++;
	while (rl[data->i] != 39)
	{
		if (rl[data->i] == '|')
		{
			data->rl2[data->i] = 'a';
			tab[data->index] = data->i;
			data->index++;
		}
		else
			data->rl2[data->i] = rl[data->i];
		data->i++;
	}
	return (data->i);
}

char	*change_pipe(char *rl, int *tab)
{
	t_change_pipe_data	data;

	data.i = 0;
	data.index = 0;
	data.rl2 = malloc(sizeof(char) * (ft_strlen(rl) + 1));
	while (rl[data.i])
	{
		if (rl[data.i] == 34)
		{
			change_pipe34(rl, &data, tab);
		}
		if (rl[data.i] == 39)
		{
			change_pipe39(rl, &data, tab);
		}
		data.rl2[data.i] = rl[data.i];
		data.i++;
	}
	data.rl2[data.i] = '\0';
	printf("la string ds change pipe %s\n", data.rl2);
	return (data.rl2);
}

int get_tab34(const char *rl, t_get_tab_data *data, int *tab)
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

int *get_tab(const char *rl, int *tab)
{
	t_get_tab_data data;

	data.i = 0;
	data.index = 0;
	while (rl[data.i])
	{
		if (rl[data.i] == 39)
			get_tab34(rl, &data, tab);
		if (rl[data.i] == 34)
		{
			data.i++;
			while (rl[data.i] != 34)
			{
				if (rl[data.i] == '|')
				{
					tab[data.index] = data.i;
					data.index++;
				}
				data.i++;
			}
		}
		data.i++;
	}
	return (tab);
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
			if (data.i + data.total == tab[data.index])
			{
				checker_node->pipe_string[data.i] = '|';
				data.index++;
			}
			else
				checker_node->pipe_string[data.i]
					= checker_node->pipe_string[data.i];
			data.i++;
		}
		checker_node = checker_node->next;
		data.x++;
	}
	return (NULL);
}