# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:11:08 by ghanquer          #+#    #+#              #
#    Updated: 2022/08/22 11:58:38 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.h libft
vpath ft_%.c libft
vpath ft_%.o libft

NAME = cub3D

INC_DIR =		inc
OBJ_DIR =		obj
SRC_DIR =		src
LIB_DIR =		libft/

SRC =			$(SRC_FT:%=$(SRC_DIR)/%.c)

OBJ =			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS =		$(OBJ_DIR)

CC = cc $(CFLAGS)

RM = rm -fr

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MLX = minilibx-linux/libmlx_Linux.a

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".c$"| sed "s/\.c/ \\\/g" | sed '$s/\\$//g'

SRC_FT = affiche \
	brice_casting \
	cub3d_basic \
	cub3d_basic2 \
	ft_gnl \
	hook \
	liberation \
	main \
	map \
	moove \
	moove_for \
	moove_back \
	moove_left \
	moove_right \
	texture \
	casting_tools \
	ft_tools \
	ft_colors \
	ft_coloring \
	ft_parse \
	ft_check_map \
	ft_check_map_tools \
	ft_partext \
	ft_player \
	ft_print_map \
	ft_minimap \
	ft_print \
	hook_mouse

LIBFT = libft/libft.a

LIBPATH = -L $(LIB_DIR)
INCPATH = -I $(INC_DIR) -I $(LIB_DIR)

all: $(NAME)

-include libft/Makefile

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ) : | $(OBJ_DIRS)

$(OBJ_DIRS)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIRS) $(SRC) $(MLX) $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

$(MLX):
	$(MAKE) -C ./minilibx-linux

$(LIBFT):	${SRCS} ${OBJS} libft.h
	${MAKE} -C libft/

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Cleaned object"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIB_DIR)
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
