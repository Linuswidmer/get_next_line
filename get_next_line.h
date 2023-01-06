#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
# endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *get_next_line(int fd);
size_t ft_strlen(const char *str);
void ft_bzero(void *s, size_t n);
void *ft_calloc(size_t nmeb, size_t size);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
size_t ft_strlcat(char *dest, const char *src, size_t size);

# endif 
