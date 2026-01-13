NAME			:=	cub3D
CC				:=	cc
CFLAGS			:=	-Wall -Werror -Wextra
MLX_FLAGS		:= -Iinclude -ldl -lglfw -pthread -lm

LIBRARIES		:=	./libraries/libft/libft.a\
					./MLX42/build/libmlx42.a\

LIBFT			:= ./libraries/libft
MLX42_DIR		:= ./MLX42
MLX42			:= ./MLX42/build

SOURCES_DIR		:=	sources/
SOURCES			:=	main.c\

OBJECTS_DIR		:=	objects/
OBJECTS			:= $(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))
HEADERS			:=	-I ./includes -I ./libraries/libft

NO_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
CYAN = \033[0;96m

all:		libraries $(NAME)
			$(info Finished compiling so_long)

$(NAME):	$(OBJECTS)
				$(CC) $(CFLAGS) -o $@ $^ $(HEADERS) $(LIBRARIES) $(MLX_FLAGS)


$(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $< -O3

$(MLX42_DIR):
		@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
		fi
		@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
		@$(MAKE) -C $(MLX42_DIR)/build -j4

libraries:	$(MLX42_DIR)
			$(MAKE) -C $(LIBFT)
			

clean:
			@rm -rf $(OBJECTS)
			@$(MAKE) -C $(LIBFT) clean

fclean:		clean
			@rm -rf $(NAME)
			@$(MAKE) -C $(LIBFT) fclean
			@if [ -d "$(OBJECTS_DIR)" ]; then rm -drf $(OBJECTS_DIR); fi
			@if [ -d "$(MLX42_DIR)" ]; then rm -drf $(MLX42_DIR); fi
			@echo "$(GREEN)Cleaned up all created files.$(NO_COLOR)"

re:	fclean all

.PHONY:		all libraries clean fclean re