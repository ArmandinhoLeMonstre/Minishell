/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:11:06 by armitite          #+#    #+#             */
/*   Updated: 2024/11/05 18:28:34 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_bash_char(int c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	file_check(t_pipe_chain *checker_node, int *i, int h, int redirect)
{
	int	j;

	j = 0;
	(*i)++;
	while (checker_node->pipe_string[*i] == ' ')
		(*i)++;
	while (checker_node->pipe_string[*i] && checker_node->pipe_string[*i] != ' ')
	{
		if (ft_is_bash_char(checker_node->pipe_string[*i]))
		{
			(*i)--;
			break ;
		}
		j++;
		(*i)++;
	}
	if (redirect == 1)
		return (stock_file(checker_node, h, j, 1), 1);
	if (redirect == 2)
		return (stock_file(checker_node, h, j, 2), 1);
	if (redirect == 3)
		return (stock_file(checker_node, h, j, 3), 1);
	if (redirect == 4)
		return (stock_file(checker_node, h, j, 4), 1);
	return (0);
}

int	pipe_check(t_pipe_chain *checker_node)
{
	int	i;
	int	x;
	int	j;
	
	i = 0;
	x = 0;
	j = stack_len(checker_node);
	while (x < j)
	{
		i = 0;
		while (checker_node->pipe_string[i])
		{
			if (checker_node->pipe_string[i] == 34)
			{
				i++;
				cmd_check_commas(checker_node, &i, i, 1);
				//i++;
			}
			if (checker_node->pipe_string[i] == 39)
			{
				i++;
				cmd_check_commas(checker_node, &i, i, 2);
				//i++;
			}
			else if (checker_node->pipe_string[i] == '<')
			{
				if (checker_node->pipe_string[i + 1] == '<')
				{
					i++;
					if (file_check(checker_node, &i, i, 4) > 0)
						printf("le heredoc2 : %s\n", checker_node->heredoc_chars);
				}
				else if (file_check(checker_node, &i, i, 1) > 0)
				{
					printf("ok infile name\n");
				}
			}
			else if (checker_node->pipe_string[i] == '>')
			{
				if (checker_node->pipe_string[i + 1] == '>')
				{
					i++;
					if (file_check(checker_node, &i, i, 3) > 0)
					{
						printf("le big outfile%d\n", checker_node->append);
					}
				}
				else if (file_check(checker_node, &i, i, 2) > 0)
				{
					printf("ok outfile name\n");
				}
			}
			else if (ft_isalnum((int)checker_node->pipe_string[i]) == 1 || checker_node->pipe_string[i] == '-')
			{
				cmd_check(checker_node, &i, i);
			}
			//printf("le I : %d\n", i);
			i++;
		}
		checker_node = checker_node->next;
		x++;
	}
	return (i);
}

void	pipe_parsing(t_pipe_chain **stack, int *tab)
{
	t_pipe_chain	*checker_node;
	int				j;
	int				x;
	
	checker_node = *stack;
	j = stack_len(checker_node);
	x = 0;
	if (tab != NULL)
		ft_strdup2(checker_node, tab);
	expander(checker_node);
	printf("%d\n", pipe_check (checker_node));
	printf("la cmd string : %s\n", checker_node->cmd_string);
	while (x < j)
	{
		checker_node->cmd = ft_split(checker_node->cmd_string, ' ');
		checker_node->cmd_path = get_paths(checker_node);
		printf("le path :%s\n", checker_node->cmd_path);
		printf("la cmd :%s\n", checker_node->cmd[0]);
		checker_node = checker_node->next;
		x++;
	}
}