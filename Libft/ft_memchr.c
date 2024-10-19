/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:21:22 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:07:13 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*ss;

	cc = (unsigned char) c;
	ss = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (ss[i] == cc)
			return ((char *) &ss[i]);
		i++;
	}
	return (0);
}
