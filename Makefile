# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 22:40:28 by dolifero          #+#    #+#              #
#    Updated: 2024/08/18 14:12:47 by tomecker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3d

CC              = cc
CFLAGS			= -Wall -Wextra -Werror
HEADERFLAGS		=  -I./include -I../Libft -I$(LIBMLX)/include/MLX42

LIBFT_DIR       = Libft
LIBFT           = $(LIBFT_DIR)/libft.a
LIBMLX			= ./MLX42
MAKELIBMLX		= ./MLX42/build/libmlx42.a
LIBS			= $(MAKELIBMLX) -L$(LIBFT_DIR) -L/opt/homebrew/lib -lft -ldl -lglfw -pthread -lm

SRC_DIR         = ./src
OBJ_DIR         = ./obj

SRC_FILES       =	src/checkers/checkers.c\
					src/checkers/map_checkers.c\
					src/parsing/parsing.c\
					src/parsing/init_structs.c\
					src/parsing/init_images.c\
					src/parsing/parsing_utils.c\
					src/controls/controls.c\
					src/controls/control_utils.c\
					src/drawing/draw_bg.c\
					src/drawing/wall_dist.c\
					src/drawing/draw_walls.c\
					src/drawing/draw_info.c\
					src/utils/utils.c\
					src/utils/freeing.c\
					src/utils/debug.c\
					src/main.c

OBJ_FILES		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all:			clear_screen $(NAME) visual_feedback

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

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
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
	make clean -C $(LIBFT_DIR)
	@clear
	@echo "$(DEF_COLOR)"

fclean: clean
	@echo "$(CYAN)"
	rm -f $(NAME)
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
	@for i in {1..42}; do \
		printf '%s' "█"; \
		sleep 0.01; \
	done

.PHONY: all clean fclean re CUBED_CYAN CUBED_GREEN loading clear_screen visual_feedback
