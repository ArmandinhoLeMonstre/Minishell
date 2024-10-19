/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:27:14 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:20:09 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	p;
	char	*l;

	i = 0;
	p = c;
	l = 0;
	while (s[i])
	{
		if (s[i] == p)
			l = ((char *) &s[i]);
		i++;
	}
	if (s[i] == p)
		l = ((char *) &s[i]);
	return (l);
}
