/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:44:48 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 14:21:47 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	if (!haystack && len == 0)
		return (0);
	i = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		l = 0;
		while (haystack[i + l] && haystack[i + l] == needle[l] && l + i < len)
		{
			if (needle[l + 1] == 0)
				return ((char *) &haystack[i]);
			l++;
		}
		i++;
	}
	return (0);
}
