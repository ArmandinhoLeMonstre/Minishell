/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:05 by armitite          #+#    #+#             */
/*   Updated: 2024/10/16 15:50:52 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_token(t_pipe_chain *checker_node, int *i)
{
	if (checker_node->pipe_string[*i] == '>' && checker_node->pipe_string[*i + 1] == '>')
		return (0);
	if (checker_node->pipe_string[*i] == '<' && checker_node->pipe_string[*i + 1] == '<')
		return (0);
	(*i)++;
	while (checker_node->pipe_string[*i] == ' ')
		(*i)++;
	while (checker_node->pipe_string[*i])
	{
		if (ft_is_bash_char(checker_node->pipe_string[*i]))
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			//ft_putstr_fd(&checker_node->pipe_string[*i], 2);
			write(2, &checker_node->pipe_string[*i], 1);
			ft_putendl_fd("'", 2);
			return (1);
		}
		else
			return (0);
	}
	if (checker_node->next == NULL)
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	else
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	return (1);
}

int	token_checker(t_pipe_chain **stack)
{
	int	i;
	int	j;
	int	x;
	t_pipe_chain *checker_node;
	
	x = 0;
	checker_node = *stack;
	j = stack_len(checker_node);
	while (x < j)
	{
		i = 0;
		while (checker_node->pipe_string[i])
		{
			if (ft_is_bash_char(checker_node->pipe_string[i]))
				if (after_token(checker_node, &i) == 1)
				{
					return (1);
				}
			i++;
		}
		checker_node = checker_node->next;
		x++;
	}
	return (0);
}