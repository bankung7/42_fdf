# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 18:18:35 by vnilprap          #+#    #+#              #
#    Updated: 2022/07/19 12:52:36 by vnilprap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

NAME = libft.a

INC = -Iinc

SRCS_DIR = srcs/
SRCS_LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
       ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c
SRCS_GNL = get_next_line.c
SRCS_FT_PRINTF = ft_convertdi.c ft_convertux.c ft_convertcs.c ft_convertp.c \
		 ft_check.c ft_util.c ft_util2.c ft_printf.c

OBJS_DIR = obj/
OBJS_LIBFT = $(addprefix $(OBJS_DIR),$(SRCS_LIBFT:.c=.o))
OBJS_GNL = $(addprefix $(OBJS_DIR),$(SRCS_GNL:.c=.o))
OBJS_FT_PRINTF = $(addprefix $(OBJS_DIR), $(SRCS_FT_PRINTF:.c=.o))

all: $(NAME)

$(NAME): $(OBJS_LIBFT) $(OBJS_GNL) $(OBJS_FT_PRINTF)
	@ar rcs $@ $^
	@echo "\033[32m libft is ready"

# libft
$(OBJS_DIR)%.o: ./srcs/libft/%.c
	@echo "\033[33m compling [$@]"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I./inc -c $^ -o $@
	@printf "\033[A \033[K"

# get_next_line
$(OBJS_DIR)%.o: ./srcs/get_next_line/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I./inc -c $^ -o $@

# ft_printf
$(OBJS_DIR)%.o: ./srcs/ft_printf/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I./inc -c $^ -o $@

clean:
	@$(RM) $(OBJS_DIR)
	@echo "libft is clean"

fclean: clean
	@$(RM) $(NAME)
	@echo "libft is fclean"

re: fclean all

.PHONY: all clean fclean comply
