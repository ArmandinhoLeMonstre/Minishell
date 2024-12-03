/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:34:42 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 09:58:34 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s || s[start] == '\0')
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len < ft_strlen(&s[start]))
	{
		dst = ft_calloc(len + 1, sizeof(char));
		if (!dst)
			return (NULL);
		if (start > ft_strlen(s))
			return (dst);
		ft_strlcpy(dst, &s[start], len + 1);
	}
	else
	{
		dst = ft_calloc(ft_strlen(&s[start]) + 1, sizeof(char));
		if (!dst)
			return (NULL);
		if (start > ft_strlen(s))
			return (dst);
		ft_strlcpy(dst, &s[start], ft_strlen(s) + 1);
	}
	return (dst);
}
