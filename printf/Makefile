# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 20:08:31 by smoore-a          #+#    #+#              #
#    Updated: 2024/06/08 14:27:36 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	libftprintf.a
INCLUDE		=	include
SRC_DIR		= 	src/
OBJ_DIR		= 	obj/
CC			= 	clang
CFLAGS		= 	-Wall -Werror -Wextra -g -I
RM			= 	rm -rf
AR			= 	ar rcs

SRC_FILES	=	ft_printf ft_conversion ft_hex_address ft_uitoa\
				ft_puthex_fd ft_printf_itoa ft_printf_utils
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:			$(NAME)

$(NAME):		$(OBJ)
				@echo "$(YELLOW)Compiling the libft library...$(RESET)"
				@make -C libft
				@cp libft/libft.a .
				@echo "$(YELLOW)Copying libft.a to the current directory...$(RESET)"
				@mv libft.a $(NAME)
				@echo "$(YELLOW)Renaming libft.a to $(NAME)...$(RESET)"
				@$(AR) $(NAME) $(OBJ)
				@echo "$(GREEN)Creating the final library $(NAME)...$(RESET)"

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c | $(OBJF)
				@echo "$(YELLOW)Compiling $<...$(RESET)"
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
				@echo "$(YELLOW)Creating $(OBJ_DIR) directory...$(RESET)"
				@mkdir -p $(OBJ_DIR)

clean:
				@echo "$(RED)Cleaning up object files...$(RESET)"
				@$(RM) $(OBJ_DIR)
				@echo "$(RED)Calling clean in libft...$(RESET)"
				@make clean -C libft

fclean:			clean
				@echo "$(RED)Cleaning up $(NAME)...$(RESET)"
				@$(RM) $(NAME)
				@echo "$(RED)Removing libft/libft.a...$(RESET)"
				@$(RM) libft/libft.a

re:				fclean all

.PHONY:			all clean fclean re