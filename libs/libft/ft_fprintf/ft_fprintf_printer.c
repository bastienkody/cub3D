/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:05:14 by bguillau          #+#    #+#             */
/*   Updated: 2022/12/23 14:38:12 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	print_char(int fd, va_list init)
{
	int				i;
	unsigned char	c;

	i = (int) va_arg(init, int);
	c = (unsigned char) i;
	return (write(fd, &c, 1));
}

int	print_str(int fd, va_list init)
{
	char	*str;

	str = (char *) va_arg(init, char *);
	if (!str)
		return (write(fd, STR_NULL, 6));
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	print_ptr(int fd, va_list init)
{
	void				*ptr;
	uintptr_t			num;
	int					len;

	len = 0;
	ptr = (void *) va_arg(init, void *);
	if (!ptr)
		return (write(fd, PTR_NULL, 5));
	num = (uintptr_t) ptr;
	len = write(fd, "0x", 2);
	if (!num)
		return (len + write(fd, "0", 1));
	else
		return (ptr_hexa(fd, num, &len));
}

int	print_deci(int fd, va_list init)
{
	int		n;
	int		len;

	n = (int) va_arg(init, int);
	ft_putnbr_fd(n, fd);
	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}

int	print_unsigned(int fd, va_list init)
{
	unsigned int		n;
	int					len;

	n = (unsigned int) va_arg(init, unsigned int);
	ft_putunbr_fd(n, fd);
	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}
