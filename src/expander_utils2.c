/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:42:33 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 16:55:18 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expander_char(t_pipe_chain *checker_node, int i)
{
	if (checker_node->pipe_string[i] == ' ')
		return (1);
	if (checker_node->pipe_string[i] == 34)
		return (1);
	if (checker_node->pipe_string[i] == 39)
		return (1);
	if (checker_node->pipe_string[i] == '$')
		return (1);
	if (checker_node->pipe_string[i] == ' ')
		return (1);
	return (0);
}

char	*get_name(t_pipe_chain *checker_node, int i)
{
	int		x;
	int		k;
	char	*name;

	i++;
	x = 0;
	k = i;
	while (checker_node->pipe_string[i]
		&& is_expander_char(checker_node, i) == 0)
	{
		i++;
		x++;
	}
	name = malloc(sizeof(char) * (x + 1));
	x = 0;
	while (checker_node->pipe_string[k]
		&& is_expander_char(checker_node, k) == 0)
	{
		name[x] = checker_node->pipe_string[k];
		x++;
		k++;
	}
	name[x] = '\0';
	return (name);
}

char	*check_dollars_value(t_pipe_chain *checker_node, int i, t_env **env)
{
	int		x;
	int		k;
	char	*name;
	t_env	*en;

	en = *env;
	i++;
	x = 0;
	k = i;
	while (checker_node->pipe_string[i++]
		&& is_expander_char(checker_node, i) == 0)
		x++;
	name = malloc(sizeof(char) * (x + 1));
	x = 0;
	while (checker_node->pipe_string[k]
		&& is_expander_char(checker_node, k) == 0)
		name[x++] = checker_node->pipe_string[k++];
	name[x] = '\0';
	while (en->next != NULL)
	{
		if (ft_strncmp(name, en->name, x + 1) == 0)
			return (free(name), en->value);
		en = en->next;
	}
	return (free(name), NULL);
}
