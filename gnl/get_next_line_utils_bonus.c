/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:33:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/02/20 14:52:42 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*found_nl(char *cache)
{
	int	i;

	i = 0;
	while (cache[i] && cache[i] != '\n')
		i++;
	return (&cache[i]);
}

char	*create_cache(char *cache, char *buffer)
{
	size_t	final_size;
	int		i;

	final_size = ft_strlen(buffer) + 1;
	cache = (char *)malloc(final_size * sizeof(char));
	if (!cache)
		return (NULL);
	i = -1;
	while (buffer[++i])
		cache[i] = buffer[i];
	cache[i] = '\0';
	return (cache);
}

char	*extend_cache(char *cache, char *buffer)
{
	size_t	final_size;
	int		i;
	int		j;
	char	*temp;

	if (!cache)
		return (create_cache(cache, buffer));
	final_size = ft_strlen(cache) + ft_strlen(buffer) + 1;
	temp = (char *)malloc(final_size * sizeof(char));
	if (!temp)
	{
		free(cache);
		return (NULL);
	}
	i = -1;
	while (cache[++i])
		temp[i] = cache[i];
	j = -1;
	while (buffer[++j])
		temp[i++] = buffer[j];
	temp[i] = '\0';
	free(cache);
	return (temp);
}

void	free_cache(char **cache)
{
	int	i;

	i = 1024;
	while (--i >= 0)
	{
		if (cache[i])
			free(cache[i]);
	}
}
