# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 22:40:28 by dolifero          #+#    #+#              #
#    Updated: 2024/09/03 19:44:26 by tomecker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3d
NAME_BONUS      = cub3d_bonus

CC              = cc
CFLAGS			= -Wall -Wextra -Werror
HEADERFLAGS		=  -I./include -I../Libft -I$(LIBMLX)/include/MLX42

LIBFT_DIR       = Libft
LIBFT           = $(LIBFT_DIR)/libft.a
LIBMLX			= ./MLX42
MAKELIBMLX		= ./MLX42/build/libmlx42.a
LIBS			= $(MAKELIBMLX) -L$(LIBFT_DIR) -L/opt/homebrew/lib -lft -ldl -lglfw -pthread -lm

SRC_DIR         = ./src
SRC_DIR_BONUS   = ./src_bonus
OBJ_DIR         = ./obj
OBJ_DIR_BONUS   = ./obj_bonus

SRC_FILES_BONUS =	./src_bonus/checkers/checkers.c\
					./src_bonus/checkers/map_checkers.c\
					./src_bonus/initialize/init_structs.c\
					./src_bonus/initialize/init_images.c\
					./src_bonus/initialize/init_textures.c\
					./src_bonus/initialize/init_sprites.c\
					./src_bonus/initialize/parsing.c\
					./src_bonus/controls/controls.c\
					./src_bonus/controls/collision.c\
					./src_bonus/controls/controls_mouse.c\
					./src_bonus/drawing/draw_bg.c\
					./src_bonus/raycasting/wall_dist.c\
					./src_bonus/raycasting/dda.c\
					./src_bonus/raycasting/initialization.c\
					./src_bonus/drawing/draw_walls.c\
					./src_bonus/drawing/draw_sprites.c\
					./src_bonus/drawing/draw_overlay.c\
					./src_bonus/drawing/draw_minimap.c\
					./src_bonus/utils/utils.c\
					./src_bonus/utils/utils_2.c\
					./src_bonus/utils/drawing_utils.c\
					./src_bonus/utils/init_utils.c\
					./src_bonus/utils/control_utils.c\
					./src_bonus/utils/freeing.c\
					./src_bonus/utils/debug.c\
					./src_bonus/main.c

SRC_FILES		=	./src/checkers/checkers.c\
					./src/checkers/map_checkers.c\
					./src/initialize/init_structs.c\
					./src/initialize/init_images.c\
					./src/initialize/init_textures.c\
					./src/initialize/parsing.c\
					./src/controls/controls.c\
					./src/controls/collision.c\
					./src/drawing/draw_bg.c\
					./src/raycasting/wall_dist.c\
					./src/raycasting/dda.c\
					./src/raycasting/initialization.c\
					./src/drawing/draw_walls.c\
					./src/utils/utils.c\
					./src/utils/utils_2.c\
					./src/utils/drawing_utils.c\
					./src/utils/init_utils.c\
					./src/utils/control_utils.c\
					./src/utils/freeing.c\
					./src/utils/debug.c\
					./src/main.c

OBJ_FILES		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_BONUS	=	$(patsubst $(SRC_DIR_BONUS)/%.c, $(OBJ_DIR_BONUS)/%.o, $(SRC_FILES_BONUS))

all:			clear_screen $(NAME) visual_feedback

bonus:			clear_screen $(NAME_BONUS) visual_feedback

libmlx:
				mkdir -p $(LIBMLX)/build
				cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
BOLD_WHITE	=	\033[1;97m
BOLD_GREEN	=	\033[1;92m
NO_COLOR	=	\033[0m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[2;96m
BR_CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

$(NAME): $(OBJ_FILES) $(LIBFT) $(MAKELIBMLX)
	$(CC) $(CFLAGS) $(HEADERFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBS)

$(NAME_BONUS): $(OBJ_FILES_BONUS) $(LIBFT) $(MAKELIBMLX)
	$(CC) $(CFLAGS) $(HEADERFLAGS) -o $(NAME_BONUS) $(OBJ_FILES_BONUS) $(LIBS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c | $(OBJ_DIR_BONUS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERFLAGS) -c $< -o $@


$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MAKELIBMLX):	$(LIBMLX)
			@echo "\n$(BOLD_CYAN)Starting $(BOLD_WHITE)[${LIBMLX}] $(BOLD_CYAN)compilation..$(DEF_COLOR)\n"
			@mkdir -p $(LIBMLX)/build
			@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
			@echo "\n$(BOLD_GREEN)${LIBMLX} DONE!\n$(DEF_COLOR)"

$(LIBMLX):
				touch .gitmodules
				git submodule add -f https://github.com/codam-coding-college/MLX42.git

clear_screen:
	@clear

visual_feedback:
	@$(MAKE) CUBED_CYAN
	@$(MAKE) loading
	@clear
	@$(MAKE) CUBED_GREEN
	@echo "             $(BOLD_GREEN)${NAME} DONE!\n$(DEF_COLOR)"

clean:
	@echo "$(CYAN)"
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)
	make clean -C $(LIBFT_DIR)
	@clear
	@echo "$(DEF_COLOR)"

fclean: clean
	@echo "$(CYAN)"
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)
	rm -rf $(LIBMLX)/build
	@clear
	@echo "$(DEF_COLOR)"

re: fclean all

CUBED_CYAN:
	@echo "\n$(BR_CYAN) ________  ___  ___  ________  ________  ________     "
	@echo "|\   ____\|\  \ \  \|\   __  \|\_____  \|\   ___ \    "
	@echo "\ \  \___|\ \  \ \  \ \  \|\ /\|____|\  \ \  \_|\ \   "
	@echo " \ \  \    \ \  \ \  \ \   __  \    \|\  \ \  \  \ \  "
	@echo "  \ \  \____\ \  \_\  \ \  \|\  \  __\_\  \ \  \__\ \ "
	@echo "   \ \_______\ \_______\ \_______\|\_______\ \_______\ "
	@echo "    \|_______|\|_______|\|_______|\|_______|\|_______|$(DEF_COLOR)\n"

CUBED_GREEN:
	@echo "\n$(GREEN) ________  ___  ___  ________  ________  ________     "
	@echo "|\   ____\|\  \ \  \|\   __  \|\_____  \|\   ___ \    "
	@echo "\ \  \___|\ \  \ \  \ \  \|\ /\|____|\  \ \  \_|\ \   "
	@echo " \ \  \    \ \  \ \  \ \   __  \    \|\  \ \  \  \ \  "
	@echo "  \ \  \____\ \  \_\  \ \  \|\  \  __\_\  \ \  \__\ \ "
	@echo "   \ \_______\ \_______\ \_______\|\_______\ \_______\ "
	@echo "    \|_______|\|_______|\|_______|\|_______|\|_______|$(DEF_COLOR)\n"

loading:
	@for i in {1..55}; do \
		printf '%s' "█"; \
		sleep 0.01; \
	done

.PHONY: all clean fclean re CUBED_CYAN CUBED_GREEN loading clear_screen visual_feedback
