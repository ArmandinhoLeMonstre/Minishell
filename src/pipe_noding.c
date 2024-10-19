/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_noding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:50:07 by armitite          #+#    #+#             */
/*   Updated: 2024/10/16 18:09:54 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stack_len(t_pipe_chain *stack)
{
	int	i;

	i = 0;
	if (!stack)
		return (0);
	while (stack != NULL)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

t_pipe_chain	*find_last(t_pipe_chain *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next != NULL)
		stack = stack->next;
	return (stack);
}

void	append_node(t_pipe_chain **stack, char *rl, int i, char **envp)
{
	t_pipe_chain	*node;
	t_pipe_chain	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_pipe_chain));
	// if (!node)
	// 	panic_parsing(stack, 1);
	node->next = NULL;
	node->pipe_string = ft_strdup(rl);
	node->envp = envp;
	node->infile = 0;
	node->outfile = 0;
	node->pipe_number = i;
	if (!(*stack))
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

int	pipe_noding(char *rl, char **envp)
{	
	int				i;
	char			**split_rl;
	t_pipe_chain	*stack;

	i = 0;
	split_rl = ft_split(rl, '|');
	if (!split_rl)
		return (ft_free2(split_rl), 2);
    stack = NULL;
	while (split_rl[i])
	{
		//printf("le i, %s\n", split_rl[i]);
		append_node(&stack, split_rl[i], i, envp);
		i++;
	}
	ft_free2(split_rl);
	if (token_checker(&stack) == 1)
		panic_parsing(stack, -1);
	pipe_parsing(&stack);
	//get_outfile_number(stack);
	printf("le i, %d\n", get_outfile_number(stack));
	shell_exec2(&stack);
	// if (i > 0)
	// {
	// 	while (stack->next != NULL)
	// 	{
	// 		printf("le i : %d\n", stack->pipe_number);
	// 		stack = stack->next;
	// 	}
	// 	printf("le i : %d\n", stack->pipe_number);
	// }
	return (0);
}