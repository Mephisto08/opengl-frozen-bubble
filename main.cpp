#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<listS, vecS, undirectedS, int> Graph;
typedef labeled_graph<Graph, string> LabeledGraph;

int main()
{
    LabeledGraph lg;
    auto vid = get(vertex_bundle, lg.graph());

    int id = 0;
    for (string name : { "a", "b", "c", "d", "e" })
        add_vertex(name, id++, lg);
    // add some edges
    add_edge(vertex_by_label("a", lg), vertex_by_label("b", lg), lg);


    std::cout << "===================\nnum_vertices = " << num_vertices(lg) << "\n";
    for (std::string name : { "a", "b", "c", "d", "e" })
        std::cout << name + " = " << vid[vertex_by_label(name, lg)] << "\n";
    for (auto v : make_iterator_range(vertices(lg)))
        std::cout << vid[v] << " ";
    std::cout << "\n";

    // lg.remove_vertex("c");
    remove_vertex("c", lg);

    std::cout << "===================\nnum_vertices = " << num_vertices(lg) << "\n";
    for (std::string name : { "a", "b", /* "c",*/ "d", "e" })
        std::cout << name + " = " << vid[vertex_by_label(name, lg)] << "\n";
    for (auto v : make_iterator_range(vertices(lg)))
        std::cout << vid[v] << " ";
    std::cout << "\n";


    auto t = lg.graph();
    // represent graph in DOT format and send to cout
    //write_graphviz(cout, t);

    return 0;
}