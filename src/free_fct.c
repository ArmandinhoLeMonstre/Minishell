/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:19:01 by armitite          #+#    #+#             */
/*   Updated: 2024/09/26 14:49:01 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nodes(t_pipe_chain **a)
{
	int				i;
	int				j;
	t_pipe_chain	*tmp;
	t_pipe_chain	*stack;

	stack = *a;
	if (!stack)
		return ;
	j = 0;
	i = stack_len(*a);
	while (j < i)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
		j++;
	}
	*a = NULL;
}

void	ft_free2(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}