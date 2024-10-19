/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:51:26 by armitite          #+#    #+#             */
/*   Updated: 2024/07/25 18:59:19 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_wordup(char const *s, char c)
{
	int		i;
	char	*tab;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

static void	*ft_free(char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static	char	**ft_cpysplit(char	**split, char const *s, char c)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			split[j] = ft_wordup(&s[i], c);
			if (!split[j])
				return (ft_free(split, j));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**split;

	if (!s)
		return (0);
	size = ft_wordcount(s, c);
	split = ft_calloc(sizeof(char *), size + 1);
	if (!split)
		return (0);
	split[size] = 0;
	return (ft_cpysplit(split, s, c));
}
