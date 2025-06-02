# Makefile for a simple C project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Executable name
NAME = computor

# Source files
SRCS = mlx.c \
	ft_split.c \
	ft_strjoin.c \
	ft_substr.c \
	irr_fraction.c \


# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lm -lmlx -lXext -lX11

# Rule to create object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild from scratch
re: fclean all

# Make sure these rules don't conflict with files of the same name
.PHONY: all clean fclean re