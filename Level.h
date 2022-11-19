#ifndef HMI_LEVEL_H
#define HMI_LEVEL_H
#include <utility>
#include "Graph.h"

class Level {
private:
    string name;
    Graph graph;
    vector<string> colors;
public:
    void setColors(const vector<string> &colors);

public:
    Level(string n, Graph g);
    explicit Level(const string &name);

    void print();

    void insertNode(char row, int column);
    const string &getName() const;
};

#endif //HMI_LEVEL_H