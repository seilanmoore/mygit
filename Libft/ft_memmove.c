/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:10:25 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/13 10:20:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr_dst;
	const char	*ptr_src;

	if (dst > src)
	{
		ptr_dst = dst + len;
		ptr_src = src + len;
		while (len-- > 0)
			*(--ptr_dst) = *(--ptr_src);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
