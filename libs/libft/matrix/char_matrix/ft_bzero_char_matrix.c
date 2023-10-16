/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:36:03 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/11 16:11:02 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero_char_matrix(char **matrix, size_t n)
{
	if (!n || !matrix)
		return ;
	while (--n)
		matrix[n] = NULL;
	matrix[n] = NULL;
}
