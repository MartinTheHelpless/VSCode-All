# Compiler and flags
CC = gcc
CFLAGS = -Isrc/Include
LDFLAGS = -Lsrc/lib
LIBS = -lmingw32 -lSDL2 -lSDL2_image -lSDL2_ttf

# Source and target
SOURCE = main.c
TARGET = Chess

# Build target
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

# Clean up
clean:
	rm -f $(TARGET)
