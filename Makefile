# Makefile for C program

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source and header file directories
SRC_DIR = src
HDR_DIR = headers

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXE = mymitmproxy

# Include directories
INC = -I$(HDR_DIR)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $^ -o $@

clean:
	rm -f $(OBJ) $(EXE)
