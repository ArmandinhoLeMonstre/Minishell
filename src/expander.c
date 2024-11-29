/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:59 by armitite          #+#    #+#             */
/*   Updated: 2024/11/29 15:38:33 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollars(t_pipe_chain *checker_node, int i, t_env **env)
{
	int	x;
	int k;
	char *name;
	t_env *en;
	
	en = *env;
	i++;
	x = 0;
	k = i;
	while (checker_node->pipe_string[i] && (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != '$' && checker_node->pipe_string[k] != 34))
	{
		i++;
		x++;
	}
	name = malloc(sizeof(char) * (x + 1));
	x = 0;
	while (checker_node->pipe_string[k] && (checker_node->pipe_string[k] != ' ' && checker_node->pipe_string[k] != '$' && checker_node->pipe_string[k] != 34))
	{
		name[x] = checker_node->pipe_string[k];
		x++;
		k++;
	}
	name[x] = '\0';
	while (en->next != NULL)
	{
		if (ft_strncmp(name, en->name, x + 1) == 0)
		{
			int h = ft_strlen(en->value);
			printf("%d\n", h);
			return (free(name), h);
		}
		en = en->next;
	}
	return (free(name), 0);
}

int	commas34(t_pipe_chain *checker_node, int i, int *total, char *user, t_env **env)
{
	int x;
	i++;
	(*total)++;
	x = 0;
	user = NULL;
	while (checker_node->pipe_string[i] != 34)
	{
		if (checker_node->pipe_string[i] == '$')
		{
			if (checker_node->pipe_string[i + 1] == '?')
			{
				i++;
				(*total) += ft_strlen(ft_itoa(g_exitcode));
			}
			else if ((x = check_dollars(checker_node, i, env)) > 0)
			{
				(*total) = (*total) + x;
				printf("le x bis : %d\n", x);
				printf("le data tot bis : %d\n", (*total));
				i++;
				while (checker_node->pipe_string[i] && (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != '$' && checker_node->pipe_string[i] != 34))			
					i++;
				i--;
			}
			else
			{
				while (checker_node->pipe_string[i] && (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != '$'))
					i++;
				i--;
			}
		}
		i++;
		(*total)++;
	}
	return (i);
}

void	parse_string_expander(t_pipe_chain *checker_node, t_expander_data *data, t_env **env)
{
	int x;
	int verif;

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
				if (checker_node->pipe_string[data->i + 1] == '?')
				{
					data->i++;
					data->total += ft_strlen(ft_itoa(g_exitcode));
				}
				else if ((x = check_dollars(checker_node, data->i, env)) > 0)
				{
					data->total = data->total + x;
					printf("le x : %d\n", x);
					printf("le data tot : %d\n", data->total);
					data->i++;
					while (checker_node->pipe_string[data->i] && checker_node->pipe_string[data->i] != ' ')			
						data->i++;
					data->i--;
				}
				else
				{
					data->i++;
					while (checker_node->pipe_string[data->i])
					{
						data->i++;
						if (checker_node->pipe_string[data->i] == ' ' && checker_node->pipe_string[data->i] == '$')
							break ;
					}
					data->i--;
				}
			}
			else if (checker_node->pipe_string[data->i] == 34)
				data->i = commas34(checker_node, data->i, &data->total, data->user, env);
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
	data.user = get_user(checker_node);

	while (data.x < data.j)
	{
		data.i = 0;
		data.verif = 0;
		parse_string_expander(checker_node, &data, env);
		clean_string(checker_node, env, data.total, data.user);
		checker_node = checker_node->next;
		data.x++;
	}
	free(data.user);
}
