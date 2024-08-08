NAME			= cub3d

CC				= cc
CFLAGS			= -Wall -Wextra -Werror

LIBFT_DIR 		= Libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRC_DIR			= ./src
OBJ_DIR			= ./obj

SRC_FILES		= 	checkers.c\
					parsing.c

OBJ_FILES		= $(patsubst $(SRC_DIR)/main.c, $(OBJ_DIR)/%.o, $(SRC_DIR)/$(SRC_FILES))

all:				$(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(foreach dir, $(SUBDIRS), $(OBJ_DIR)/$(dir))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


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

all:
				clear;
				@$(MAKE) CUBED_CYAN
				@$(MAKE) loading
				clear;
				@$(MAKE) CUBED_GREEN
				@echo "             $(BOLD_GREEN)${NAME} DONE!\n$(DEF_COLOR)"

clean:
				@echo "$(CYAN)"
				rm -rf $(OBJ_DIR)
				make clean -C $(LIBFT_DIR)
				clear;
				@echo "$(DEF_COLOR)"

fclean:	clean
				@echo "$(CYAN)"
				rm -f $(NAME)
				make fclean -C $(LIBFT_DIR)
				clear;
				@echo "$(DEF_COLOR)"

re:				fclean all

CUBED_CYAN:
				@echo "\n$(BR_CYAN) ________  ___  ___  ________  ________  ________     "
				@echo "|\   ____\|\  \|\  \|\   __  \|\_____  \|\   ___ \    "
				@echo "\ \  \___|\ \  \\\  \ \  \|\ /\|____|\ /\ \  \_|\ \   "
				@echo " \ \  \    \ \  \\\  \ \   __  \    \|\  \ \  \ \\ \  "
				@echo "  \ \  \____\ \  \\\  \ \  \|\  \  __\_\  \ \  \_\\ \ "
				@echo "   \ \_______\ \_______\ \_______\|\_______\ \_______\"
				@echo "    \|_______|\|_______|\|_______|\|_______|\|_______|$(DEF_COLOR)\n"
                                                      
                                                      
                                                      

CUBED_GREEN:
				@echo "\n$(GREEN) ________  ___  ___  ________  ________  ________     "
				@echo "|\   ____\|\  \|\  \|\   __  \|\_____  \|\   ___ \    "
				@echo "\ \  \___|\ \  \\\  \ \  \|\ /\|____|\ /\ \  \_|\ \   "
				@echo " \ \  \    \ \  \\\  \ \   __  \    \|\  \ \  \ \\ \  "
				@echo "  \ \  \____\ \  \\\  \ \  \|\  \  __\_\  \ \  \_\\ \ "
				@echo "   \ \_______\ \_______\ \_______\|\_______\ \_______\"
				@echo "    \|_______|\|_______|\|_______|\|_______|\|_______|$(DEF_COLOR)\n"

loading:
				@for i in {1..42}; do \
					printf '%s' "█"; \
					sleep 0.01; \
				done

.PHONY:			all clean fclean re