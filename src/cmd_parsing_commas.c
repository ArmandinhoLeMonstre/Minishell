/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_commas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:13:12 by armitite          #+#    #+#             */
/*   Updated: 2024/11/05 18:25:31 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stock_cmd_commas(t_pipe_chain *checker_node, int h, int j)
{
	int		x;
	char	*cmd_name;
	//char	**cmd_tmp;

	x = 0;
	//printf("ici");
	cmd_name = malloc(sizeof(char) * (j + 1));
	// while (checker_node->pipe_string[h] == ' ')
	// 	h++;
	while (j > 0)
	{
		cmd_name[x] = checker_node->pipe_string[h];
		printf("%c char de la cmd\n", cmd_name[x]);
		h++;
		j--;
		x++;
	}
	// if (cmd_name[x] != ' ')
	// {
	// 	cmd_name[x] = ' ';
	// 	x++;
	// }
	printf(("la cmd %s\n"), cmd_name);
	printf(("la cmd %d\n"), h);
	cmd_name[x] = '\0';
	if (checker_node->cmd_string == NULL)
	{
		checker_node->cmd_string = ft_strdup(cmd_name);
	}
	else
		checker_node->cmd_string = ft_strjoin(checker_node->cmd_string, cmd_name);
	//cmd_tmp = ft_split(cmd_name, ' ');
	// checker_node->cmd = ft_split(checker_node->cmd_string, ' ');
	// checker_node->cmd_path = get_paths(checker_node);
	// printf("le path :%s\n", checker_node->cmd_path);
	// printf("la cmd :%s\n", checker_node->cmd[0]);
	x = 0;
	// while (cmd_name[x])
	// {
		//printf(("la cmd %s\n"), cmd_name[x]);
		//x++;
	// }
	// if (!cmd_tmp)
	// 	free les trucs
}

int	cmd_check_commas(t_pipe_chain *checker_node, int *i, int h, int	keycode)
{
	int	j;
	
	j = 0;
	if (keycode == 1)
	{
		while (checker_node->pipe_string[*i] != 34)
		{
			j++;
			(*i)++;
			// if (checker_node->pipe_string[*i] == ' ')
			// 	break ;
		}
	}
	else
	{
		while (checker_node->pipe_string[*i] != 39)
		{
			j++;
			(*i)++;
			// if (checker_node->pipe_string[*i] == ' ')
			// 	break ;
		}
	}
	// if (ft_is_bash_char(checker_node->pipe_string[*i]) == 1 && checker_node->pipe_string[*i - 1] == ' ')
	// 	j--;
	// if (checker_node->next == NULL)
	// 	j++;
	//(*i)--;
	printf("le j commas : %d\n", j);
	stock_cmd_commas(checker_node, h, j);
	return (1);
}