/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll_nvof.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:46:31 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/09 17:46:33 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../libft.h"

static	int	check_overflow(char nb, char nptr, int sign)
{
	char	next_nb;

	if (sign > 0)
		next_nb = nb * 10 + (nptr - '0');
	else
		next_nb = nb * 10 - 1 + (nptr - '0');
	if (next_nb < nb)
		return (0);
	return (1);
}

int	ft_atoc_novf(const char *nptr, char *nb)
{
	int		sign;

	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	*nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (*nb >= (CHAR_MAX / 10) && !check_overflow(*nb, *nptr, sign))
			return (0);
		*nb = *nb * 10 + (*nptr++ - '0');
	}
	*nb = *nb * sign;
	return (1);
}
