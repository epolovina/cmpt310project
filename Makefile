CXX = g++
CXXFLAGS = -g -Wall -Wpedantic -pthread
BUILD_DIR = build
SUBMIT_DIR = submission
OBJECTS = mcts.o main.o reversi.o
TARGET = main

OBJECT := $(addprefix $(BUILD_DIR)/,$(OBJECTS))

.PHONY: all valgrind clean

all: $(TARGET)

$(TARGET): $(OBJECT) 
	$(CXX) $(CXXFLAGS) $(OBJECT) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

sub: $(SUBMIT_DIR)
	cp -t submission/\
		main.cpp main.hpp\
		mcts.cpp mcts.hpp\
		reversi.cpp reversi.hpp\
		README.md\
		Makefile

zip: sub
	zip -r 310FinalProj.zip submission

clean:
	rm -Rf *.o *.out out build main mcts reversi submission

$(BUILD_DIR):
	mkdir $@

$(SUBMIT_DIR):
	mkdir $@