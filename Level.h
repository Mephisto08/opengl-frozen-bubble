#ifndef HMI_LEVEL_H
#define HMI_LEVEL_H
#include <utility>
#include "Graph.h"

class Level {
private:
    string name;
    Graph graph;
    map<string, Color> colors;
    
public:
    Level(string n, Graph g);
    explicit Level(const string &name);

    void setColors(const map<string, Color> &colors);

    void print();
    void insertNode(char row, int column, Color color);
    const string &getName() const;
};

#endif //HMI_LEVEL_H