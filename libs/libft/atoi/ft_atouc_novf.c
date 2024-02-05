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

/*	unsigned char	*/
int	ft_atouc_novf(const char *nptr, unsigned char *nb)
{
	unsigned	old_nb;

	if (ft_strlen(nptr) > 3 || ft_atoi(nptr) > 255)
		return (0);
	if (*nptr == '+')
		nptr++;
	*nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		old_nb = *nb;
		*nb = *nb * 10 + (*nptr++ - '0');
		if (old_nb > *nb)
			return (0);
	}
	return (1);
}
