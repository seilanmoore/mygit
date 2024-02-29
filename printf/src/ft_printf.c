/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:55:29 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/29 22:31:13 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

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

static const char	*arginpos(const char *p, va_list ap_cpy, int *add)
{
	int	argn;

	p++;
	argn = 0;
	while (p[argn] != '$')
		argn++;
	argn = ft_atoi(ft_substr(p, 0, argn));
	if (!argn)
		return (0);
	p += count_digit(argn) + 1;
	while (argn-- > 1)
		va_arg(ap_cpy, char *);
	*add = ft_conversion(*p, ap_cpy);
	return (p);
}

static const char	*read_str(
	va_list *ap, va_list *ap_cpy, const char *p, int *count)
{
	int	add;

	add = 0;
	if (*p != '%' || (*p == '%' && *(p + 1) == '0'))
	{
		put_char(*p, 1);
		add = 1;
	}
	else if (ft_isdigit(*(p + 1)))
		p = arginpos(p, *ap_cpy, &add);
	else
	{
		add = ft_conversion(*(p + 1), *ap);
		p++;
	}
	if (add == -1)
	{
		*count = -1;
		return (NULL);
	}
	p++;
	*count = *count + add;
	return (p);
}

int	ft_printf(const char *format, ...)
{
	const char	*p;
	va_list		ap;
	va_list		ap_cpy;
	int			count;

	if (write(1, "", 0) == -1)
		return (-1);
	count = 0;
	va_start(ap, format);
	va_start(ap_cpy, format);
	p = format;
	while (*p)
	{
		p = read_str(&ap, &ap_cpy, p, &count);
		if (count == -1)
			return (-1);
		va_start(ap_cpy, format);
	}
	va_end(ap);
	va_end(ap_cpy);
	return (count);
}
