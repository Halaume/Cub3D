# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:11:08 by ghanquer          #+#    #+#              #
#    Updated: 2022/08/23 16:52:48 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.h libft
vpath ft_%.c libft
vpath ft_%.o libft

NAME = cub3D
NAMEB = cub3D_bonus

INC =			inc/cub3d.h
INCB =			inc/cub3d_bonus.h
OBJ_DIR =		obj
OBJB_DIR =		obj_bonus
SRC_DIR =		src
SRCB_DIR =		src_bonus
LIB_DIR =		libft/

SRC =			$(SRC_FT:%=$(SRC_DIR)/%.c)
SRCB =			$(SRCB_FT:%=$(SRCB_DIR)/%.c)

OBJ =			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJB =			$(SRCB:$(SRCB_DIR)%.c=$(OBJB_DIR)%.o)

CC = cc $(CFLAGS)

RM = rm -fr

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MLX = minilibx-linux/libmlx_Linux.a

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".c$"| sed "s/\.c/ \\\/g" | sed '$s/\\$//g'

SRC_FT = affiche brice_casting cub3d_basic cub3d_basic2 ft_gnl hook liberation \
		 main map moove moove_for moove_back moove_left moove_right texture \
		 casting_tools ft_tools ft_colors ft_coloring ft_parse ft_check_map \
		 ft_check_map_tools ft_partext ft_player ft_print hook_mouse check_edge

SRCB_FT = affiche_bonus brice_casting_bonus casting_tools_bonus \
		  cub3d_basic2_bonus cub3d_basic_bonus ft_check_map_bonus \
		  ft_check_map_tools_bonus ft_coloring_bonus ft_colors_bonus \
		  ft_doors_bonus ft_gnl_bonus ft_minimap_bonus ft_parse_bonus \
		  ft_partext_bonus ft_player_bonus ft_print_bonus ft_print_map_bonus \
		  ft_tools_bonus hook_bonus hook_mouse_bonus liberation_bonus \
		  main_bonus map_bonus moove_back_bonus moove_bonus moove_for_bonus \
		  moove_left_bonus moove_right_bonus texture_bonus 

LIBFT = libft/libft.a

LIBPATH = -L $(LIB_DIR)
INCPATH = -I $(INC_DIR) -I $(LIB_DIR)

all: $(NAME)

-include libft/Makefile

$(OBJ_DIR):
	mkdir -p $@

$(OBJ) : $(INC) | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIR) $(SRC) $(MLX) $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

bonus: $(NAMEB)

$(OBJB_DIR):
	mkdir -p $@

$(OBJB) : $(INCB) | $(OBJB_DIR)

$(OBJB_DIR)/%.o: $(SRCB_DIR)/%.c
	$(CC) -c $< -o $@

$(NAMEB): $(OBJB_DIR) $(SRCB) $(MLX) $(OBJB) $(LIBFT)
	$(CC) $(OBJB) $(MLX) $(LIBFT) -lXext -lX11 -lm -Iminilibx -o $@

$(MLX):
	$(MAKE) -C ./minilibx-linux

$(LIBFT):	${SRCS} ${OBJS} libft.h
	${MAKE} -C libft/

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJB_DIR)
	@echo "Cleaned object"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAMEB)
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

.SECONDARY: $(OBJ) $(OBJ_DIR) $(OBJB) $(OBJB_DIR)
.PHONY: all clean fclean re coffee bonus
