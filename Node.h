#ifndef HMI_NODE_H
#define HMI_NODE_H
#include <map>
#include <utility>
#include "Color.h"
using namespace std;

class Node {
private:
    string name;
    Color color;
public:
    explicit Node(string  n);
    const string &getName() const;
    const Color &getColor() const;
    void setColor(const Color &c);
    void setColor(int r, int g, int b);
    void setColor(int r, int g, int b, int a);
};

#endif //HMI_NODE_H