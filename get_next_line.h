/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:27:41 by inaranjo          #+#    #+#             */
/*   Updated: 2022/11/28 14:26:50 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

/* main fonction */
char	*get_next_line(int fd);
char	*buff_read_add_to_res(int fd, char *reserve);
char	*m_reserve(char *reserve);
char    *extract_line(char *reserve);

/* link to main fonction*/
size_t  ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
char    *ft_strjoin(char *s1, char *s2);


# endif

