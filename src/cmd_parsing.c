/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:12:41 by armitite          #+#    #+#             */
/*   Updated: 2024/11/05 15:19:28 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path(t_pipe_chain *checker_node)
{
	int	i;

	i = 0;
	while (checker_node->envp[i])
	{
		if (ft_strncmp(checker_node->envp[i], "PATH", 4) == 0)
			return (checker_node->envp[i]);
		i++;
	}
	return (NULL);
}

char	*access_check(char *av, char **allpaths)
{
	int		i;
	char	*joinpaths;
	char	*tmp;

	i = 0;
	if (!av)
		return (NULL);
	if (access(av, X_OK) == 0)
		return (av);
	while (allpaths[i])
	{
		joinpaths = ft_strjoin(allpaths[i], "/");
		tmp = joinpaths;
		joinpaths = ft_strjoin(joinpaths, av);
		free(tmp);
		if (access(joinpaths, X_OK) == 0)
			return (joinpaths);
		i++;
		free(joinpaths);
	}
	//ft_free2(allpaths);
	return (NULL);
}

char	*get_paths(t_pipe_chain *checker_node)
{
	char	*path1;
	char	*path;
	char	**allpaths;

	path = ft_path(checker_node);
	path = ft_strchr(path, '/');
	allpaths = ft_split(path, ':');
	path1 = access_check(checker_node->cmd[0], allpaths);
	if (path1 == NULL)
	{
		return (ft_putstr_fd(checker_node->cmd[0], 2),
			ft_putendl_fd(": command not found", 2), ft_free2(allpaths), NULL);
	}
	ft_free2(allpaths);
	return (path1);
}

void	stock_cmd(t_pipe_chain *checker_node, int h, int j)
{
	int		x;
	char	*cmd_name;
	//char	**cmd_tmp;

	x = 0;
	//printf("ici");
	cmd_name = malloc(sizeof(char) * (j + 1));
	while (checker_node->pipe_string[h] == ' ')
		h++;
	while (j > 0)
	{
		cmd_name[x] = checker_node->pipe_string[h];
		printf("%c char de la cmd\n", cmd_name[x]);
		h++;
		j--;
		x++;
	}
	if (cmd_name[x] != ' ')
	{
		cmd_name[x] = ' ';
		x++;
	}
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

int	cmd_check(t_pipe_chain *checker_node, int *i, int h)
{
	int	j;
	
	j = 0;
	while (checker_node->pipe_string[*i] && (ft_is_bash_char(checker_node->pipe_string[*i]) != 1))
	{
		j++;
		(*i)++;
		if (checker_node->pipe_string[*i] == ' ')
			break ;
	}
	if (ft_is_bash_char(checker_node->pipe_string[*i]) == 1 && checker_node->pipe_string[*i - 1] == ' ')
		j--;
	if (checker_node->next == NULL)
		j++;
	(*i)--;
	printf("le j : %d\n", j);
	stock_cmd(checker_node, h, j);
	return (1);
}