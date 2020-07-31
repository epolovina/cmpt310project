CXX = g++
CXXFLAGS = -g -Wall -Wpedantic
BUILD_DIR = build
OBJECTS = mcts.o main.o reversi.o
TARGET = main

OBJECT := $(addprefix $(BUILD_DIR)/,$(OBJECTS))

.PHONY: all valgrind clean

all: $(TARGET)

$(TARGET): $(OBJECT) 
	$(CXX) $(CXXFLAGS) $(OBJECT) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

valgrind: out
	valgrind -s --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --show-reachable=yes\
			$(TARGET)

clean:
	rm -Rf *.o *.out out build main mcts reversi

$(BUILD_DIR):
	mkdir $@
