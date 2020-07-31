CC = g++
CCFLAGS = -g -Wall -Wpedantic
TARGET = mcts.o reversi.o main.o

all: clean build

build: mcts reversi main

mcts: $(TARGET)
	$(CC) $(CCFLAGS) $(TARGET) -o mcts

reversi: $(TARGET)
	$(CC) $(CCFLAGS) $(TARGET) -o reversi

main: $(TARGET)
	$(CC) $(CCFLAGS) $(TARGET) -o main

$(TARGET): %.o: %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@

valgrind: myls
	valgrind -s --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --show-reachable=yes\
			./myls

clean:
	rm -f *.o *.out mcts reversi main