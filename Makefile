NAME	= cub3D 

#---------------------COMPILATION-----------------------#
CC			=	cc
CFLAGS		=	-g -Wall -Werror -Wextra
#-------------------------------------------------------#

#---------------------SOURCES---------------------------#
SRC_PATH	=	src/
SRC			=						\
				main.c				\
				check_map.c			\
				clean_up.c			\
				errors.c			\
				game_loop.c			\
				init_mlx.c			\
				init_s_map.c		\
				utils.c				\

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
#-------------------------------------------------------#

#---------------------LIBS------------------------------#
LIBS_PATH	=	libs/

LIBFT_NAME	=	libft.a
LIBFT_PATH	=	$(LIBS_PATH)libft/
LIBFT		=	$(LIBFT_PATH)$(LIBFT_NAME)

MLX_PATH	=	$(LIBS_PATH)minilibx/
MLX_LINK	=	-L $(MLX_PATH) -lmlx -lXext -lX11
#-------------------------------------------------------#

#---------------------HEADERS---------------------------#
HDR_PATH	=	include/
HDR			=	$(HDR_PATH)cub3D.h

INC			=	-I include/\
				-I $(LIBFT_PATH)includes/\
#-------------------------------------------------------#

#---------------------OBJETS----------------------------#
OBJ_PATH	=	obj/
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
#-------------------------------------------------------#

all: $(NAME)

$(NAME): libft mlx $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_LINK) $(INC)
	@make --silent folie

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	
libft:
	@make -sC $(LIBFT_PATH)

mlx:
	@make -sC $(MLX_PATH)
	
clean:
	@make --silent sweep
	@rm -rf $(OBJ_PATH)
	@make -sC $(LIBFT_PATH) fclean
	@make -sC $(MLX_PATH) clean

fclean: clean
	@rm -rf $(NAME)

re: fclean all

# Define color codes
BLUE	= \033[94m
RED		= \033[95;52m
RESET	= \033[0m

folie:
	@printf "$(RED)_________                        ___________      __________                                    ________     __________      \n"
	@printf "$(RED)__  ____/____________ ______________(_)__  /_____ __  /___(_)____________     ____________      ___  __/________  /__(_)____ \n"
	@printf "$(RED)_  /    _  __ \\_  __ \`__ \\__  __ \\_  /__  /_  __ \`/  __/_  /_  __ \\_  __ \\    _  _ \\_  __ \\     __  /_ _  __ \\_  /__  /_  _ \\ \n"
	@printf "$(RED)/ /___  / /_/ /  / / / / /_  /_/ /  / _  / / /_/ // /_ _  / / /_/ /  / / /    /  __/  / / /     _  __/ / /_/ /  / _  / /  __/ \n"
	@printf "$(RED)\\____/  \\____//_/ /_/ /_/_  .___//_/  /_/  \\__,_/ \\__/ /_/  \\____//_/ /_/     \\___//_/ /_/      /_/    \\____//_/  /_/  \\___/  \n"
	@printf "$(RED)                         /_/                                                                                                  $(RESET)\n"

sweep:
	@printf "${BLUE}           ______           __  __                                                          \n"
	@printf "          / ____/__  ____  / /_/ /__  ____ ___  ____ _____     ______      _____  ___  ____ \n"
	@printf "         / / __/ _ \/ __ \/ __/ / _ \/ __ \`__ \/ __ \`/_ __ \  / ___/ | /| / / _ \/ _ \/ __ \\ \n"
	@printf "        / /_/ /  __/ / / / /_/ /  __/ / / / / / /_/ / / / /  (__  )| |/ |/ /  __/  __/ /_/ / \n"
	@printf "        \\____/\\___/_/ /_/\\__/_/\\___/_/ /_/ /_/\\__,_/ / /_/  /____/ |__/|__/\\___/\\___/ .___/ \n"
	@printf "                                                                                   /_/       ${RESET}\n"


.PHONY: clean fclean re folie sweep