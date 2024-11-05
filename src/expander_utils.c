/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:51 by armitite          #+#    #+#             */
/*   Updated: 2024/11/05 18:02:26 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_string(t_pipe_chain *checker_node, int total, char *user)
{
	char *string2;
	int	i;
	int	h;
	int	verif;
	
	string2 = malloc (sizeof(char) * total + 1);
	i = 0;
	total = 0;
	verif = 0;
	while (checker_node->pipe_string[i])
	{
		if (checker_node->pipe_string[i] == 39)
		{
			verif++;
			//i++;
		}
		if (verif % 2 == 0)
		{
			if (checker_node->pipe_string[i] == 34)
			{
				string2[total] = checker_node->pipe_string[i];
				total++;
				i++;
				while (checker_node->pipe_string[i] != 34)
				{
					if (checker_node->pipe_string[i] == '$')
					{
						if (check_dollars(checker_node, i) == 1)
						{
							h = 0;
							while (user[h])
							{
								string2[total] = user[h];
								h++;
								total++;
							}
							i = i + 5;
						}
						else
						{
							while (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != 34)
								i++;
							//i--;
						}
					}
					if (checker_node->pipe_string[i] != 34)
					{
						string2[total] = checker_node->pipe_string[i];
						total++;
						i++;
					}
				}
			}
			if (checker_node->pipe_string[i] != '\0') //&& checker_node->pipe_string[i] != 34)
			{
				string2[total] = checker_node->pipe_string[i];
				total++;
			}
			i++;
		}
		else
		{
			string2[total] = checker_node->pipe_string[i];
			total++;
			i++;
		}
	}
	string2[total] = '\0';
	return (string2);
}