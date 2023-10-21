/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:00:08 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/13 16:29:52 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOI_H
# define ATOI_H

# include <limits.h>

# define CHAR_MIN_STR "-128"
# define CHAR_MAX_STR "127"
# define INT_MIN_STR "-2147483648"
# define INT_MAX_STR "2147483647"
# define LLONG_MIN_STR "-9223372036854775808"
# define LLONG_MAX_STR "9223372036854775807"

int	ft_atoc(const char *nptr);
int	ft_atol(const char *nptr);

int	ft_atoc_novf(const char *nptr, char *nb);
int	ft_atouc_novf(const char *nptr, unsigned char *nb);
int	ft_atoi_novf(const char *nptr, int *nb);
int	ft_atoll_novf(const char *nptr, long long int *nb);

#endif
