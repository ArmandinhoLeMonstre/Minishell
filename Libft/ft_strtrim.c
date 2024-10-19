/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:34 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 14:15:57 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checkend(const char *s1, const char *set, size_t pl)
{
	size_t	i;
	size_t	j;

	i = pl;
	j = 0;
	i--;
	while (set[j])
	{
		if (set[j] == s1[i])
		{
			j = -1;
			i--;
		}
		j++;
	}
	return (pl - i - 1);
}

static size_t	ft_checkstart(const char *s1, const char *set, size_t pl)
{
	size_t	i;
	size_t	j;

	i = pl;
	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
		{
			j = -1;
			i++;
		}
		j++;
	}
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*res;
	size_t	len;
	size_t	x;
	size_t	y;
	size_t	i;

	if (!s1)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	x = ft_checkstart(s1, set, i);
	y = ft_checkend(s1, set, len);
	if (x == len)
		y = 0;
	res = malloc((len - (x + y)) * sizeof(char) + 1);
	if (!res)
		return (0);
	while (x < len - y)
		res[i++] = s1[x++];
	res[i] = '\0';
	return (res);
}

// int main()
// {
// 	char *s1 = " \t \t \n  \n\n\n\t";
// 	printf("%s", ft_strtrim(s1, " \t\n"));
// }
