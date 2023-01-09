/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:51:53 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/09 11:52:07 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_buffer(char **buf)
{
	free(*buf);
	*buf = 0;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < n)
		{
			((char *)s)[i] = '\0';
			i++;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest && src)
	{
		if (dest >= src)
		{
			while (n-- > 0)
				((char *)dest)[n] = ((char *)src)[n];
		}
		else
		{
			while (i < n)
			{
				((char *)dest)[i] = ((char *)src)[i];
				i++;
			}
		}
	}
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	result;

	i = 0;
	j = 0;
	if (size > ft_strlen(dest))
		result = ft_strlen(src) + ft_strlen(dest);
	else
		return (ft_strlen(src) + size);
	while (dest[i] != '\0')
		i++;
	if (size != 0)
	{
		while (src[j] != '\0' && i < size - 1)
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		dest[i] = '\0';
	}
	return (result);
}
