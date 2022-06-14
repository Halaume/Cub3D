# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:11:08 by ghanquer          #+#    #+#              #
#    Updated: 2022/06/14 14:59:53 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INC_DIR =		inc
OBJ_DIR =		obj
SRC_DIR =		src

SRC =			$(SRC_FT:%=$(SRC_DIR)/%.c)

OBJ =			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS =		$(OBJ_DIR)

CC = clang $(CFLAGS)

RM = rm -fr

CFLAGS = -Wall -Wextra -Werror -pthread -g #3 -fsanitize=address

MLX = minilibx-linux/libmlx_Linux.a

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".c$"| sed "s/\.c/ \\\/g" | sed '$s/\\$//g'

SRC_FT = cub3d_basic \
		hook \
		main 

all: $(NAME)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ) : | $(OBJ_DIRS)

$(OBJ_DIRS)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIRS) $(SRC) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(MLX) -lXext -lX11 -lm -Iminilibx -o $@

$(MLX):
	$(MAKE) -C ./minilibx-linux

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Cleaned object"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) clean -C ./minilibx-linux
	@echo "Cleaned program and MLX"

re: fclean all

define print_aligned_coffee
    @t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3C\033[$${i}CAnd Your program \"$(NAME)\" "
endef

coffee: all clean
	@echo ""
	@echo "                                {"
	@echo "                             {   }"
	@echo "                              }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "                           \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "                          \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "                          \0033[1;34m| -.._____..- |"
	@echo "                          |             ;--."
	@echo "                          |            (__  \ "
	@echo "                          |             | )  )"
	@echo "                          |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "                          |             /  / "
	@echo "                          |            (  / "
	@echo "                          \             | "
	@echo "                            -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C                    Take Your Coffee"
	$(call print_aligned_coffee)

.SECONDARY: $(OBJ) $(OBJ_DIR)
.PHONY: all clean fclean re coffee
