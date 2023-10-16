/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:10:27 by bguillau          #+#    #+#             */
/*   Updated: 2022/12/01 14:23:08 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# define TRIG -1

int		strle(const char *s);
int		idx_of(char *buf, char c);
int		itrig(char *buf);
void	clr_buf(char buf[], int j, char val);
char	*init(char **line, char buf[], int *eof);
char	*finall(char *line, char buf[], int eof);
char	*get_next_line(int fd);
char	*strj(char *s1, char *s2);
char	*subs(char *s, int start, int len);

#endif
