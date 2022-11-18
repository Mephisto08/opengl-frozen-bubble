#include "Node.h"

Node::Node(string name) : name(move(name)) {}

const string &Node::getName() const {
    return name;
}
