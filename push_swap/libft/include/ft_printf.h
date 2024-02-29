/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:50:24 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/27 22:17:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *arg, ...);
void	ft_conversion(char format, va_list ap, int *count);
int		ft_hex_address(size_t address);
int		ft_uitoa(unsigned int n);
int		ft_puthex_fd(unsigned int n, int low_upper);
int		put_str(char *s, int fd);
int		put_char(int c, int fd);
int		int_itoa(int n);

#endif