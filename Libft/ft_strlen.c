/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:51:25 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:15:53 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
		i++;
	return (i);
}

// #include <stdio.h>
// int	main()
// {
// 	char	m[] = "";
// 	printf("%zu", ft_strlen(m));

// 	return (0);
// }