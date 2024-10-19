/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:40:40 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 14:31:11 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	if (!dst && dstsize == 0)
		return (0);
	i = -1;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= dstsize)
		dst_len = dstsize;
	if (dstsize == dst_len)
		return (src_len + dstsize);
	if (dstsize - dst_len > src_len)
	{
		while (src[++i] != '\0')
			dst[dst_len + i] = src[i];
	}
	else
	{
		while (++i < dstsize - dst_len - 1)
			dst[dst_len + i] = src[i];
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
