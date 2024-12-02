/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:01:45 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 09:08:00 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_space34(char *rl, t_change_space_data *data)
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

int	change_space39(char *rl, t_change_space_data *data)
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

char	*change_space(char *rl)
{
	t_change_space_data	data;

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

void	while_space(t_pipe_chain *checker_node, int j)
{
	int	x;

	x = 0;
	while (x < j)
	{
		if (space_numbers(checker_node->pipe_string) > 0)
		{
			checker_node->pipe_string = change_space(checker_node->pipe_string);
		}
		checker_node = checker_node->next;
		x++;
	}
}
