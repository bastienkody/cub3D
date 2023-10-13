/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:36:33 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/21 11:19:42 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	n_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len += 1;
	while (n / 10)
	{
		len += 1;
		n /= 10;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	nb;
	int				len;

	len = n_len(n);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		*res = '-';
		nb = n * -1;
	}
	else
		nb = n;
	res[len] = '\0';
	while (nb / 10)
	{
		res[--len] = nb % 10 + '0';
		nb /= 10;
	}
	res[--len] = nb % 10 + '0';
	return (res);
}
