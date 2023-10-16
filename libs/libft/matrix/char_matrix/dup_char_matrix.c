/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charmatrix_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:05:58 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/21 19:19:00 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/* These dup functions : 
	- return a new matrix malloced
	- return NULL on malloc error
	- are not protected against NULL src
	- do not free src
*/

static char	**get_new_matrix_malloced(char **src_matrix, int offset)
{
	int		i;
	int		len;
	char	**new_matrix;

	len = 0;
	i = -1;
	while (src_matrix && src_matrix[++i])
		len += 1;
	new_matrix = malloc((len + 1 + offset) * sizeof(char *));
	return (new_matrix);
}

/* dup src_matrix	*/
char	**charmatrix_dup(char **src_matrix)
{
	int		i;
	char	**new_matrix;

	new_matrix = get_new_matrix_malloced(src_matrix, 0);
	if (!new_matrix)
		return (NULL);
	i = -1;
	while (src_matrix && src_matrix[++i])
	{
		new_matrix[i] = ft_strdup(src_matrix[i]);
		if (!new_matrix[i])
			return (free_char_matrix(new_matrix), NULL);
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

/*	dup src_matrix + 1 (entry specific, can be null) at end	*/
char	**charmatrix_add_one(char **src_matrix, char *entry)
{
	int		i;
	char	**new_matrix;

	new_matrix = get_new_matrix_malloced(src_matrix, 1);
	if (!new_matrix)
		return (NULL);
	i = -1;
	while (src_matrix && src_matrix[++i])
	{
		new_matrix[i] = ft_strdup(src_matrix[i]);
		if (!new_matrix[i])
			return (free_char_matrix(new_matrix), NULL);
	}
	new_matrix[i++] = entry;
	new_matrix[i] = NULL;
	free_char_matrix(src_matrix);
	return (new_matrix);
}

/*	dup src_matrix - 1 (entry specific). Segfault if entry is not in matrix	*/
char	**charmatrix_del_one(char **src_matrix, char *entry)
{
	int		i;
	int		j;
	char	**new_matrix;

	new_matrix = get_new_matrix_malloced(src_matrix, -1);
	if (!new_matrix)
		return (NULL);
	i = -1;
	j = -1;
	while (src_matrix && src_matrix[++i])
	{
		if (!ft_strcmp(entry, src_matrix[i]))
			continue ;
		new_matrix[++j] = ft_strdup(src_matrix[i]);
		if (!new_matrix[j])
			return (free_char_matrix(new_matrix), NULL);
	}
	new_matrix[++j] = NULL;
	return (new_matrix);
}

/* dup src_matrix sorted, does not free	*/
char	**charmatrix_buble_sort(char **src_matrix)
{
	char	**new_matrix;
	char	*tmp;
	int		i;
	int		j;

	new_matrix = charmatrix_dup(src_matrix);
	if (!new_matrix)
		return (NULL);
	i = -1;
	while (new_matrix[++i + 1])
	{
		j = 0;
		while (new_matrix[j + 1])
		{
			if (ft_strcmp(new_matrix[j], new_matrix[j + 1]) > 0)
			{
				tmp = new_matrix[j];
				new_matrix[j] = new_matrix[j + 1];
				new_matrix[j + 1] = tmp;
			}
			j++;
		}
	}
	return (new_matrix);
}
