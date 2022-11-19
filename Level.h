#ifndef HMI_LEVEL_H
#define HMI_LEVEL_H
#include <utility>
#include "Graph.h"

const int LOWER_COLUMN = 0;
const int UPPER_COLUMN = 7;
const char LOWER_ROW = 'A';
const char UPPER_ROW = 'M';

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