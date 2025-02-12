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

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	
libft:
	@make -sC $(LIBFT_PATH)

mlx:
	@make -sC $(MLX_PATH)
	
clean:
	rm -rf $(OBJ_PATH)
	make -sC $(LIBFT_PATH) fclean
	make -sC $(MLX_PATH) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
