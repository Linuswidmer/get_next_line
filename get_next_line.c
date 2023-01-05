#include "get_next_line.h"

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

int	search_new_line(const char *s)
{
  int i;

  i = 0;
	while (s[i] != '\n' && i <= BUFFER_SIZE)
	{
		i++;
	}
	return (i);
}

char *buf_to_str(char *str, char *buf, int size)
{
  char *str_new;

  // if (size == 0)
  //   return (NULL);
  str_new = ft_calloc(ft_strlen(str) + size + 1, 1);
  ft_strlcpy(str_new, str, ft_strlen(str) + 1);
  ft_strlcat(str_new, buf, ft_strlen(str) + size + 1);
  free (str);
  return (str_new);
}

char *line_in_buffer(char *buf, char *str, ssize_t read_return)
{
  int next_line;
  int buf_len;

  printf("Line in Buffer\n");
  // if (read_return == 0 && ft_strlen(str) == 0)
  //   return (NULL);
  // else if (read_return == 0)
  // {
  //   ft_bzero(buf, ft_strlen(buf));
  //   return (str);
  // }
  // else if (read_return < BUFFER_SIZE && search_new_line(buf) == ft_strlen(buf))
  //     next_line = read_return;
  // else
  //   next_line = search_new_line(buf) + 1;
  next_line = search_new_line(buf) + 1;

  buf_len = ft_strlen(buf);
  str = buf_to_str(str, buf, next_line); // + 1 for the newline
  buf = ft_memmove(buf, buf + next_line, buf_len - next_line);
  ft_bzero(buf + (buf_len - next_line), next_line);
  return (str);
}

char *no_line_in_buffer(char *buf, ssize_t read_return, int fd)
{
  char *str;

  printf("No Line in buffer\n");
  str = ft_calloc(ft_strlen(buf) + 1, 1);
  if (!str)
    return (NULL);
  str = buf_to_str(str, buf, ft_strlen(buf));
  printf("%s\n", str);
  ft_bzero(buf, BUFFER_SIZE);
  read_return = read(fd, buf, BUFFER_SIZE);
  while (search_new_line(buf) - 1 == BUFFER_SIZE && read_return == BUFFER_SIZE)
  {
    str = buf_to_str(str, buf, read_return);
    ft_bzero(buf, BUFFER_SIZE);
    read_return = read(fd, buf, BUFFER_SIZE);
  }
  return(line_in_buffer(buf, str, read_return));
}


char *get_next_line(int fd)
{
  ssize_t read_return;
  char *str;
  static char *buf;

  read_return = 0;
  if (BUFFER_SIZE == 0)
    return (NULL);
  if (!buf)
  {
    printf("Buffer read\n");
    buf = ft_calloc(BUFFER_SIZE, 1);
    if (!buf)
      return (NULL);
    read_return = read(fd, buf, BUFFER_SIZE);
  }
  if (search_new_line(buf) < BUFFER_SIZE)
  {
    str = ft_calloc(1,1);
    if (!str)
      return (NULL);
    return(line_in_buffer(buf, str, read_return));
  }
  else
  {
    return(no_line_in_buffer(buf, read_return, fd));
  }
}


#include <fcntl.h>

int main(int argc, char **argv)
{
  int fd;
  char *buf;
  ssize_t read_return;

  (void)argc;
  fd = open(argv[1], O_RDONLY);
  // buf = ft_calloc(BUFFER_SIZE, 1);
  // read_return = read(fd, buf, BUFFER_SIZE);
  // printf("Read return is: %i\n", read_return);
  // if (read_return == 5)
  //   printf("sdfkdahsf\n");
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("%s\n", get_next_line(fd));
  close(fd);
}
