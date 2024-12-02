/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:59 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 17:04:02 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollars(t_pipe_chain *checker_node, int i, t_env **env)
{
	int		x;
	char	*name;
	int		h;
	t_env	*en;

	en = *env;
	x = 0;
	name = get_name(checker_node, i);
	while (en->next != NULL)
	{
		if (ft_strncmp(name, en->name, x + 1) == 0)
		{
			h = ft_strlen(en->value);
			return (free(name), h);
		}
		en = en->next;
	}
	return (free(name), 0);
}

int	if_dollarz(t_pipe_chain *checker_node, t_expander_data *data, t_env **env)
{
	int	x;

	x = check_dollars(checker_node, data->i, env);
	data->i++;
	if (checker_node->pipe_string[data->i + 1] == '?')
	{
		data->total += ft_strlen(ft_itoa(g_exitcode));
	}
	else if (x > 0)
	{
		data->total = data->total + x;
		while (checker_node->pipe_string[data->i]
			&& is_expander_char(checker_node, data->i) == 0)
			data->i++;
		data->i--;
	}
	else
	{
		while (checker_node->pipe_string[data->i]
			&& is_expander_char(checker_node, data->i) == 0)
			data->i++;
		data->i--;
	}
	return (0);
}

int	commas34(t_pipe_chain *checker_node, int i,
	t_env **env, t_expander_data *data)
{
	int	x;

	data->i++;
	data->total++;
	x = 0;
	while (checker_node->pipe_string[data->i] != 34)
	{
		if (checker_node->pipe_string[data->i] == '$')
		{
			if_dollarz(checker_node, data, env);
		}
		data->i++;
		data->total++;
	}
	return (i);
}

void	parse_string_expander(t_pipe_chain *checker_node,
	t_expander_data *data, t_env **env)
{
	int	x;
	int	verif;

	x = 0;
	verif = 0;
	while (checker_node->pipe_string[data->i])
	{
		if (checker_node->pipe_string[data->i] == 39)
			verif++;
		if (verif % 2 == 0)
		{
			if (checker_node->pipe_string[data->i] == '$')
			{
				if_dollarz(checker_node, data, env);
			}
			else if (checker_node->pipe_string[data->i] == 34)
				commas34(checker_node, data->i, env, data);
		}
		data->i++;
		data->total++;
	}
}

void	expander(t_pipe_chain *checker_node, t_env **env)
{
	t_expander_data	data;

	data.x = 0;
	data.total = 0;
	data.j = stack_len(checker_node);
	while (data.x < data.j)
	{
		data.i = 0;
		data.verif = 0;
		parse_string_expander(checker_node, &data, env);
		clean_string(checker_node, env, data.total);
		checker_node = checker_node->next;
		data.x++;
	}
}
