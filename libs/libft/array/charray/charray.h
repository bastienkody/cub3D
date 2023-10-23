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

#ifndef CHARRAY_H
# define CHARRAY_H

# include <stdlib.h>

void	free_charray(char **array);
void	ft_bzero_charray(char **array, size_t n);

char	**charray_dup(char **src_array);
char	**charray_add_one(char **src_array, char *entry);
char	**charray_del_one(char **src_array, char *key);
char	**charray_buble_sort(char **src_array);

#endif
