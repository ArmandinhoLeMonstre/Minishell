/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:51 by armitite          #+#    #+#             */
/*   Updated: 2024/11/27 18:43:51 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_dollars_value(t_pipe_chain *checker_node, int i, t_env **env)
{
	int	x;
	int k;
	char *name;
	t_env *en;
	
	en = *env;
	i++;
	x = i;
	k = i;
	while (checker_node->pipe_string[i] && (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != '$'))
	{
		i++;
		x++;
	}
	name = malloc(sizeof(char) * (x + 1));
	x = 0;
	while (checker_node->pipe_string[k] && (checker_node->pipe_string[k] != ' ' && checker_node->pipe_string[k] != '$'))
	{
		name[x] = checker_node->pipe_string[k];
		x++;
		k++;
	}
	name[x] = '\0';
	printf("le name %s\n", name);
	while (en->next != NULL)
	{
		if (ft_strncmp(name, en->name, x + 1) == 0)
			return (en->value);
		en = en->next;
	}
	return (NULL);
}

void	clean_string34(t_pipe_chain *checker_node,
	t_clean_string_data *data, int *total, char *user, t_env **env)
{
	char *itoa;
	int i;
	
	i = 0;
	itoa = NULL;
	data->string2[(*total)] = checker_node->pipe_string[data->i];
	(*total)++;
	data->i++;
	while (checker_node->pipe_string[data->i] != 34)
	{
		if (checker_node->pipe_string[data->i] == '$')
		{
			if (checker_node->pipe_string[data->i + 1] == '?')
			{	
				data->i++;
				data->i++;
				i = 0;
				itoa = ft_itoa(g_exitcode);
				while (itoa[i])
				{
					data->string2[(*total)++] = itoa[i++];
				}
			}
			else if (check_dollars(checker_node, data->i, env) == 1)
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
		else if (checker_node->pipe_string[data->i] != 34)
		{
			data->string2[(*total)++] = checker_node->pipe_string[data->i++];
		}
	}
}

void	if_verif(t_pipe_chain *checker_node, t_clean_string_data *data, int *total, char *user, t_env **env)	
{
	char *itoa;
	char *value;
	int i;
	
	i = 0;
	itoa = NULL;
	if (checker_node->pipe_string[data->i] == 34)
		clean_string34(checker_node, data, total, user, env);
	if (checker_node->pipe_string[data->i] == '$')
	{
		if (checker_node->pipe_string[data->i + 1] == '?')
		{	
			data->i++;
			data->i++;
			i = 0;
			itoa = ft_itoa(g_exitcode);
			while (itoa[i])
			{
				data->string2[(*total)++] = itoa[i++];
			}
		}
		else if (check_dollars(checker_node, data->i, env) > 0)
		{
			data->h = 0;
			value = ft_strdup(check_dollars_value(checker_node, data->i, env));
			printf("la value %s\n", value);
			printf("la data i %d\n", data->i);
			
			if (value != NULL)
			{
				while (value[data->h])
					data->string2[(*total)++] = value[data->h++];
			}
			data->i++;
			while (checker_node->pipe_string[data->i] && (checker_node->pipe_string[data->i] != ' ' && checker_node->pipe_string[data->i] != '$'))
				data->i++;
			free(value);
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
		}
	}
	else if (checker_node->pipe_string[data->i] != '\0')
	{
		
		data->string2[(*total)++] = checker_node->pipe_string[data->i];
		data->i++;
	}
}

char	*clean_string(t_pipe_chain *checker_node, t_env **env, int total, char *user)
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
			if_verif(checker_node, &data, &total, user, env);
		}
		else
			data.string2[total++] = checker_node->pipe_string[data.i++];
	}
	data.string2[total] = '\0';
	checker_node->pipe_string = ft_strdup(data.string2);
	free(data.string2);
	return (NULL);
}