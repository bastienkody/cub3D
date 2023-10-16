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

#ifndef CHAR_MATRIX_H
# define CHAR_MATRIX_H

# include <stdlib.h>

void	free_char_matrix(char **matrix);
void	ft_bzero_char_matrix(char **matrix, size_t n);

char	**charmatrix_dup(char **src_matrix);
char	**charmatrix_add_one(char **src_matrix, char *entry);
char	**charmatrix_del_one(char **src_matrix, char *key);
char	**charmatrix_buble_sort(char **src_matrix);

#endif
