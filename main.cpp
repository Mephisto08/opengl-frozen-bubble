#include <iostream>
#include "Graph.h"
#include "Node.h"
using namespace std;

int main() {
    Graph g;
    Node* a = g.addNode("A");
    g.addNode("B");
    cout << "Name: " << a->getName() << endl;
    g.removeNode("A");
    Node* b = g.getNode("B");
    cout << "Color (r): " <<  b->getColor().r << endl;
    b->setColor(123, 255, 255);
    cout << "Color (r): " <<  b->getColor().r << endl;
    g.addNode("C");
    g.addNode("A");
    g.addEdge("C", "B");
    g.addEdge("A", "C");
    g.removeNode("B");
    g.print();
    if(g.checkEdge("C", "A")) {
        cout << "Edge between C and A!" << endl;
    }
    set<string> neighborsOfC = g.getNeighbors("C");
    g.clear();
    g.addNode("A");
    g.addNode("B");
    g.addNode("X");
    g.addNode("Y");
    g.addNode("Z");
    g.addEdge("A", "Y");
    g.addEdge("X", "A");
    g.addEdge("B", "Z");
    g.addEdge("X", "Z");
    g.addEdge("X", "B");
    g.print();
    if(g.checkPath("A", "Z")) {
        cout << "Path from A to Z before removing X!" << endl;
    }
    g.removeNode("X");
    g.print();
    if(g.checkPath("A", "Z")) {
        cout << "Path from A to Z after removing X!" << endl;
    }
    return 0;
}