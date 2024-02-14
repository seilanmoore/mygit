/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:14:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/14 20:16:56 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;
	size_t			j;

	str2 = (unsigned char *)needle;
	str1 = (unsigned char *)haystack;
	if (!*str2)
		return ((char *)str1);
	if (*str1)
	{
		i = 0;
		while (str1[i] && i < len)
		{
			j = 0;
			while (str1[i + j] == str2[j] && str1[i + j]
				&& str2[j] && (i + j) < len)
				j++;
			if (!str2[j])
				return ((char *) &str1[i]);
			i++;
		}
	}
	return (0);
}
