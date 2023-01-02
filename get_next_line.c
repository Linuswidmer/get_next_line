#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* read keeps iterating so i cannot call it twice
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

int	search_new_line(const char *s, int buf_size)
{
  int i;

  i = 0;
	while (i <= buf_size)
	{
		if (((char *)s)[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char *buf_to_str(char *str, char *buf, int buf_size, int iteration, int end)
{
  char *str_new;

  str_new = ft_calloc(buf_size * iteration + end + 1, 1);
  ft_strlcpy(str_new, str, ft_strlen(str) + 1);
  ft_strlcat(str_new, buf, buf_size * iteration + end + 1);
  free (str);
  return (str_new);
}

char *no_line_in_buffer(char *buf, int *pos, int buf_size, int fd)
{
  int beginning;
  int position;
  int iteration;
  int next_line;
  char *str;

  iteration = 1;
  beginning = 0;
  next_line = 0;
  position = *pos;
  str = ft_calloc(buf_size, 1);
  if (!str)
    return (NULL);
  if (position != 0)
    beginning = buf_size - position;
  while (search_new_line(buf + position, buf_size) - 1 == buf_size)
  {
    printf("Buffer is: %s\n", buf);
    str = buf_to_str(str, buf + position, buf_size, iteration, beginning);
    if (position != 0)
       iteration --;
    printf("Current string is: %s\n", str);
    iteration++;
    read(fd, buf, buf_size);
    printf("Buffer read\n");
    position = 0;
    printf("Iteration count: %i\n", iteration);
  }
  printf("Iteration count is: %i\n", iteration);
  next_line = search_new_line(buf + position, buf_size);
  printf("Last line is: %i chars long\n", next_line);
  str = buf_to_str(str, buf, buf_size, iteration - 1, next_line + 1 + beginning); // + 1 for the newline
  printf("Line is: %s\n", str);
  *pos = next_line + 1;
  printf("Position is: %i\n", position);
}

char *line_in_buffer(char *buf, int *pos, int buf_size)
{
  int next_line;
  char *str;
  int  position;

  position = *pos;
  printf("New line found in buffer\n");
  next_line = search_new_line(buf + position, buf_size);
  printf("End of next line is %i\n", next_line + position);  
  printf("Line lenght is %i\n", next_line);
  str = ft_calloc(next_line + 1, 1);
  if (!str)
    return (NULL);
  ft_strlcpy(str, buf + position, next_line + 2);
  printf("Line is: %s\n", str);
  *pos = position + next_line + 1;
  return (str);
}

char *get_next_line(int fd)
{
  int buf_size;
  char *buf;
  static int position;

  buf_size = 50;
  printf("Position is: %i\n", position);
  if (position == 0)
  {
    buf = ft_calloc(buf_size, 1);
    printf("Buffer allocated\n");
    read(fd, buf, buf_size);
    printf("Buffer read\n");
  }
  if (search_new_line(buf + position, buf_size) < buf_size)
  {
    return(line_in_buffer(buf, &position, buf_size));
  }
  else
  {
    return(no_line_in_buffer(buf, &position, buf_size, fd));
  }
}


#include <fcntl.h>

int main()
{
  int fd;

  fd = open("test", O_RDONLY);
  get_next_line(fd);
  get_next_line(fd);
  get_next_line(fd);
  // printf("%s\n", get_next_line(fd));
  close(fd);
}
