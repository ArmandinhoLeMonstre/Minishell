/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:17:19 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:13:36 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	p;

	i = 0;
	p = c;
	while (s[i])
	{
		if (s[i] == p)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == p)
		return ((char *) &s[i]);
	return (0);
}
