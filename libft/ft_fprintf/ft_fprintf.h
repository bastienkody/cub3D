/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:09:54 by bguillau          #+#    #+#             */
/*   Updated: 2022/12/23 14:37:27 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H
# define STD_OUT 1
# define PTR_NULL "(nil)"
# define STR_NULL "(null)"

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_fprintf(int fd, const char *str, ...);
int		print_char(int fd, va_list init);
int		print_str(int fd, va_list init);
int		print_ptr(int fd, va_list init);
int		print_deci(int fd, va_list init);
int		print_unsigned(int fd, va_list init);
int		ptr_hexa(int fd, uintptr_t nbr, int *len);
int		print_hexa(int fd, va_list init, char xX);
void	ft_putunbr_fd(unsigned int n, int fd);

#endif
