/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:08:52 by bguillau          #+#    #+#             */
/*   Updated: 2022/11/21 11:16:04 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	char	*nbr;
	int		sign;
	int		res;

	nbr = (char *) nptr;
	sign = 1;
	while (*nbr == ' ' || *nbr == '\t' || *nbr == '\n' || *nbr == '\r'
		|| *nbr == '\v' || *nbr == '\f')
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	res = 0;
	while (*nbr >= '0' && *nbr <= '9')
		res = res * 10 + (*nbr++ - '0');
	return (res * sign);
}
