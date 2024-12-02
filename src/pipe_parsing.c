/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:11:06 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 21:14:22 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check_commas(t_pipe_chain *checker_node, int *i, int z)
{
	if (checker_node->pipe_string[*i] == 34)
	{
		(*i)++;
		if (checker_node->pipe_string[*i] == 34)
			return (0);
		cmd_check_commas(checker_node, i, z + 1, 1);
	}
	if (checker_node->pipe_string[*i] == 39)
	{
		(*i)++;
		if (checker_node->pipe_string[*i] == 39)
			return (0);
		cmd_check_commas(checker_node, i, z + 1, 2);
	}
	return (0);
}

int	pipe_check_redirect(t_pipe_chain *checker_node, int *i, int z)
{
	if (checker_node->pipe_string[*i] == '<')
	{
		if (checker_node->pipe_string[z + 1] == '<')
		{
			(*i)++;
			z++;
			file_check(checker_node, i, z, 4);
		}
		else
			file_check(checker_node, i, z, 1);
	}
	else if (checker_node->pipe_string[*i] == '>')
	{
		if (checker_node->pipe_string[z + 1] == '>')
		{
			(*i)++;
			z++;
			file_check(checker_node, i, z, 3);
		}
		else
			file_check(checker_node, i, z, 2);
	}
	return (0);
}

int	pipe_check(t_pipe_chain *checker_node, int j)
{
	int	i;
	int	x;

	x = 0;
	while (x < j)
	{
		i = 0;
		while (checker_node->pipe_string[i])
		{
			if (checker_node->pipe_string[i] == 34
				|| checker_node->pipe_string[i] == 39)
				pipe_check_commas(checker_node, &i, i);
			else if (checker_node->pipe_string[i] == '>'
				|| checker_node->pipe_string[i] == '<')
				pipe_check_redirect(checker_node, &i, i);
			else if (checker_node->pipe_string[i] != 32
				&& ft_is_bash_char(checker_node->pipe_string[i]) == 0)
				cmd_check(checker_node, &i, i);
			i++;
		}
		checker_node = checker_node->next;
		x++;
	}
	return (i);
}

int	add_path(t_pipe_chain *checker_node, int j)
{
	int	x;

	x = 0;
	while (x < j)
	{
		if (checker_node->cmd_string != NULL)
		{
			checker_node->cmd = ft_split(checker_node->cmd_string, ' ');
			checker_node->cmd_path = get_paths(checker_node);
			checker_node->cmd = ft_strdup3(checker_node->cmd);
		}
		checker_node = checker_node->next;
		x++;
	}
	return (0);
}

void	pipe_parsing(t_pipe_chain **stack, int *tab, t_env **env)
{
	t_pipe_chain	*checker_node;
	int				j;

	checker_node = *stack;
	j = stack_len(checker_node);
	if (tab != NULL)
	{
		ft_strdup2(checker_node, tab, j);
		free(tab);
	}
	expander(checker_node, env);
	while_space(checker_node, j);
	pipe_check(checker_node, j);
	add_path(checker_node, j);
}
