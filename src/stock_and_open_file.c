/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_and_open_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:14:14 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 19:21:26 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfiles_function(t_pipe_chain *checker_node, int c)
{
	if (c == 1)
	{
		if (checker_node->infile != 0)
			close(checker_node->infile);
		checker_node->infile = open(checker_node->last_infile, O_RDONLY);
		checker_node->checker_in_here = 2;
	}
	if (c == 2)
	{
		if (checker_node->outfile != 0)
			close(checker_node->outfile);
		checker_node->outfile = open(checker_node->last_outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		checker_node->checker = 2;
	}
	if (c == 3)
	{
		if (checker_node->append != 0)
			close(checker_node->append);
		checker_node->append = open(checker_node->last_append,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		checker_node->checker = 3;
	}
}

int	redirect_check_dup(t_pipe_chain *checker_node,
	char *file_name, int redirect)
{
	if (redirect == 1)
		checker_node->last_infile = ft_strdup(file_name);
	if (redirect == 2)
		checker_node->last_outfile = ft_strdup(file_name);
	if (redirect == 3)
		checker_node->last_append = ft_strdup(file_name);
	if (redirect == 4)
		checker_node->heredoc_chars = ft_strdup(file_name);
	return (0);
}

void	stock_file(t_pipe_chain *checker_node, int h, int j, int redirect)
{
	int		x;
	char	*file_name;

	h++;
	x = 0;
	file_name = malloc(sizeof(char) * (j + 1));
	while (checker_node->pipe_string[h] == ' ')
		h++;
	if (checker_node->pipe_string[h] == 34
		|| checker_node->pipe_string[h] == 39)
		h++;
	while (j > 0)
	{
		file_name[x] = checker_node->pipe_string[h];
		h++;
		j--;
		x++;
	}
	file_name[x] = '\0';
	redirect_check_dup(checker_node, file_name, redirect);
	free(file_name);
	if (redirect == 1 || redirect == 2 || redirect == 3)
		outfiles_function(checker_node, redirect);
	if (redirect == 4)
		display_line(checker_node);
}
