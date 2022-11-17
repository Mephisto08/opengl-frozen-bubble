#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/graphviz.hpp>
# include <boost/graph/lookup_edge.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<listS, listS, undirectedS, int> Graph;
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
    add_edge(vertex_by_label("a", lg), vertex_by_label("c", lg), lg);


    std::cout << "===================\nnum_vertices = " << num_vertices(lg) << "\n";
    for (std::string name : { "a", "b", "c", "d", "e" })
        std::cout << name + " = " << vid[vertex_by_label(name, lg)] << "\n";
    for (auto v : make_iterator_range(vertices(lg)))
        std::cout << vid[v] << " ";
    std::cout << "\n";

    auto nb = lookup_edge(vertex_by_label("a", lg), vertex_by_label("b", lg), lg).second;
    auto nnb = lookup_edge(vertex_by_label("a", lg), vertex_by_label("c", lg), lg).second;
    auto nnnb = lookup_edge(vertex_by_label("a", lg), vertex_by_label("d", lg), lg).second;
    std::cout << "B: ab" << " = " << nb << "\n";
    std::cout << "B: ac" << " = " << nnb << "\n";
    std::cout << "B: ad" << " = " << nnnb << "\n";


    // lg.remove_vertex("c");
    clear_vertex(vertex_by_label("c", lg), lg);
    remove_vertex("c", lg);

    std::cout << "===================\nnum_vertices = " << num_vertices(lg) << "\n";
    for (std::string name : { "a", "b", /* "c",*/ "d", "e" })
        std::cout << name + " = " << vid[vertex_by_label(name, lg)] << "\n";
    for (auto v : make_iterator_range(vertices(lg)))
        std::cout << vid[v] << " ";
    std::cout << "\n";

    std::cout << "===================\n DEINE MUM VITALI = " << num_vertices(lg) << "\n";

    auto n = lookup_edge(vertex_by_label("a", lg), vertex_by_label("b", lg), lg).second;
    auto nn = lookup_edge(vertex_by_label("a", lg), vertex_by_label("c", lg), lg).second;
    auto nnn = lookup_edge(vertex_by_label("a", lg), vertex_by_label("d", lg), lg).second;
    std::cout << "ab" << " = " << n << "\n";
    std::cout << "ac" << " = " << nn << "\n";
    std::cout << "ad" << " = " << nnn << "\n";

    return 0;
}