/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:19:01 by armitite          #+#    #+#             */
/*   Updated: 2024/12/01 13:39:44 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(t_pipe_chain *stack)
{
	// t_pipe_chain	*stack;

	// stack = *a;
	if (stack->infile != 0)
	{
		close(stack->infile);
		free(stack->last_infile);
	}
	if (stack->outfile != 0)
	{
		close(stack->outfile);
		free(stack->last_outfile);
	}
	if (stack->append != 0)
	{
		close(stack->append);
		free(stack->last_append);
	}
	if (stack->cmd_string != NULL)
		free(stack->cmd_string);
	if (stack->cmd_path != NULL)
		free(stack->cmd_path);
	if (stack->cmd != NULL)
		ft_free2(stack->cmd);
	if (stack->heredoc_chars != NULL)
		free(stack->heredoc_chars);
	if (stack->pipe_string != NULL)
		free(stack->pipe_string);
}

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
		free_stack(stack);
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