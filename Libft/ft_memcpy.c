/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:13:50 by armitite          #+#    #+#             */
/*   Updated: 2024/05/05 17:47:50 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*char_dst;
	char	*char_src;

	i = 0;
	char_dst = (char *) dst;
	char_src = (char *) src;
	if (dst == 0 && src == 0)
		return (dst);
	while (n > i)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	return (dst);
}

// int	main()
// {
// 	char	m[] = "Manger";
// 	char	c[100];

// 	memcpy(m+2, m, 5);
// 	printf("%s", m);
// 	return(0);
// }