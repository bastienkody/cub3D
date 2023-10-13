/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_char_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:39:00 by bguillau          #+#    #+#             */
/*   Updated: 2023/03/24 16:43:26 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_matrix.h"

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
