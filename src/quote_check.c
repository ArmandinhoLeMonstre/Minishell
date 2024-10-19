/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:51 by armitite          #+#    #+#             */
/*   Updated: 2024/10/16 17:48:58 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_quote(char *rl, int *i, int keycode)
{
	int	x;

	x = 0;
	(*i)++;
	if (keycode == 1)
	{
		while (rl[*i])
		{
			if (rl[*i] == '"')
				return (x);
			(*i)++;
			x++;
		}
	}
	else
	{
		while (rl[*i])
		{
			if (rl[*i] == 39)
				return (x);
			(*i)++;
			x++;
		}
	}
	return (-1);
}

int	quote_checker(char *rl)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (rl[i])
	{
		if (rl[i] == '"')
		{
			x = after_quote(rl, &i, 1);
			if (x == -1)
				return (printf("err quote"), exit(1), 2);
		}
		if (rl[i] == 39)
		{
			x = after_quote(rl, &i, 2);
			if (x == -1)
				return (printf("err quote"), exit(1), 2);
		}
		i++;
	}
	return (0);
}