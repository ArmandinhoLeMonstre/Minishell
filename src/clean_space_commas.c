/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:01:45 by armitite          #+#    #+#             */
/*   Updated: 2024/11/14 16:12:29 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_numbers(const char *rl)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (rl[i])
	{
		if (rl[i] == 39)
		{
			i++;
			while (rl[i] != 39)
			{
				if (rl[i] == ' ')
					nbr++;
				i++;
			}
		}
		if (rl[i] == 34)
		{
			i++;
			while (rl[i] != 34)
			{
				if (rl[i] == ' ')
					nbr++;
				i++;
			}
		}
		i++;
	}
	return (nbr);
}

char *change_space(char *rl, int *tab)
{
	int	i;
	int	index;
	char *rl2;

	i = 0;
	index = 0;
	tab = NULL;
	rl2 = malloc(sizeof(char) * (ft_strlen(rl) + 1));
	while (rl[i])
	{
		if (rl[i] == 34)
		{
			rl2[i] = rl[i];
			i++;
			while (rl[i] != 34)
			{
				if (rl[i] == ' ')
				{
					rl2[i] = '\t';
					//tab[index] = i;
					index++;
				}
				else
					rl2[i] = rl[i];
				i++;
			}
		}
		if (rl[i] == 39)
		{
			rl2[i] = rl[i];
			i++;
			while (rl[i] != 39)
			{
				if (rl[i] == ' ')
				{
					rl2[i] = '\t';
					//tab[index] = i;
					index++;
				}
				else
					rl2[i] = rl[i];
				i++;
			}
		}
			rl2[i] = rl[i];
		i++;
	}
	rl2[i] = '\0';
	printf("la string ds change space %s\n", rl2);
	i = 0;
	// while (i < index)
	// {
	// 	printf("le tab%d\n", tab[i]);
	// 	i++;
	// }
	return (rl2);
}

int *get_tab_space(const char *rl, int *tab)
{
	int	i;
	int	index;
	char *rl2;

	i = 0;
	index = 0;
	rl2 = malloc(sizeof(char) * (ft_strlen(rl) + 1));
	while (rl[i])
	{
		if (rl[i] == 39)
		{
			rl2[i] = rl[i];
			i++;
			while (rl[i] != 39)
			{
				if (rl[i] == ' ')
				{
					//rl2[i] = 'a';
					tab[index] = i;
					index++;
				}
				else
					rl2[i] = rl[i];
				i++;
			}
		}
		if (rl[i] == 34)
		{
			rl2[i] = rl[i];
			i++;
			while (rl[i] != 34)
			{
				if (rl[i] == ' ')
				{
					//rl2[i] = 'a';
					tab[index] = i;
					index++;
				}
				else
					rl2[i] = rl[i];
				i++;
			}
		}
		else
			rl2[i] = rl[i];
		i++;
	}
	rl2[i] = '\0';
	//printf("la string %s\n", rl2);
	i = 0;
	while (i < index)
	{
		printf("%d\n", tab[i]);
		i++;
	}
	return (tab);
}

char	**ft_strdup3(char **cmd, int *tab)
{
	int		total;
	int		index;
	int	i;
	int x;

	i = 0;
	total = 0;
	index = 0;
	x = 0;
	tab = NULL;
	while (cmd[x])
	{
		i = 0;
		while (cmd[x][i])
		{
			if (cmd[x][i] == '\t')
			{
				cmd[x][i] = ' ';
				index++;
			}
			else
				cmd[x][i] = cmd[x][i];
			i++;
		}
		x++;
	}
	return (cmd);
}