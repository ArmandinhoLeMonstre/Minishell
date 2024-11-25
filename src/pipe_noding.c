/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_noding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:50:07 by armitite          #+#    #+#             */
/*   Updated: 2024/11/25 08:44:00 by armitite         ###   ########.fr       */
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

void	append_node(t_pipe_chain **stack, char *rl, char **envp)
{
	t_pipe_chain	*node;
	t_pipe_chain	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_pipe_chain));
	node->next = NULL;
	node->pipe_string = ft_strdup(rl);
	node->cmd = NULL;
	node->envp = envp;
	node->infile = 0;
	node->outfile = 0;
	node->append = 0;
	node->heredoc_chars = ft_strdup("");
	node->cmd_string = NULL;
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

int appending(t_pipe_chain **stack, int i, char **envp, char *rl)
{
	char			**split_rl;
	//t_pipe_chain	*stack;

	//stack = NULL;
	if (ft_ispipe(rl) != 0)
	{
		i = 0;
		split_rl = ft_split(rl, '|');
		while (split_rl[i])
		{
			append_node(stack, split_rl[i], envp);
			i++;
		}
		ft_free2(split_rl);
	}
	else
		append_node(stack, rl, envp);
	//return (stack);
	return (0);
}

int	pipe_noding(t_pipe_chain **stack, char *rl, char **envp)
{
	int				i;
	int				*tab;
	//t_pipe_chain	*stack;

	i = 0;
	//stack = *s;
	tab = NULL;
	if (rl[0] == '\0')
		return (2);
	if (token_checker(rl) == 1)
	{
		g_exitcode = 258;
		return (2);
	}
	if (pipe_numbers(rl) > 0)
	{
		tab = (malloc(pipe_numbers(rl) * sizeof(int)));
		tab = get_tab(rl, tab);
		rl = change_pipe(rl, tab);
	}
	if (ft_ispipe(rl) != 0)
		appending(stack, i, envp, rl);
	else
		append_node(stack, rl, envp);
	pipe_parsing(stack, tab);
	g_exitcode = 0;
	//shell_exec2(&stack, 0);
	return (0);
}


