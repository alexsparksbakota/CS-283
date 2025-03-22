# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = dsh

# Source files, specific to assignment
SRC = dsh_cli.c dshlib.c

# Default target
all: $(TARGET)

# Compile source to executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	-del /f /q $(TARGET).exe 2>nul || rm -f $(TARGET)

# Phony targets
.PHONY: all clean
