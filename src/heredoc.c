/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:08:25 by armitite          #+#    #+#             */
/*   Updated: 2024/10/24 18:44:14 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd2(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

void	display_line(t_pipe_chain *checker_node)
{
	char	*line;
	int		len;

	line = ft_strdup("");
	len = ft_strlen(checker_node->heredoc_chars);
	if (pipe(checker_node->fd) == -1)
		exit(1);
	while(1)
	{
		line = readline ("> ");
		if(ft_strcmp(line, checker_node->heredoc_chars) == 0)
		{
			close(checker_node->fd[1]);
			break;
		}
		ft_putstr_fd2(line, checker_node->fd[1]);
		ft_putstr_fd2("\n", checker_node->fd[1]);
	}
	// dup2(checker_node->fd[0], 0);
	//execve(checker_node->cmd_path, checker_node->cmd, checker_node->envp);
}