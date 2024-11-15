/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:59 by armitite          #+#    #+#             */
/*   Updated: 2024/11/14 16:07:11 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollars(t_pipe_chain *checker_node, int i)
{
	i++;
	if (ft_strncmp(checker_node->pipe_string + i, "USER", 4) == 0)
		return (1);
	return (0);
}

int	commas34(t_pipe_chain *checker_node, int i, int *total, char *user)
{
	i++;
	(*total)++;
	while (checker_node->pipe_string[i] != 34)	
	{
		if (checker_node->pipe_string[i] == '$')
		{
			if (check_dollars(checker_node, i) == 1)
			{
				//printf("le total avt : %d\n", (int)total);
				(*total) = (*total) + ft_strlen(user);							
				//printf("le total apres : %d\n", (int)total);
				i = i + 4;
			}
			else
			{
				while (checker_node->pipe_string[i] != ' ' && checker_node->pipe_string[i] != 34)
					i++;
				i--;
			}					
		}
		i++;
		//if (checker_node->pipe_string[i] != 34)
			(*total)++;
	}
	return (i);
}

void	expander(t_pipe_chain *checker_node)
{
	int	i;
	int	x;
	int	j;
	int	total;
	int	verif;
	char *user;
	//char *string2;

	i = 0;
	x = 0;
	total = 0;
	j = stack_len(checker_node);
	user = get_user(checker_node);
	//printf("l'utilisateur : %s\n", user);
	while (x < j)
	{
		i = 0;
		verif = 0;
		while (checker_node->pipe_string[i])
		{
			if (checker_node->pipe_string[i] == 34)
			{
				i = commas34(checker_node, i, &total, user);
			}
			i++;
			if (checker_node->pipe_string[i] != '\0')
				total++;
		}
		checker_node->pipe_string = ft_strdup(clean_string(checker_node, total, user));
		checker_node = checker_node->next;
		x++;
	}
}