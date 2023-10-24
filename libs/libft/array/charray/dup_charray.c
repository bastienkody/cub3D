/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chararray_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:05:58 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/21 19:19:00 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/* These dup functions : 
	- return a new array malloced
	- return NULL on malloc error
	- are not protected against NULL src
	- do not free src (execpt add_one that "replaces" src)
*/

static char	**get_new_array_malloced(char **src_array, int offset)
{
	int		i;
	int		len;
	char	**new_array;

	len = 0;
	i = -1;
	while (src_array && src_array[++i])
		len += 1;
	new_array = malloc((len + 1 + offset) * sizeof(char *));
	return (new_array);
}

/* dup src_array	*/
char	**charray_dup(char **src_array)
{
	int		i;
	char	**new_array;

	new_array = get_new_array_malloced(src_array, 0);
	if (!new_array)
		return (NULL);
	i = -1;
	while (src_array && src_array[++i])
	{
		new_array[i] = ft_strdup(src_array[i]);
		if (!new_array[i])
			return (free_charray(new_array), NULL);
	}
	new_array[i] = NULL;
	return (new_array);
}

/*	dup src_array + 1 (entry specific, can be null) at end	*/
char	**charray_add_one(char **src_array, char *entry)
{
	int		i;
	char	**new_array;

	new_array = get_new_array_malloced(src_array, 1);
	if (!new_array)
		return (NULL);
	i = -1;
	while (src_array && src_array[++i])
	{
		new_array[i] = ft_strdup(src_array[i]);
		if (!new_array[i])
			return (free_charray(new_array), NULL);
	}
	new_array[i++] = entry;
	new_array[i] = NULL;
	free_charray(src_array);
	return (new_array);
}

/*	dup src_array - 1 (entry specific). Segfault if entry is not in array	*/
char	**charray_del_one(char **src_array, char *entry)
{
	int		i;
	int		j;
	char	**new_array;

	new_array = get_new_array_malloced(src_array, -1);
	if (!new_array)
		return (NULL);
	i = -1;
	j = -1;
	while (src_array && src_array[++i])
	{
		if (!ft_strcmp(entry, src_array[i]))
			continue ;
		new_array[++j] = ft_strdup(src_array[i]);
		if (!new_array[j])
			return (free_charray(new_array), NULL);
	}
	new_array[++j] = NULL;
	return (new_array);
}

/* dup src_array sorted, does not free	*/
char	**charray_buble_sort(char **src_array)
{
	char	**new_array;
	char	*tmp;
	int		i;
	int		j;

	new_array = charray_dup(src_array);
	if (!new_array)
		return (NULL);
	i = -1;
	while (new_array[++i + 1])
	{
		j = 0;
		while (new_array[j + 1])
		{
			if (ft_strcmp(new_array[j], new_array[j + 1]) > 0)
			{
				tmp = new_array[j];
				new_array[j] = new_array[j + 1];
				new_array[j + 1] = tmp;
			}
			j++;
		}
	}
	return (new_array);
}
