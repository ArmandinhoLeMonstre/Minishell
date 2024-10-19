/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:18:39 by armitite          #+#    #+#             */
/*   Updated: 2024/10/16 15:53:47 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	panic_parsing(t_pipe_chain *checker_node, int error_code)
{
	if (error_code == -1)
		return (free_nodes(&checker_node), exit(1), 2);
	if (error_code == 0)
		return (files_error(checker_node, 0), 2);
	return (0);
}