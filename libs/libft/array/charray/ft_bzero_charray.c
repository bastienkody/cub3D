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

void	ft_bzero_charray(char **array, size_t n)
{
	if (!n || !array)
		return ;
	while (--n)
		array[n] = NULL;
	array[n] = NULL;
}
