#include "get_next_line.h"

int	search_new_line(const char *s)
{
  int i;

  i = 0;
	while (i <= BUFFER_SIZE)
	{
		if (((char *)s)[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char *buf_to_str(char *str, char *buf, int size)
{
  char *str_new;

  if (size == 0)
    return (NULL);
  str_new = ft_calloc(ft_strlen(str) + size + 1, 1);
  ft_strlcpy(str_new, str, ft_strlen(str) + 1);
  ft_strlcat(str_new, buf, ft_strlen(str) + size + 1);
  printf("Line length is: %i\n", size);
  printf("Allocation for new string is %i\n", ft_strlen(str) + size + 1);
  printf("STR is %s\n", str);
  printf("STR_NEW is %s\n", str_new);
  free (str);
  return (str_new);
}

char *line_in_buffer(char *buf, int *position, char *str)
{
  int next_line;

  printf("New line found in buffer\n");
  printf("Buffer with newline is: %s\n", buf);
  next_line = search_new_line(buf + *position);
  printf("Start of next line is: %i \n", *position);
  printf("End of next line is %i\n", next_line + *position);  
  printf("Line lenght is %i\n", next_line);
  str = buf_to_str(str, buf + *position, next_line + 1); // + 1 for the newline
  *position = *position + next_line + 1;
  return (str);
}

char *no_line_in_buffer(char *buf, int *position, int fd)
{
  char *str;
  ssize_t read_return;

  printf("No Line in buffer\n");
  str = ft_calloc(BUFFER_SIZE, 1);
  if (!str)
    return (NULL);
  str = buf_to_str(str, buf + *position, BUFFER_SIZE);
  *position = 0;
  read_return = read(fd, buf, BUFFER_SIZE);
  printf("Read return is %i\n", read_return);
  if (read_return == 0)
  {
    return (str);
  }
  // printf("return form snl is: %i\n", search_new_line(buf + *position));
  printf("New Buffer is: %s\n", buf);
  while (search_new_line(buf + *position) - 1 == BUFFER_SIZE && read_return != 0)
  {
    printf("New Buffer is: %s\n", buf);
    str = buf_to_str(str, buf, read_return + 1);
    printf("Current string is: %s\n", str);
    ft_bzero(buf, BUFFER_SIZE);
    read_return = read(fd, buf, BUFFER_SIZE) == BUFFER_SIZE ;
  }

  return(line_in_buffer(buf, position, str));
}


char *get_next_line(int fd)
{
  char *buf;
  static int position;
  char *str;

  printf("Position is: %i\n", position);
  if (BUFFER_SIZE == 0)
    return (NULL);
  if (position == 0)
  {
    buf = ft_calloc(BUFFER_SIZE, 1);
    if (!buf)
      return (NULL);
    if (read(fd, buf, BUFFER_SIZE) == 0)
      return (NULL);
  }
  if (search_new_line(buf + position) < BUFFER_SIZE)
  {
    str = ft_calloc(1,1);
    if (!str)
      return (NULL);
    return(line_in_buffer(buf, &position, str));
  }
  else
    return(no_line_in_buffer(buf, &position, fd));
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
