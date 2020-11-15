#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

using namespace std;
using namespace boost;

int main()
{
    // define our concepts as real types to improve readability and stop our eyes from bleeding.
    typedef std::pair<int,int>                                 Edge;       // Connection between two Vetices (or nodes)
    typedef adjacency_list<vecS, vecS, directedS, no_property> Graph;      // the graph data structure based on adjacency_list
    typedef boost::graph_traits<Graph>::vertex_descriptor      Vertex;     // aka a Node
    typedef std::vector<Vertex>                                container;  // for the results
    typedef property_map<Graph, vertex_index_t>::type          IndexMap;   //

    enum vertices {A,B,C,D,E,F}; // serves no real purpose except to help highlight the example
    //             0,1,2,3,4,5
    //    A--→--\
    //    ↓     |
    //    B     |
    //    ↓     |
    //    E--→--D
    //    ↑
    //    C-→-F
    // Create an array of Edges to define the edges or arcs within the Graph
    Edge edges[6] = {
        Edge(0,1), // A-B
        Edge(2,4), // C-E
        Edge(2,5), // C-F
        Edge(0,3), // A-D
        Edge(1,4), // B-E
        Edge(4,3)  // E-D
    };

    // create the Graph
    Graph g(edges, edges + sizeof(edges) / sizeof(Edge), 6);

    // create a container for the results
    container c;

    // Here's the science bit!!
    // sort the Graph 'g'
    topological_sort(g, std::back_inserter(c));

    cout << "A topological ordering: ";
    IndexMap index = get(vertex_index, g);
    for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii) {
      cout << index[*ii] << " ";
    }
    cout << endl;
}
