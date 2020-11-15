#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

using namespace std;
using namespace boost;

int main()
{
    typedef std::pair<int,int> Edge;
    typedef adjacency_list<vecS, vecS, directedS, color_property<>> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef std::vector<Vertex> container;

    Edge edges[6] = {
        Edge(0,1),
        Edge(2,4),
        Edge(2,5),
        Edge(0,3),
        Edge(1,4),
        Edge(4,3)
    };

    Graph G(6, edges, edges + 6);

    container c;
    topological_sort(G, std::back_inserter(c));

    cout << "A topological ordering: ";
    for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii)
      cout << index(*ii) << " ";
    cout << endl;
}
