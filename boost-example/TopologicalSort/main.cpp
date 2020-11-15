#include <iostream>

using namespace std;

int main()
{
    typedef adjacency_list< vecS, vecS, directedS, color_property<> > Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    Pair edges[6] = { Pair(0,1), Pair(2,4),
                      Pair(2,5),
                      Pair(0,3), Pair(1,4),
                      Pair(4,3) };
    Graph G(6, edges, edges + 6);

    typedef std::vector< Vertex > container;
    container c;
    topological_sort(G, std::back_inserter(c));

    cout << "A topological ordering: ";
    for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii)
      cout << index(*ii) << " ";
    cout << endl;
}
