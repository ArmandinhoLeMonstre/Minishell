/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:58 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:12:19 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;

	src = s;
	i = 0;
	while (i < n)
	{
		src[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// int	main()
// {
// 	char	buffer[0];
// 	int	n;

// 	n = 5;
// 	ft_memset(buffer, 'p', sizeof(char) * n);
// 	printf("%s", buffer);
// }