/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic_parsing_fct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:18:20 by armitite          #+#    #+#             */
/*   Updated: 2024/10/16 18:18:10 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	files_error(t_pipe_chain *checker_node, int c)
{
	// if find last checker == vrai, tt free;
	if (c == 0)
	{
		ft_putstr_fd(checker_node->last_infile, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free_nodes(&checker_node);
		exit(1);
	}
}