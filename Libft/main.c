/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:42:05 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/04 14:32:04 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* int	main(void) //ft_bzero
{
	char	str1[30] = "Hello my name";
	char	str2[30] = "Hello my name";

	ft_bzero(str1, 5);
	printf("Using ft_bzero, the string looks like this: %s.\n", str1);
	bzero(str2, 5);
	printf("Using bzero, the string looks like this: %s.\n", str2);
	return (0);
} */

/* int	main(void) //ft_isalnum
{
	printf("Using ft_isalnum \'%c\' returns: %d.\n",
		FTALNUM, ft_isalnum(FTALNUM));
	printf("Using ft_isalnum \'%c\' returns: %d.\n",
		FTALNUM, isalnum(FTALNUM));
	return (0);
} */

/* int	main(void) //ft_isalpha
{
	printf("Using ft_isalpha \'%c\' returns: %d.\n",
		FTCHAR, ft_isalpha(FTCHAR));
	printf("Using isalpha \'%c\' returns: %d.\n",
		FTCHAR, isalpha(FTCHAR));
	return (0);
} */

/* int	main(void) //ft_isascii
{
	printf("Using ft_isascii \'%c\' returns: %d.\n",
		FTALNUM, ft_isascii(FTALNUM));
	printf("Using ft_isascii \'%c\' returns: %d.\n",
		FTALNUM, isascii(FTALNUM));
	return (0);
} */

/* int	main(void) //ft_isdigit
{
	printf("Using ft_isdigit \'%c\' returns: %d.\n",
		FTDIGIT, ft_isdigit(FTDIGIT));
	printf("Using isdigit \'%c\' returns: %d.\n",
		FTDIGIT, isdigit(FTDIGIT));
	return (0);
} */

/* int	main(void) //ft_isprint
{
	printf("Using ft_isprint \'%c\' returns: %d.\n",
		FTALNUM, ft_isprint(FTALNUM));
	printf("Using ft_isprint \'%c\' returns: %d.\n",
		FTALNUM, isprint(FTALNUM));
	return (0);
} */

/* int	main(void) //ft_memcpy
{
	char	src[30] = "Start stop";

	ft_memcpy(src + 2, src, 3);
	printf("Using memcpy, the string looks like this: %s.\n", src);
	return (0);
} */

/* int	main(void) //ft_memmove
{
	char	src[] = "0123456789";
	char	src1[] = "0123456789";

	printf("The prev srt is: %s.\n", src);
	ft_memmove(src, src + 3, 2);
	printf("The next srt is: %s.\n", src);
	printf("The prev srt is: %s.\n", src1);
	memmove(src1, src1 + 3, 2);
	printf("The next srt is: %s.\n", src1);
	return (0);
} */

/* int	main(void) //ft_memset
{
	char	str1[30] = "";
	char	str2[30] = "";

	printf("Using ft_memset, the string looks like this: %s.\n",
		ft_memset(str1, 'B', 5));
	printf("Using memset, the string looks like this: %s.\n",
		memset(str2, 'B', 5));
	return (0);
} */

/* int	main(void) //ft_strlcpy
{
	char	*src1;
	char	dst1[0] = "";
	char	*src2;
	char	dst2[0] = "";

	src1 = "aaa";
	src2 = "aaa";
	ft_strlcpy(dst1, src1, 0);
	printf("Using ft_strlcpy, the string looks like this: %s. "
		"And the size of the src is : %lu.\n", dst1, ft_strlcpy(dst1, src1, 0));
	strlcpy(dst2, src2, 0);
	printf("Using strlcpy, the string looks like this: %s. "
			"Size of the src is : %lu.\n",
			dst2,
			strlcpy(dst2, src2, 0));
	return (0);
} */

/* int	main(void) //ft_strlen
{
	char	*str = "fefefefe";

	printf("Using ft_strlen, the lengnth is: %lu.\n", ft_strlen(str));
	printf("Using strlen, the lengnth is: %lu.\n", strlen(str));
	return (0);
} */

/* int	main(void) //ft_strlcat
{
	char	dest[10] = "A";
	size_t	full_len = ft_strlcat(dest, "lorem ipsum dolor sit amet", 0);

	printf("Concatenated string: \"%s\"\n", dest);
	printf("Total size if not truncated: %lu\n", full_len);
	return (0);
} */

/* int	main(void) //ft_toupper
{
	char	str[] = "What eVeR.";
	int		i = 0;

	printf("Using ft_toupper \'%s\'\n", str);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("Returns: %s\n", str);
	return (0);
} */

/* int	main(void) //ft_tolower
{
	char	str[] = "What eVeR.";
	int		i = 0;

	printf("Using ft_tolower \'%s\'\n", str);
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	printf("Returns: %s\n", str);
	return (0);
} */

/* int	main(void) //ft_strchr
{
	char	str[] = "teste";
	char	stro[] = "teste";

	printf("Using ft_strchr want to find \'%c\' in the"
		" string \'%s\'\n", 'a', str);
	printf("Returns: %s\n", ft_strchr(str, 1024));
	printf("Using strchr want to find \'%c\' in the"
		" string \'%s\'\n", 'a', str);
	printf("Returns: %s\n", strchr(stro, 1024));

	printf("%c\n", 357);
	return (0);
} */
