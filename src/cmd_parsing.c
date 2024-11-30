/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:12:41 by armitite          #+#    #+#             */
/*   Updated: 2024/11/30 22:11:39 by armitite         ###   ########.fr       */
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
	if (ft_strchr(av, '/'))
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
	return (NULL);
}

char	*get_paths(t_pipe_chain *checker_node)
{
	char	*path1;
	char	*path;
	char	**allpaths;

	path1 = NULL;
	path = ft_path(checker_node);
	if (path != NULL)
	{
		path = ft_strchr(path, '/');
		allpaths = ft_split(path, ':');
		if (checker_node->cmd != NULL)
		{
			path1 = access_check(checker_node->cmd[0], allpaths);
			if (path1 == NULL)
			{
				return (ft_free2(allpaths), NULL);
			}
			ft_free2(allpaths);
		}
	}
	return (path1);
}

void	stock_cmd(t_pipe_chain *checker_node, int h, int j)
{
	int		x;
	char	*cmd_name;
	char	*tmp;

	x = 0;
	cmd_name = malloc(sizeof(char) * (j + 1));
	while (checker_node->pipe_string[h] == ' ')
		h++;
	while (j > 0)
	{
		cmd_name[x] = checker_node->pipe_string[h];
		h++;
		j--;
		x++;
	}
	cmd_name[x] = '\0';
	if (checker_node->cmd_string == NULL)
	{
		tmp = ft_strdup(cmd_name);
		checker_node->cmd_string = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(checker_node->cmd_string, " ");
		free(checker_node->cmd_string);
		checker_node->cmd_string = ft_strjoin(tmp, cmd_name);
		free(tmp);
	}
	free(cmd_name);
}

int	cmd_check(t_pipe_chain *checker_node, int *i, int h)
{
	int	j;

	j = 0;
	while (checker_node->pipe_string[*i])
	{
		j++;
		(*i)++;
		if (ft_is_bash_char(checker_node->pipe_string[*i]) == 1)
			break ;
		if (checker_node->pipe_string[*i] == ' ')
			break ;
	}
	if (ft_is_bash_char(checker_node->pipe_string[*i]) == 1
		&& checker_node->pipe_string[*i - 1] == ' ')
		j--;
	if (checker_node->next == NULL
		&& ft_is_bash_char(checker_node->pipe_string[*i]) != 1)
		j++;
	(*i)--;
	stock_cmd(checker_node, h, j);
	return (1);
}
