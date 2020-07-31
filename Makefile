CXX = g++
CXXFLAGS = -g -Wall -Wpedantic
BUILD_DIR = build
# OUTPUT = $(BUILD_DIR)/out
OBJECTS = mcts
TARGET = mcts

all: clean mcts

mcts: $(OBJECTS).o
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/$(OBJECTS).o -o $(TARGET)

$(OBJECTS).o: %.o: %.cpp | $(BUILD_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $(BUILD_DIR)/$@

valgrind: mcts
	valgrind -s --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --show-reachable=yes\
			./mcts

clean:
	rm -Rf *.o *.out mcts build

$(BUILD_DIR):
	mkdir $@
