/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in_commas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:14:28 by armitite          #+#    #+#             */
/*   Updated: 2024/10/31 15:01:42 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_numbers(const char *rl)
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
				if (rl[i] == '|')
					nbr++;
				i++;
			}
		}
		if (rl[i] == 34)
		{
			i++;
			while (rl[i] != 34)
			{
				if (rl[i] == '|')
					nbr++;
				i++;
			}
		}
		i++;
	}
	return (nbr);
}

char *change_pipe(char *rl, int *tab)
{
	int	i;
	int	index;
	char *rl2;

	i = 0;
	index = 0;
	rl2 = malloc(sizeof(char) * (ft_strlen(rl) + 1));
	while (rl[i])
	{
		if (rl[i] == 34)
		{
			rl2[i] = rl[i];
			i++;
			while (rl[i] != 34)
			{
				if (rl[i] == '|')
				{
					rl2[i] = 'a';
					tab[index] = i;
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
				if (rl[i] == '|')
				{
					rl2[i] = 'a';
					tab[index] = i;
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
	printf("la string ds change pipe %s\n", rl2);
	i = 0;
	while (i < index)
	{
		printf("le tab%d\n", tab[i]);
		i++;
	}
	return (rl2);
}

int *get_tab(const char *rl, int *tab)
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
				if (rl[i] == '|')
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
				if (rl[i] == '|')
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

// char	*reput_pipe(t_pipe_chain *checker_node, int *tab)
// {
// 	int	i;
// 	int	len;
// 	int	index;

// 	i = 0;
// 	index = 0;
// 	while (checker_node->pipe_string[i])
// 	{
// 		if (i == tab[index])
// 		{
// 			rl2[i] = '|';
// 			index++;
// 		}
// 		else
// 			rl2[i] = rl[i];
// 		i++;
// 	}
// 	rl2[i] = '\0';
// 	return (rl2);
// }

char	*ft_strdup2(t_pipe_chain *checker_node, int *tab)
{
	//char	*dst;
	int		total;
	int		index;
	int	i;

	i = 0;
	total = 0;
	index = 0;
	//printf("ici");
	while (checker_node->next != NULL)
	{
		i = 0;
		if (checker_node->prev != NULL)
			total = total + ft_strlen(checker_node->prev->pipe_string) + 1;
		printf("total : %d\n", total);
		printf("la string avt append :  %s\n", checker_node->pipe_string);
		while (checker_node->pipe_string[i])
		{
			if (i + total == tab[index])
			{
				checker_node->pipe_string[i] = '|';
				index++;
			}
			else
				checker_node->pipe_string[i] = checker_node->pipe_string[i];
			i++;
		}
		printf("la string ds append :  %s\n", checker_node->pipe_string);
		checker_node = checker_node->next;
	}
	// i = 0;
	// total = total + ft_strlen(checker_node->pipe_string);
	// printf("total : %d\n", total);
	// 	while (checker_node->pipe_string[i])
	// 	{
	// 		if (i + total == tab[index])
	// 		{
	// 			checker_node->pipe_string[i] = '|';
	// 			index++;
	// 		}
	// 		else
	// 			checker_node->pipe_string[i] = checker_node->pipe_string[i];
	// 		i++;
	// 	}
		//checker_node = checker_node->next;
	//printf("total : %d\n", total);
	//dst = (char *) malloc(ft_strlen(checker_node->pipe_string) + 1);
	// if (!dst)
	// 	return (0);
	// while (checker_node->pipe_string[i])
	// {
	// 	if (i + total == tab[index])
	// 	{
	// 		dst[i] = '|';
	// 		index++;
	// 	}
	// 	else
	// 		dst[i] = s1[i];
	// 	i++;
	// }
	//dst[i] = 0;
	return (NULL);
}

int	pipe_split(t_pipe_chain *stack, char *rl, char **envp, int *tab)
{
	//int	*tab;
	char	**split_rl;
	int	i;

	i = 0;
	rl = change_pipe(rl, tab);
	split_rl = ft_split(rl, '|');
	if (!split_rl)
		return (ft_free2(split_rl), 2);
	//stack = NULL;
	while (split_rl[i])
	{
		//printf("le i, %s\n", split_rl[i]);
		//printf("la string ds pipe_n %s\n", rl);
		append_node(&stack, split_rl[i], envp);
		//printf("la string avt append :  %s\n", stack->pipe_string);
		// stack->pipe_string = ft_strdup2(&stack, split_rl[i], tab);
		// printf("la string ds append :  %s\n", stack->pipe_string);
		// stack = stack->next;
		i++;
	}
	ft_free2(split_rl);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	char *rl;

// 	rl = av[1];
// 	ft_range(rl);
// 	// printf("%d\n", pipe_numbers(rl));
// 	return (0);
// }