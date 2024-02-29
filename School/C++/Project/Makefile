# Compiler and flags
CC = g++
CFLAGS = -Isrc/include
LDFLAGS = -Lsrc/lib
LIBS = -lmingw32 -lSDL2 -lSDL2_image -lSDL2_ttf

# Source and target
SOURCE_FILES = $(wildcard *.cpp)
SOURCE = main.cpp 
TARGET = Maze

# Build target
all: $(TARGET)

$(TARGET): $(SOURCE_FILES) $(SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Clean up
clean:
	rm -f $(TARGET)
