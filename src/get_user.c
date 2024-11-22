/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:37:43 by armitite          #+#    #+#             */
/*   Updated: 2024/11/22 21:00:36 by armitite         ###   ########.fr       */
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
	path = ft_strdup(path + 1);
	return (path);
}