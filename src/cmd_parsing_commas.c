/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:13:12 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 09:38:36 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name_cmd(t_pipe_chain *checker_node, int h, int j)
{
	int		x;
	char	*cmd_name;

	x = 0;
	cmd_name = malloc(sizeof(char) * (j + 1));
	while (j > 0)
	{
		cmd_name[x] = checker_node->pipe_string[h];
		h++;
		j--;
		x++;
	}
	cmd_name[x] = '\0';
	return (cmd_name);
}

void	stock_cmd_commas(t_pipe_chain *checker_node, int h, int j)
{
	char	*cmd_name;
	char	*tmp;

	cmd_name = get_name_cmd(checker_node, h, j);
	if (checker_node->cmd_string == NULL)
	{
		tmp = ft_strdup(cmd_name);
		checker_node->cmd_string = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		if (checker_node->pipe_string[h - 2] == 32)
			tmp = ft_strjoin(checker_node->cmd_string, " ");
		else
			tmp = ft_strdup(checker_node->cmd_string);
		free(checker_node->cmd_string);
		checker_node->cmd_string = ft_strjoin(tmp, cmd_name);
		free(tmp);
	}
	free(cmd_name);
}

int	cmd_check_commas(t_pipe_chain *checker_node, int *i, int h, int keycode)
{
	int	j;

	j = 0;
	if (keycode == 1)
	{
		while (checker_node->pipe_string[*i] != 34)
		{
			j++;
			(*i)++;
		}
	}
	else
	{
		while (checker_node->pipe_string[*i] != 39)
		{
			j++;
			(*i)++;
		}
	}
	stock_cmd_commas(checker_node, h, j);
	return (1);
}

int	cmd_lenght(t_pipe_chain *checker_node, int *i, int *checker)
{
	int	j;

	j = 0;
	while (checker_node->pipe_string[*i])
	{
		if (checker_node->pipe_string[*i] == 34
			|| checker_node->pipe_string[*i] == 39)
		{
			(*checker)++;
			break ;
		}
		j++;
		(*i)++;
		if (ft_is_bash_char(checker_node->pipe_string[*i]) == 1)
			break ;
		if (checker_node->pipe_string[*i] == ' ')
			break ;
	}
	return (j);
}
