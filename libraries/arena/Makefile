# Library Name
NAME := arena.a

# Archive
AR := ar rcs

# Compiler and Flags
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g
CFLAGS		+= -MMD -MP
MAKEFLAGS	+= --no-print-directory
INCLUDES	:= -I include

# Directories
SRCDIR := src/
OBJDIR := obj/
INCDIR := include/

# Sources
SRCS :=	arena.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_realloc.c \

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

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo $(GREEN)Library $(NAME) compiled$(RESET)

-include $(DEPS)

clean:
	@rm -rf $(OBJDIR)
	@echo $(GREEN)$(NAME) object files cleaned$(RESET)

fclean: clean
	@rm -rf $(NAME)
	@echo $(GREEN)$(NAME) cleaned$(RESET)

re:	fclean all

.PHONY: all clean fclean re
