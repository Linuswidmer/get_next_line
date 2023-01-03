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

char *buf_to_str(char *str, char *buf, int iteration, int end)
{
  char *str_new;

  str_new = ft_calloc(BUFFER_SIZE * iteration + end + 1, 1);
  ft_strlcpy(str_new, str, ft_strlen(str) + 1);
  ft_strlcat(str_new, buf, BUFFER_SIZE * iteration + end + 1);
  free (str);
  return (str_new);
}

char *no_line_in_buffer(char *buf, int *position, int fd)
{
  int beginning;
  int iteration;
  int next_line;
  ssize_t read_return;
  char *str;

  iteration = 1;
  beginning = 0;
  next_line = 0;
  str = ft_calloc(BUFFER_SIZE, 1);
  if (!str)
    return (NULL);
  if (*position != 0)
    beginning = BUFFER_SIZE - *position;
  printf("Beginning counter is: %i\n", beginning);
  printf("return form snl is: %i\n", search_new_line(buf + *position));
    printf("Previous Buffer is: %s\n", buf);
  while (search_new_line(buf + *position) - 1 == BUFFER_SIZE)
  {
    str = buf_to_str(str, buf + *position, iteration, beginning);
    if (*position != 0)
       iteration --;
    printf("Current string is: %s\n", str);
    iteration++;
    read_return = read(fd, buf, BUFFER_SIZE);
    printf("ReadReturn is: %i\n", read_return);
    if (read_return == 0)
        return (str);
    *position = 0;
    printf("New Buffer is: %s\n", buf);
    // printf("Iteration count: %i\n", iteration);
  }
  printf("Iteration count is: %i\n", iteration);
  next_line = search_new_line(buf + *position);
  printf("Last line is: %i chars long\n", next_line);
  str = buf_to_str(str, buf, iteration - 1, next_line + 1 + beginning); // + 1 for the newline
  // printf("Line is: %s\n", str);
  *position = next_line + 1;
  printf("Position is: %i\n", *position);
  return (str);
}

char *line_in_buffer(char *buf, int *position)
{
  int next_line;
  char *str;

  printf("New line found in buffer\n");
  next_line = search_new_line(buf + *position);
  printf("End of next line is %i\n", next_line + *position);  
  printf("Line lenght is %i\n", next_line);
  str = ft_calloc(next_line + 1, 1);
  if (!str)
    return (NULL);
  ft_strlcpy(str, buf + *position, next_line + 2);
  *position = *position + next_line + 1;
  return (str);
}

char *get_next_line(int fd)
{
  char *buf;
  static int position;
  ssize_t read_return;

  read_return = BUFFER_SIZE;
  if (BUFFER_SIZE == 0)
    return (NULL);
  printf("Position is: %i\n", position);
  if (position == 0)
  {
    buf = ft_calloc(BUFFER_SIZE, 1);
    read_return = read(fd, buf, BUFFER_SIZE);
    printf("Read return is: %i\n", read_return);
    if (read_return == 0)
    {
      return (NULL);
    }
  }
  if (search_new_line(buf + position) < BUFFER_SIZE)
  {
    return(line_in_buffer(buf, &position));
  }
  else
  {
    return(no_line_in_buffer(buf, &position, fd));
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
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("Line is: %s\n", get_next_line(fd));
  // printf("%s\n", get_next_line(fd));
  close(fd);
}
