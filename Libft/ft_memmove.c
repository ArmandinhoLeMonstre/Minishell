/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:00:04 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:46:33 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*p_dst;
	char	*p_src;
	size_t	i;

	if (dst == 0 && src == 0)
		return (dst);
	p_dst = (char *) dst;
	p_src = (char *) src;
	i = 0;
	if (p_dst > p_src)
	{
		while (len-- > 0)
			p_dst[len] = p_src[len];
	}
	else
	{
		while (i < len)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	return (dst);
}
