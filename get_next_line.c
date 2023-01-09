/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:10:56 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/09 09:42:53 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void free_buffer(char **buf)
{
  free (*buf);
  *buf = 0;
}

static size_t	search_new_line(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && i < ft_strlen(s))
		i++;
	return (i);
}

static char	*buf_to_str(char *str, char *buf, int size)
{
	char	*str_new;
	int str_len;

	str_len = ft_strlen(str) + 1;
	if (!str)
	{
		str = malloc(str_len);
		if (!str)
			return (NULL);
		ft_bzero(str, str_len);
	}
	str_new = malloc(str_len + size);
	if (!str_new)
		return (NULL);
	ft_bzero(str_new, str_len + size);
	ft_strlcat(str_new, str, str_len);
	ft_strlcat(str_new, buf, str_len + size);
	free (str);
	return (str_new);
}

static char	*line_in_buffer(char *buf, char *str)
{
	int	next_line;
	int	buf_len;

	next_line = search_new_line(buf) + 1;
	buf_len = ft_strlen(buf);
	str = buf_to_str(str, buf, next_line);
	buf = ft_memmove(buf, buf + next_line, buf_len - next_line);
	ft_bzero(buf + (buf_len - next_line), next_line);
	return (str);
}

static char	*no_line_in_buffer(char *buf, int fd, ssize_t *read_return)
{
	char	*str;

	str = buf_to_str(0, buf, ft_strlen(buf));
	ft_bzero(buf, BUFFER_SIZE);
	*read_return = read(fd, buf, BUFFER_SIZE);
	while (search_new_line(buf) == BUFFER_SIZE && *read_return == BUFFER_SIZE)
	{
		str = buf_to_str(str, buf, *read_return);
		ft_bzero(buf, BUFFER_SIZE);
		*read_return = read(fd, buf, BUFFER_SIZE);
	}
	if (search_new_line(buf) < (unsigned long int)(*read_return))
		return (line_in_buffer(buf, str));
	else if(*read_return != -1)
	{
		str = buf_to_str(str, buf, *read_return);
		ft_bzero(buf, *read_return);
		return (str);
	}
  return (NULL);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*buf;
	ssize_t	read_return;

	str = NULL;
	read_return = 0;
	if (BUFFER_SIZE > 0 && fd >= 0)
	{
		if (!buf)
		{
			buf = malloc(BUFFER_SIZE + 1);
			if (!buf)
				return (NULL);
			ft_bzero(buf, BUFFER_SIZE + 1);
			read_return = read(fd, buf, BUFFER_SIZE);
		}
		if (search_new_line(buf) < ft_strlen(buf))
			str = line_in_buffer(buf, str);
		else if (ft_strlen(buf) > 0)
			str = no_line_in_buffer(buf, fd, &read_return);
	}
	if (ft_strlen(buf) == 0 || read_return == -1)
	  free_buffer(&buf);
	return (str);
}

#include <fcntl.h>

int main()
{
  char *str1;
  int fd;

  fd = open("test",O_RDONLY);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  close(fd);
  fd = open("test_no_newline",O_RDONLY);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  close(fd);
  fd = open("test_around10",O_RDONLY);
  str1 = get_next_line(fd);
  printf("\n%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  str1 = get_next_line(fd);
  printf("%s", str1);
  free(str1);
  close(fd);
  fd = open("test_no_newline",O_RDONLY);
}
