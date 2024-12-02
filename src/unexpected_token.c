/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:05 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 18:03:49 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char *rl, int *i, int x)
{
	if (rl[x] == '|' && (rl[*i] == '<' || rl[*i] == '>'))
	{
		if (rl[*i] == '>' && rl[*i + 1] == '>')
			(*i)++;
		if (rl[*i] == '<' && rl[*i + 1] == '<')
			(*i)++;
		(*i)++;
		while (rl[*i] == ' ')
			(*i)++;
	}
	return (0);
}

int	after_token(char *rl, int *i, int x)
{
	if ((rl[*i] == '>' && rl[*i + 1] == '>')
		&& ft_is_bash_char(rl[*i + 2]) != 1)
		return (0);
	if ((rl[*i] == '<' && rl[*i + 1] == '<')
		&& ft_is_bash_char(rl[*i + 2]) != 1)
		return (0);
	(*i)++;
	while (rl[*i] == ' ')
		(*i)++;
	special_case(rl, i, x);
	while (rl[*i])
	{
		if (rl[*i] == 34 || rl[*i] == 39)
			return (0);
		if (ft_is_bash_char(rl[*i]))
			return (ft_putstr_fd("syntax error near unexpected token `", 2),
				write(2, &rl[*i], 1), ft_putendl_fd("'", 2), 1);
		else
			return (0);
		(*i)++;
	}
	ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	return (1);
}

int	token_checker(char *rl)
{
	int	i;

	i = 0;
	while (rl[i])
	{
		if (rl[i] == 34)
		{
			i++;
			while (rl[i] != 34)
				i++;
		}
		if (rl[i] == 39)
		{
			i++;
			while (rl[i] != 39)
				i++;
		}
		if (ft_is_bash_char(rl[i]))
			if (after_token(rl, &i, i) == 1)
				return (1);
		i++;
	}
	return (0);
}
