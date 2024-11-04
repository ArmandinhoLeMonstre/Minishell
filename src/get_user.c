/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:37:43 by armitite          #+#    #+#             */
/*   Updated: 2024/11/03 13:44:45 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path_user(t_pipe_chain *checker_node)
{
	int	i;

	i = 0;
	while (checker_node->envp[i])
	{
		if (ft_strncmp(checker_node->envp[i], "USER", 4) == 0)
			return (checker_node->envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_user(t_pipe_chain *checker_node)
{
	char	*path;

	path = ft_path_user(checker_node);
	path = ft_strchr(path, '=');
	// if (path == NULL)
	// {
	// 	return (ft_putstr_fd(checker_node->cmd[0], 2),
	// 		ft_putendl_fd(": command not found", 2), ft_free2(allpaths), NULL);
	// }
	return (path);
}