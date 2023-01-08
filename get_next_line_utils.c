#include "get_next_line.h"

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

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmeb > 2147483647 / size)
		return (0);
	if (nmeb != 0 && size > 2147483647 / nmeb)
		return (0);
	ptr = malloc(nmeb * size);
	if (ptr)
	{
		ft_bzero(ptr, nmeb * size);
		return (ptr);
	}
	return (ptr);
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
