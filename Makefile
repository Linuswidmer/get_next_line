# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 09:51:03 by lwidmer           #+#    #+#              #
#    Updated: 2022/12/16 10:44:22 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Makefile to compile the get_next_line project 

NAME = get_next_line

FILENAMES_GET_NEXT_LINE = get_next_line \
													get_next_line_utils

SRCS_GET_NEXT_LINE_DIR = ./
SRCS_GET_NEXT_LINE = $(addprefix $(SRCS_GET_NEXT_LINE_DIR), $(addsuffix .c, $(FILENAMES_GET_NEXT_LINE)))

OBJS_GET_NEXT_LINE_DIR = ./
OBJS_GET_NEXT_LINE= $(addprefix $(OBJS_GET_NEXT_LINE_DIR), $(addsuffix .o, $(FILENAMES_GET_NEXT_LINE)))

SRCS = $(SRCS_GET_NEXT_LINE)
OBJS = $(OBJS_GET_NEXT_LINE)

CFLAGS = -Werror -Wall -Wextra

${NAME}: ${OBJS}
	cc $(CFLAGS) ${OBJS} -D BUFFER_SIZE=0

.c.o: ${SRCS}
	cc ${CFLAGS} -c -o $@ $< 

all: ${NAME} clean

clean:
	rm -rf ${OBJS_FT_PRINTF} ${OBJS_LIBFT}

fclean: clean
	rm -rf ${NAME}

re: fclean all

git:
	git add .
	git commit -m "$m"
	git push origin main

# ${LIBRARY}: 
# 	cd ${LIBRARY} && \
# 	make re

.PHONY: all clean fclean re
