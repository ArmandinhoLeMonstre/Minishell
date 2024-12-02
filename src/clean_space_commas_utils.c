/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space_commas_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:06:44 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 09:10:10 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_space_number(const char *rl, int *i, int *nbr)
{
	if (rl[*i] == 39)
	{
		(*i)++;
		while (rl[*i] != 39)
		{
			if (rl[*i] == ' ')
				(*nbr)++;
			(*i)++;
		}
	}
	if (rl[*i] == 34)
	{
		(*i)++;
		while (rl[*i] != 34)
		{
			if (rl[*i] == ' ')
				(*nbr)++;
			(*i)++;
		}
	}
}

int	space_numbers(const char *rl)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (rl[i])
	{
		if (rl[i] == 39 || rl[i] == 34)
			get_space_number(rl, &i, &nbr);
		i++;
	}
	return (nbr);
}
