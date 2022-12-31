#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* read keeps iterating i cannot call it twice
  */

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (ft_strlen(src));
	else
	{
		while (index < (size - 1) && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
		return (ft_strlen(src));
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (start >= ft_strlen(s))
	{
		ptr = ft_calloc(1, 1);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (len + start > ft_strlen(s))
	{
		ptr = ft_calloc(ft_strlen(s) + 1 - start, 1);
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr, s + start, ft_strlen(s) + 1 - start);
	}
	else
	{
		ptr = ft_calloc(len + 1, 1);
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr, s + start, len + 1);
	}
	return (ptr);
}

char write_to_buffer(char *buf, buf_size)
{
  int i;
  char c;

  i = 0;
  read(fd, &c, 1);
  while (c != '\n' && i < buf_size)
  {
    buf[i] = c;
    // printf("%c\n", c);
    read(fd, &c, 1);
    i++;
  }
  return (c);
}

char *get_next_line(int fd)
{
  int buf_size;
  char *buf;
  char *str;
  char c;

  buf_size = 20;
  buf = malloc(buf_size);
  c = 0;
  while (c != '\n')
  {
    c = write_to_buffer(buf, buf_size);
    str = ft_calloc(buf_size, 1);
    ft_strlcpy(str, buf, buf_size);
  }
}


// char *get_next_line(int fd)
// {
//   int buf_size;
//   char c;
//   int i;
//   char *buf;
//   char *str;
//
//   buf_size = 20;
//   i = 0;
//   buf = malloc(buf_size);
//   read(fd, &c, 1);
//   while (c != '\n' && i < buf_size)
//   {
//     buf[i] = c;
//     // printf("%c\n", c);
//     read(fd, &c, 1);
//     i++;
//   }
//   // printf("%s\n", buf);
//   // printf("%i\n", i);
//   // printf("%c\n", c);
//   if (c != '\n')
//   {
//     str = ft_calloc((i + 1)*2, 1);
//     ft_strlcpy(str, buf, i + 1);
//     printf("%s\n", str);
//     buf = ft_calloc(buf_size, 1);
//     i = 0;
//     while (c != '\n')
//     {
//       buf[i] = c;
//       read(fd, &c, 1);
//       i++;
//     }
//     printf("%s\n", buf);
//     printf("%i\n", i);
//     ft_strlcpy(str + buf_size, buf, i + 1);
//   }
//   else
//   {
//     str = malloc(i + 1);
//     ft_strlcpy(str, buf, i + 1);
//   }
//   free(buf);
//   printf("%s\n", str);
// }

#include <fcntl.h>

int main()
{
  int fd;

  fd = open("test", O_RDONLY);
  get_next_line(fd);
  get_next_line(fd);
  // printf("%s\n", get_next_line(fd));
  close(fd);
}
