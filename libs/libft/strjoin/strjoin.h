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

#ifndef STRJOIN_H
# define STRJOIN_H

# include "../libft.h"

/*	two strings	*/
char	*strjoin_f1(const char *s1, const char *s2);
char	*strjoin_f2(const char *s1, const char *s2);
char	*strjoin_fall(const char *s1, const char *s2);

/*	three strings	*/
char	*strjoin3(char const *s1, char const *s2, char const *s3);
char	*strjoin3_f1(char const *s1, char const *s2, char const *s3);
char	*strjoin3_f2(char const *s1, char const *s2, char const *s3);
char	*strjoin3_f3(char const *s1, char const *s2, char const *s3);
char	*strjoin3_fall(char const *s1, char const *s2, char const *s3);

/*	string + char	*/
char	*strjoin_char(char *str, char c);
char	*strjoin_char_fstr(char *str, char c);

/*	superjoin va	*/
char	*superjoin(char const *s1, ...);
char	*superjoin_fall(char const *s1, ...);

/*	superjoin tab	*/
char	*superjoin_tab(char **tab);
char	*superjoin_tab_fall(char **tab);

#endif
