# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I. -g

# Source and object files
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Target program name (remove .c extension from first source file)
TARGET = $(basename $(firstword $(SRCS)))

# Default rule
all: $(TARGET)

# Link object files into final executable (add -lm to link math library)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Rule to compile each .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS)

# Clean up executable
clean1:
	rm -f $(TARGET)

