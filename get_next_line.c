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

size_t	search_new_line(const char *s)
{
  size_t i;

  i = 0;
	while (s[i] != '\n' && i < ft_strlen(s))
	{
		i++;
	}
	return (i);
}

char *buf_to_str(char *str, char *buf, int size)
{
  char *str_new;

  str_new = ft_calloc(ft_strlen(str) + size + 1, 1);
  ft_strlcpy(str_new, str, ft_strlen(str) + 1);
  ft_strlcat(str_new, buf, ft_strlen(str) + size + 1);
  free (str);
  return (str_new);
}

char *line_in_buffer(char *buf, char *str)
{
  int next_line;
  int buf_len;

  // printf("Line in Buffer\n");
  next_line = search_new_line(buf) + 1;
  buf_len = ft_strlen(buf);
  str = buf_to_str(str, buf, next_line); // + 1 for the newline
  buf = ft_memmove(buf, buf + next_line, buf_len - next_line);
  ft_bzero(buf + (buf_len - next_line), next_line);
  return (str);
}

char *no_line_in_buffer(char *buf, int fd)
{
  char *str;
  ssize_t read_return;

  // printf("No Line in buffer\n");
  str = ft_calloc(ft_strlen(buf) + 1, 1);
  if (!str)
    return (NULL);
  str = buf_to_str(str, buf, ft_strlen(buf));
  ft_bzero(buf, BUFFER_SIZE);
  read_return = read(fd, buf, BUFFER_SIZE);
  if (read_return == 0 && ft_strlen(str) == 0)
  {
    free(str);
    return (NULL);
  }
  while (search_new_line(buf) == BUFFER_SIZE && read_return == BUFFER_SIZE)
  {
    str = buf_to_str(str, buf, read_return);
    ft_bzero(buf, BUFFER_SIZE);
    read_return = read(fd, buf, BUFFER_SIZE);
  }
  if (read_return < BUFFER_SIZE)
  {
    str = buf_to_str(str, buf, read_return);
    ft_bzero(buf, read_return);
    return (str);
  }
  else
    return(line_in_buffer(buf, str));
}


char *get_next_line(int fd)
{
  char *str;
  static char *buf;

  if (BUFFER_SIZE == 0 || fd < 0)
    return (NULL);
  if (!buf)
  {
    // printf("Buffer read\n");
    buf = ft_calloc(BUFFER_SIZE + 1, 1);
    if (!buf)
      return (NULL);
    read(fd, buf, BUFFER_SIZE);
  }
  // printf("SNL:%li\n",search_new_line(buf));
  // printf("STRLEN: %li\n", ft_strlen(buf));
  if (search_new_line(buf) < ft_strlen(buf))
  {
    str = ft_calloc(1,1);
    if (!str)
      return (NULL);
    return(line_in_buffer(buf, str));
  }
  else
    return(no_line_in_buffer(buf, fd));
}


#include <fcntl.h>

int main(int argc, char **argv)
{
  int fd;
  char *str1;
  char *str2;
  char *str3;
  char *str4;
  char *str5;
  char *str6;
  char *str7;
  
  (void)argc;
  fd = open(argv[1], O_RDONLY);
  str1 = get_next_line(fd);
  str2 = get_next_line(fd);
  str3 = get_next_line(fd);
  str4 = get_next_line(fd);
  str5 = get_next_line(fd);
  str6 = get_next_line(fd);
  str7 = get_next_line(fd);
  printf("Line is: %s\n", str1);
  printf("Line is: %s\n", str2);
  printf("Line is: %s\n", str3);
  printf("Line is: %s\n", str4);
  printf("Line is: %s\n", str5);
  printf("Line is: %s\n", str6);
  printf("Line is: %s\n", str7);
  free(str1);
  free(str2);
  free(str3);
  free(str4);
  free(str5);
  free(str6);
  free(str7);
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("%s\n", get_next_line(fd));
  close(fd);
}
