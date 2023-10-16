/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:44:11 by bguillau          #+#    #+#             */
/*   Updated: 2022/12/23 14:38:30 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include <stdio.h>

static int	putnbr_hexa(int fd, unsigned int nbr, int *len, char c)
{
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr > 15)
		putnbr_hexa(fd, nbr / 16, len, c);
	ft_putchar_fd(base[nbr % 16], fd);
	*len += 1;
	return (*len);
}

int	ptr_hexa(int fd, uintptr_t nbr, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr > 15)
		ptr_hexa(fd, nbr / 16, len);
	ft_putchar_fd(base[nbr % 16], fd);
	*len += 1;
	return (*len);
}

int	print_hexa(int fd, va_list init, char xX)
{
	unsigned int		nbr;
	int					len;

	nbr = (unsigned int) va_arg(init, unsigned int);
	len = 0;
	if (!nbr)
		return (len + ((int) write(fd, "0", 1)));
	else
		return (putnbr_hexa(fd, nbr, &len, xX));
}
