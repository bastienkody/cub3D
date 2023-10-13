/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:39:35 by bguillau          #+#    #+#             */
/*   Updated: 2023/03/24 17:30:57 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_matrix.h"

void	free_int_matrix(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(matrix[i++]);
	free(matrix);
}
