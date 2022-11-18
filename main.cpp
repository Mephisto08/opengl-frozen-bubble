#include <iostream>
#include "Graph.h"
#include "Node.h"
using namespace std;

int main() {
    Graph g;
    Node* a = g.addNode("A");
    g.addNode("B");
    cout << a->getName() << endl;
    g.removeNode("A");
    Node* b = g.getNode("B");
    cout << b->getName() << endl;
    g.addNode("C");
    g.addNode("A");
    g.addEdge("C", "B");
    g.addEdge("A", "C");
    g.removeNode("B");
    if(g.checkEdge("C", "A")) {
        cout << "Edge between C and A!" << endl;
    }
    auto edgesOfC = g.getEdges("C");
    g.print();
    return 0;
}