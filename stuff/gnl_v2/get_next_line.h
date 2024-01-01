/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:58:00 by smoore-a          #+#    #+#             */
/*   Updated: 2024/01/01 22:16:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

//Lib for read()
# include <unistd.h>
//Lib for malloc()
# include <stdlib.h>
//Lib for printf()
# include <stdio.h>
//Libs for open()
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
int		found_nl(char *cache);
char	*create_cache(char *cache, char *buffer);
char	*extend_cache(char *cache, char *buffer);

#endif