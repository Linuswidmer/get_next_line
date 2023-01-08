#include "get_next_line.h"

static size_t	search_new_line(const char *s)
{
  size_t i;

  i = 0;
	while (s[i] != '\n' && i < ft_strlen(s))
	{
		i++;
	}
	return (i);
}

static char *buf_to_str(char *str, char *buf, int size)
{
  char *str_new;

  if (!str)
  {
    str = ft_calloc(1,1);
    if (!str)
      return (NULL);
  }
  str_new = ft_calloc(ft_strlen(str) + size + 1, 1);
  ft_strlcat(str_new, str, ft_strlen(str) + 1);
  ft_strlcat(str_new, buf, ft_strlen(str) + size + 1);
  free (str);
  return (str_new);
}

static char *line_in_buffer(char *buf, char *str)
{
  int next_line;
  int buf_len;

  next_line = search_new_line(buf) + 1;
  buf_len = ft_strlen(buf);
  str = buf_to_str(str, buf, next_line);
  buf = ft_memmove(buf, buf + next_line, buf_len - next_line);
  ft_bzero(buf + (buf_len - next_line), next_line);
  return (str);
}

static char *no_line_in_buffer(char *buf, int fd)
{
  char *str;
  ssize_t read_return;

  str = ft_calloc(ft_strlen(buf) + 1, 1);
  if (!str)
    return (NULL);
  str = buf_to_str(str, buf, ft_strlen(buf));
  ft_bzero(buf, BUFFER_SIZE);
  read_return = read(fd, buf, BUFFER_SIZE);
  while (search_new_line(buf) == BUFFER_SIZE && read_return == BUFFER_SIZE)
  {
    str = buf_to_str(str, buf, read_return);
    ft_bzero(buf, BUFFER_SIZE);
    read_return = read(fd, buf, BUFFER_SIZE);
  }
  if (search_new_line(buf) < (unsigned long int)read_return)
    return (line_in_buffer(buf, str));
  else 
  {
    str = buf_to_str(str, buf, read_return);
    ft_bzero(buf, read_return);
    return (str);
  }
}


char *get_next_line(int fd)
{
  char *str;
  static char *buf;

  str = NULL;
  if (BUFFER_SIZE > 0 && fd >= 0)
  {
    if (!buf)
    {
      buf = ft_calloc(BUFFER_SIZE + 1, 1);
      if (!buf)
        return (NULL);
      read(fd, buf, BUFFER_SIZE);
    }
    if (search_new_line(buf) < ft_strlen(buf))
      str = line_in_buffer(buf, str);
    else if (ft_strlen(buf) > 0)
      str = no_line_in_buffer(buf, fd);
  }
  if (ft_strlen(buf) == 0)
  {
    free (buf);
    buf = 0;
  }
  return (str);
}


#include <fcntl.h>

int main(int argc, char **argv)
{
  int fd;
  char *str1;
  char *str2;
  // char *str3;
  // char *str4;
  // char *str5;
  // char *str6;
  // char *str7;
  // char *str8;
  
  (void)argc;
  fd = open(argv[1], O_RDONLY);
  str1 = get_next_line(fd);
  printf("Line is: %s\n", str1);
  str2 = get_next_line(fd);
  printf("Line is: %s\n", str2);
  // str3 = get_next_line(fd);
  // printf("Line is: %s\n", str3);
  // close(fd);
  // fd = open(argv[1], O_RDONLY);
  // str4 = get_next_line(fd);
  // printf("Line is: %s\n", str4);
  // str5 = get_next_line(fd);
  // printf("Line is: %s\n", str5);
  // str6 = get_next_line(fd);
  // printf("Line is: %s\n", str6);
  // str7 = get_next_line(fd);
  // str8 = get_next_line(fd);
  // printf("Line is: %s\n", str7);
  // printf("Line is: %s\n", str8);
  free(str1);
  free(str2);
  // free(str3);
  // free(str4);
  // free(str5);
  // free(str6);
  // free(str7);
  // free(str8);
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("%s\n", get_next_line(fd));
  close(fd);
}
