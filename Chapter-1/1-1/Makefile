# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I. -g

# Target program name
TARGET = $(SRCS:.c=)  # in SRCS remove .c and add nothing  

# Source and object files
SRCS = $(wildcard *.c) # fetch all .c file from folder
OBJS = $(SRCS:.c=.o) # in SRCS remove .c and add .o 

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
	rm -f $(OBJS) 
clean1:
	rm -f $(TARGET)

