/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:01:45 by armitite          #+#    #+#             */
/*   Updated: 2024/11/18 11:11:16 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_space_number(const char *rl, int *i, int *nbr)
{
		if (rl[*i] == 39)
		{
			(*i)++;
			while (rl[*i] != 39)
			{
				if (rl[*i] == ' ')
					(*nbr)++;
				(*i)++;
			}
		}
		if (rl[*i] == 34)
		{
			(*i)++;
			while (rl[*i] != 34)
			{
				if (rl[*i] == ' ')
					(*nbr)++;
				(*i)++;
			}
		}
}

int	space_numbers(const char *rl)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (rl[i])
	{
		if (rl[i] == 39 || rl[i] == 34)
			get_space_number(rl, &i, &nbr);
		i++;
	}
	return (nbr);
}

int change_space34(char *rl, t_change_space_data *data)
{
	data->rl2[data->i] = rl[data->i];
	data->i++;
	while (rl[data->i] != 34)
	{
		if (rl[data->i] == ' ')
		{
			data->rl2[data->i] = '\t';
			data->index++;
		}
		else
			data->rl2[data->i] = rl[data->i];
		data->i++;
	}
	return (data->i);
}

int change_space39(char *rl, t_change_space_data *data)
{
	data->rl2[data->i] = rl[data->i];
	data->i++;
	while (rl[data->i] != 39)
	{
		if (rl[data->i] == ' ')
		{
			data->rl2[data->i] = '\t';
			data->index++;
		}
		else
			data->rl2[data->i] = rl[data->i];
		data->i++;
	}
	return (data->i);
}

char *change_space(char *rl)
{
	t_change_space_data data;

	data.i = 0;
	data.index = 0;
	data.rl2 = malloc(sizeof(char) * (ft_strlen(rl) + 1));
	while (rl[data.i])
	{
		if (rl[data.i] == 34)
				change_space34(rl, &data);
		if (rl[data.i] == 39)
			change_space39(rl, &data);
		data.rl2[data.i] = rl[data.i];
		data.i++;
	}
	data.rl2[data.i] = '\0';
	return (data.rl2);
}

char	**ft_strdup3(char **cmd)
{
	int		index;
	int	i;
	int x;

	i = 0;
	index = 0;
	x = 0;
	while (cmd[x])
	{
		i = 0;
		while (cmd[x][i])
		{
			if (cmd[x][i] == '\t')
			{
				cmd[x][i] = ' ';
				index++;
			}
			else
				cmd[x][i] = cmd[x][i];
			i++;
		}
		x++;
	}
	return (cmd);
}
