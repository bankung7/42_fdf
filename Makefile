# Color
R = \033[0;31m
G = \033[0;32m
Y = \033[0;33m
N = \033[0m

NAME = fdf

# CC
CC = gcc -g
CFLAGS = -Wall -Werror -Wextra

# INC
INC = -Iinc -Ilibft/inc -Ilibft/libft

# MLX_LINUX
MLX_LINUX = mlx_linux/libmlx_Linux.a
MLX_INC_LINUX = -I/usr/include -Imlx_linux
MLX_FLAGS_LINUX = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
# MLX_MACOS
MLX = mlx/libmlx.a
MLX_INC = -Imlx
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

# Libft
LIBFT_DIR = libft/
LIBFT = libft/libft.a

RM = rm -rf

SRCS_DIR = srcs/
SRCS = fdf.c parsing.c draw.c exit.c hook.c matrix.c setup.c utils.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(MLX) $(MLX_FLAGS) -o $@
#	@$(CC) $(CFLAGS) $^ $(MLX_LINUX) $(MLX_FLAGS_LINUX) -o $@
	@echo "$(G)fdf is ready$(N)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "$(Y)compling [$@]$(N)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(MLX_INC) $(INC) -c $< -o $@
#	@$(CC) $(CFLAGS) $(MLX_INC_LINUX) $(INC) -c $< -o $@
	@printf "\033[A \033[K"

$(LIBFT):
	@make -C mlx/
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS_DIR)
	@echo "$(R)fdf is clean$(N)"

fclean: clean
	@make clean -C mlx
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(R)fdf is fclean$(N)"

re: fclean all

.PHONY: all clean fclean re
