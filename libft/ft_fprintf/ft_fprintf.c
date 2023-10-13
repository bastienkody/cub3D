/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:09:34 by bguillau          #+#    #+#             */
/*   Updated: 2022/12/23 11:28:16 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include <stdio.h>

static int	format(int fd, const char *str, int i, va_list init)
{
	int	len;

	len = 0;
	if (str[i + 1] == 'c')
		len = print_char(fd, init);
	if (str[i + 1] == '%')
		len = write(fd, "%", 1);
	if (str[i + 1] == 's')
		len = print_str(fd, init);
	if (str[i + 1] == 'p')
		len = print_ptr(fd, init);
	if (str[i + 1] == 'd' || str[i + 1] == 'i')
		len = print_deci(fd, init);
	if (str[i + 1] == 'x')
		len = print_hexa(fd, init, 'x');
	if (str[i + 1] == 'X')
		len = print_hexa(fd, init, 'X');
	if (str[i + 1] == 'u')
		len = print_unsigned(fd, init);
	return (len);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	init;
	int		i;
	int		len;

	va_start(init, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '%')
			len += write(fd, &str[i++], 1);
		if (str[i] && str[i] == '%')
		{
			len += format(fd, str, i, init);
			i += 2;
		}
	}
	va_end(init);
	return (len);
}
