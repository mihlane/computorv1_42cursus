# Makefile for a simple C project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Executable name
NAME = computor

# Source files
SRCS = computor.c\
	ft_split.c\
	ft_strjoin.c \
	ft_substr.c \

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild from scratch
re: fclean all
