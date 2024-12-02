/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_global_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:10:10 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 19:20:50 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_bash_char(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	ft_ispipe(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	empty_rl(char *rl)
{
	int	i;

	i = 0;
	while (rl[i])
	{
		if (rl[i] != 32)
			return (0);
		else
			i++;
	}
	return (1);
}

int	check_unavaible_chars(char *rl)
{
	if (ft_strchr(rl, ';') != 0)
		return (printf("';' is not a valid char\n"), 1);
	if (ft_strchr(rl, '\\') != 0)
		return (printf("'\\' is not a valid char\n"), 1);
	return (0);
}
