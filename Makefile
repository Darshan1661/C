# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I. -g

# Target program name
TARGET = bin

# Source and object files
SRCS = c.c
OBJS = $(SRCS:.c=.o)

# Default rule (when you just type "make")
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up (run "make clean")
clean:
	rm -f $(OBJS) $(TARGET)

