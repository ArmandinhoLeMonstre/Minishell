/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_noding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:50:07 by armitite          #+#    #+#             */
/*   Updated: 2024/12/02 18:01:22 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_node(t_pipe_chain	*node, char *rl, char **envp)
{
	node->next = NULL;
	node->pipe_string = ft_strdup(rl);
	node->cmd_path = NULL;
	node->cmd = NULL;
	node->envp = envp;
	node->infile = 0;
	node->checker_in_here = 0;
	node->outfile = 0;
	node->append = 0;
	node->heredoc_chars = ft_strdup("");
	node->cmd_string = NULL;
}

void	append_node(t_pipe_chain **stack, char *rl, char **envp)
{
	t_pipe_chain	*node;
	t_pipe_chain	*last_node;

	node = malloc(sizeof(t_pipe_chain));
	allocate_node(node, rl, envp);
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

int	appending(t_pipe_chain **stack, int i, char **envp, char *rl)
{
	char	**split_rl;

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
	return (0);
}

int	pipe_noding(t_pipe_chain **stack, t_env **env, char *rl, char **envp)
{
	int				i;
	int				*tab;

	i = 0;
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
	pipe_parsing(stack, tab, env);
	g_exitcode = 0;
	return (0);
}
