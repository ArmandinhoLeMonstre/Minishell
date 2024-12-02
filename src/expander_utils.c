/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:51 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 16:59:54 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_itoa(t_clean_string_data *data, int *total)
{
	int		i;
	char	*itoa;

	data->i++;
	data->i++;
	i = 0;
	itoa = ft_itoa(g_exitcode);
	while (itoa[i])
		data->string2[(*total)++] = itoa[i++];
}

void	if_dollarz2(t_pipe_chain *checker_node, t_clean_string_data *data,
	int *total, t_env **env)
{
	char	*value;

	if (checker_node->pipe_string[data->i + 1] == '?')
	{
		if_itoa(data, total);
		return ;
	}
	else if (check_dollars(checker_node, data->i, env) > 0)
	{
		data->h = 0;
		value = ft_strdup(check_dollars_value(checker_node, data->i, env));
		if (value != NULL)
		{
			while (value[data->h])
				data->string2[(*total)++] = value[data->h++];
		}
		free(value);
	}
	data->i++;
	while (checker_node->pipe_string[data->i]
		&& is_expander_char(checker_node, data->i) == 0)
		data->i++;
}

void	clean_string34(t_pipe_chain *checker_node,
	t_clean_string_data *data, int *total, t_env **env)
{
	char	*itoa;
	int		i;

	i = 0;
	itoa = NULL;
	data->string2[(*total)] = checker_node->pipe_string[data->i];
	(*total)++;
	data->i++;
	while (checker_node->pipe_string[data->i] != 34)
	{
		if (checker_node->pipe_string[data->i] == '$')
		{
			if_dollarz2(checker_node, data, total, env);
		}
		else if (checker_node->pipe_string[data->i] != 34)
		{
			data->string2[(*total)++] = checker_node->pipe_string[data->i++];
		}
	}
}

void	if_verif(t_pipe_chain *checker_node,
	t_clean_string_data *data, int *total, t_env **env)
{
	char	*itoa;
	int		i;

	i = 0;
	itoa = NULL;
	if (checker_node->pipe_string[data->i] == 34)
		clean_string34(checker_node, data, total, env);
	if (checker_node->pipe_string[data->i] == '$')
	{
		if_dollarz2(checker_node, data, total, env);
	}
	else if (checker_node->pipe_string[data->i] != '\0')
	{
		data->string2[(*total)++] = checker_node->pipe_string[data->i];
		data->i++;
	}
}

char	*clean_string(t_pipe_chain *checker_node, t_env **env, int total)
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
			if_verif(checker_node, &data, &total, env);
		}
		else
			data.string2[total++] = checker_node->pipe_string[data.i++];
	}
	data.string2[total] = '\0';
	free(checker_node->pipe_string);
	checker_node->pipe_string = ft_strdup(data.string2);
	free(data.string2);
	return (NULL);
}
