# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 00:38:01 by smoore-a          #+#    #+#              #
#    Updated: 2024/11/30 12:36:56 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDE = -Iinclude -I/usr/include 

HEADER = philo.h

CC = clang

CFLAGS = -Wall -Werror -Wextra -g -O0 -pthread

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main init check_info routine action time error utils cleanup

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all:	$(NAME)

VPATH = src:src/init:src/simulation:src/utils:include

$(NAME): $(OBJ_FILES)
	$(CC) $(INCLUDE) $^ -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

nocflag:
	$(MAKE) CFLAGS="-g -O0 -pthread" $(NAME)

.PHONY: all clean fclean re nocflag

ifndef VERBOSE
.SILENT:
endif
