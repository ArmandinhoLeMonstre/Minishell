/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:44:24 by armitite          #+#    #+#             */
/*   Updated: 2024/05/04 16:33:18 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 127 && c >= 32)
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main()
// {
// 	int	k;

// 	k = '\n';
// 	printf("%d", ft_isprint(k));

// 	return (0);
// }