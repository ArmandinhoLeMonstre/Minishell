/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in_commas_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:33:43 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 19:21:11 by armitite         ###   ########.fr       */
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
	return (data.rl2);
}
