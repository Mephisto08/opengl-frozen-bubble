#ifndef HMI_NODE_H
#define HMI_NODE_H
#include <map>
#include <utility>
using namespace std;

class Node {
private:
    string name;
    map<string, Node*> edges;
public:
    explicit Node(string  n);
    const string &getName() const;
};

#endif //HMI_NODE_H