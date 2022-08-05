NAME = fdf

# CC
CC = gcc
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
SRCS = fdf.c parsing.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
#	$(CC) $(CFLAGS) $^ $(MLX) $(MLX_FLAGS) -o $@
	$(CC) $(CFLAGS) $^ $(MLX_LINUX) $(MLX_FLAGS_LINUX) -o $@
	@echo "fdf is ready"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
#	$(CC) $(CFLAGS) $(MLX_INC) $(INC) -c $< -o $@
	$(CC) $(CFLAGS) $(MLX_INC_LINUX) $(INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS_DIR)
	@echo "clean"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "fclean"

re: fclean all

.PHONY: all clean fclean re
