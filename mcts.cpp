#include <iostream>

class mcts {
    private:
        std::string name;
    public:
        mcts(std::string n) {
            name = n;
        }
        std::string getName() {
            return name;
        }
};

int main() {
    mcts a("name");
    std::cout << a.getName() << std::endl;


    return 0;
}

