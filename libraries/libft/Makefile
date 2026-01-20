# Library Name
NAME := libft.a

# Archive
AR := ar rcs

# Compiler and flags
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra
CFLAGS		+= -MMD -MP -g
MAKEFLAGS	+= --no-print-directory
INCLUDES	:= -I include

# Directories
SRCDIR	:= src/
OBJDIR	:= obj/
INCDIR	:= include/

# Sources
SRCS :=	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_chardup.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line_utils.c \
		get_next_line.c \
		ft_strcmp.c \

# Objects and dependencies
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
