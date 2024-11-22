/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:51 by armitite          #+#    #+#             */
/*   Updated: 2024/11/22 20:57:57 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_string34(t_pipe_chain *checker_node,
	t_clean_string_data *data, int *total, char *user)
{
	data->string2[(*total)] = checker_node->pipe_string[data->i];
	(*total)++;
	data->i++;
	while (checker_node->pipe_string[data->i] != 34)
	{
		if (checker_node->pipe_string[data->i] == '$')
		{
			if (check_dollars(checker_node, data->i) == 1)
			{
				data->h = 0;
				while (user[data->h])
					data->string2[(*total)++] = user[data->h++];
				data->i = data->i + 5;
			}
			else
			{
				while (checker_node->pipe_string[data->i] != ' '
					&& checker_node->pipe_string[data->i] != 34)
					data->i++;
			}
		}
		if (checker_node->pipe_string[data->i] != 34)
		{
			data->string2[(*total)++] = checker_node->pipe_string[data->i++];
		}
	}
}

void	if_verif(t_pipe_chain *checker_node, t_clean_string_data *data,
	int *total, char *user)
{
	if (checker_node->pipe_string[data->i] == 34)
		clean_string34(checker_node, data, total, user);
	if (checker_node->pipe_string[data->i] == '$')
	{
		if (check_dollars(checker_node, data->i) == 1)
		{
			data->h = 0;
			while (user[data->h])
				data->string2[(*total)++] = user[data->h++];
			data->i = data->i + 5;
		}
		else
		{
			while (checker_node->pipe_string[data->i] != ' '
				&& checker_node->pipe_string[data->i] != 34)
				data->i++;
		}
	}
	if (checker_node->pipe_string[data->i] != '\0')
		data->string2[(*total)++] = checker_node->pipe_string[data->i];
	data->i++;
}

char	*clean_string(t_pipe_chain *checker_node, int total, char *user)
{
	t_clean_string_data	data;

	data.string2 = malloc (sizeof(char) * total + 1);
	data.i = 0;
	total = 0;
	data.verif = 0;
	while (checker_node->pipe_string[data.i])
	{
		if (checker_node->pipe_string[data.i] == 39)
			data.verif++;
		if (data.verif % 2 == 0)
		{
			if_verif(checker_node, &data, &total, user);
		}
		else
			data.string2[total++] = checker_node->pipe_string[data.i++];
	}
	data.string2[total] = '\0';
	checker_node->pipe_string = ft_strdup(data.string2);
	free(data.string2);
	return (NULL);
}
