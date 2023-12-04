# Compiler settings - Can be customized.
CC=g++
CFLAGS=-Wall -g
LIBS=-lsimlib

# Define the target executable
TARGET=sim

# List of source files
SOURCES=Day.cpp Field.cpp Harvester.cpp listFile.cpp main.cpp Season.cpp Tractor.cpp test.cpp
# Corresponding object files
OBJECTS=$(SOURCES:.cpp=.o)

# First target - default
all: $(TARGET)

# Link the target with all objects
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile source files into objects
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(TARGET) $(OBJECTS)

# Additional dependencies
Day.o: Day.h
Field.o: Field.h
Harvester.o: Harvester.h
listFile.o: listFile.h
Season.o: Season.h
Tractor.o: Tractor.h
test.o: test.cpp

