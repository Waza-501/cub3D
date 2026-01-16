# Program Name
NAME :=	cub3D

# Library Paths
LIBFT		:= libraries/libft
ARENA		:= libraries/arena
MLX42_DIR	:= MLX42
MLX42		:= MLX42/build

# Libraries
LIBRARIES :=	$(LIBFT)/libft.a \
				$(ARENA)/arena.a \
				$(MLX42)/libmlx42.a \

# Compiler and Flags
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -g
MLX_FLAGS	:= -Iinclude -ldl -lglfw -pthread -lm
MAKEFLAGS	+= --no-print-directory
INCLUDES	:= -I include -I $(LIBFT)/include -I $(ARENA)/include

# Directories
SRCDIR := src/
OBJDIR := obj/
INCDIR := include/

# Sources
SRCS :=	main.c \

# Objects and Dependencies
SRCPATH	:= $(addprefix $(SRCDIR),$(SRCS))
OBJS 	:= $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCPATH:.c=.o))
DEPS 	:= $(OBJS:.o=.d)

# Colors
BLACK	:= "\e[0;30m"
RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
PURPLE	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
WHITE	:= "\e[0;37m"
RESET	:= "\e[0m"

$(OBJDIR)%.o: $(SRCDIR)%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: libraries $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(HEADERS) $(LIBRARIES) $(MLX_FLAGS)
	@echo $(GREEN)$(NAME) compiled$(RESET)

-include $(DEPS)

$(MLX42_DIR):
		@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
		fi
		@cmake $(MLX42_DIR) -B $(MLX42)
		@$(MAKE) -C $(MLX42) -j4

libraries: $(MLX42_DIR)
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(ARENA)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(ARENA) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(ARENA) fclean
	@rm -rf $(MLX42_DIR)
	@echo $(GREEN)Cleaned up all created files.$(RESET)

re:	fclean all

.PHONY: all libraries clean fclean re
