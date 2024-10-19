/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:33:58 by armitite          #+#    #+#             */
/*   Updated: 2024/05/14 13:05:42 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int x)
{
	int	i;

	i = 1;
	if (x < 0)
	{
		x = x * -1;
		i++;
	}
	while (x > 9)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str, int i)
{
	int	j;
	int	tmp;

	j = 0;
	if (!ft_isdigit(str[0]))
		j++;
	while (i > j)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		i--;
		j++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			i;
	long int	x;

	i = 1;
	x = n;
	i = ft_count(x);
	res = malloc((i + 1) * (sizeof(char)));
	if (!res)
		return (0);
	i = 0;
	if (x < 0)
	{
		res[i++] = '-';
		x = x * -1;
	}
	while (x > 9)
	{
		res[i++] = (x % 10) + 48;
		x /= 10;
	}
	res[i] = x + 48;
	res = ft_strrev(res, i);
	res[++i] = '\0';
	return (res);
}

// int	main()
// {
// 	int	h;

// 	h = -2147483648;
// 	printf("%s", ft_itoa(h));
// }