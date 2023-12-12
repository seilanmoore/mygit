/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:40:52 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/12 17:50:56 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*nbr;

	len = count_digit(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[len--] = '\0';
	if (n == 0)
	{
		*nbr = '0';
		return (nbr);
	}
	if (n < 0)
		*nbr = '-';
	while (n != 0)
	{
		if (*nbr == '-')
			nbr[len--] = '0' + -(n % 10);
		else
			nbr[len--] = '0' + (n % 10);
		n /= 10;
	}
	return (nbr);
}
