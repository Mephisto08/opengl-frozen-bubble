#include "Node.h"

Node::Node(string name) : name(move(name)) {}

const string &Node::getName() const {
    return name;
}

const Color &Node::getColor() const {
    return color;
}

void Node::setColor(const Color &c) {
    Node::color = c;
}

void Node::setColor(int r, int g, int b) {
    Node::color = Color(r, g, b);
}

void Node::setColor(int r, int g, int b, int a) {
    Node::color = Color(r, g, b, a);
}
