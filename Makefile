CC = g++
CCFLAGS = -g -Wall -Wpedantic
TARGET = mcts.o

all: clean mcts

mcts: $(TARGET)
	$(CC) $(CCFLAGS) $(TARGET) -o mcts

$(TARGET): %.o: %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@

valgrind: myls
	valgrind -s --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --show-reachable=yes\
			./myls

clean:
	rm -f *.o *.out mcts

