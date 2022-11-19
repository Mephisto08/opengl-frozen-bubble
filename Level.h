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
    vector<string> colors;
    
public:
    Level(string n, Graph g);
    explicit Level(const string &name);

    void print();
    void insertNode(char row, int column, Color color);
    void setColors(const vector<string> &colors);
    const string &getName() const;
};

#endif //HMI_LEVEL_H