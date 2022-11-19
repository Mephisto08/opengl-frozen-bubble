#ifndef HMI_LEVEL_H
#define HMI_LEVEL_H
#include <utility>
#include "Graph.h"

class Level {
private:
    string name;
    Graph graph;

public:
    Level(string n, Graph g);

    void print();
    void insertNode(char row, int column);
    const string &getName() const;
};

#endif //HMI_LEVEL_H