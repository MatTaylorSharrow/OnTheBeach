#include <string>
#include <utility>
#include <algorithm>
#include "otblibrary.h"
#include <boost/algorithm/string.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

OTBLibrary::OTBLibrary()
{
}


std::string OTBLibrary::sort_jobs(const std::string &adj_list_rep)
{
    std::string adj_list_rep_copy = adj_list_rep;
    boost::algorithm::trim(adj_list_rep_copy);

    if (adj_list_rep_copy == "") {
        return "";
    }

    // parse the adjacency list representation string for vertices and edges
    std::pair<SymbolList, EdgeList> results = parse_adjacency_list(adj_list_rep_copy, "=>", "\n");

    // do the topological sort
    std::vector<int> sorted_indices = do_topological_sort(results.first, results.second);

    // map the output numeric indexes to vertex symbols
    std::string result_string;
    std::for_each(sorted_indices.begin(), sorted_indices.end(), [&results, &result_string](const int & index) {
        result_string += results.first[index] + " ";
    });

    // return the sorted list of vertices symbols as a string.
    return result_string;
}


std::pair<SymbolList, EdgeList>
OTBLibrary::parse_adjacency_list(
        const std::string & source,
        const std::string & symbol_separator,
        const std::string & rule_separator)
{
    //    Split the string into lines by \n
    //    Split the lines into symbols on =>,
    //    trim the vertex symbols to remove whitespace
    //    build list of vertex symbols - we'll need this for supplying the total number of vertices to the algorithm, and generating the return string
    //    build list of Edges - mapping of vertex indices
    //

    SymbolList sl {"a", "b", "c"};
    EdgeList el {std::make_pair(1,3), std::make_pair(0,2)};

    return std::make_pair(sl, el);
}


std::vector<int>
OTBLibrary::do_topological_sort(
        const SymbolList & symbols,
        const EdgeList & edgelist)
{
    using namespace std;
    using namespace boost;

    typedef std::pair<int,int>                                 Edge;       // Connection between two Vetices (or nodes)
    typedef adjacency_list<vecS, vecS, directedS, no_property> Graph;      // the graph data structure based on adjacency_list
    typedef boost::graph_traits<Graph>::vertex_descriptor      Vertex;     // aka a Node
    typedef std::vector<Vertex>                                container;  // for the results
    typedef property_map<Graph, vertex_index_t>::type          IndexMap;   //

    Edge edges[edgelist.size()];
    // Populate 'edges' array from EdgeList data
    int j = 0;
    for_each(edgelist.begin(), edgelist.end(), [&edges,&j](const std::pair<int,int> & vertex_pair) {
        edges[j++] = Edge(vertex_pair.first, vertex_pair.second);
    });

    Graph g(edges, edges + sizeof(edges) / sizeof(Edge), symbols.size() /* no. of vertices */);
    container c;
    topological_sort(g, std::back_inserter(c));

    std::vector<int> result;
    IndexMap index = get(vertex_index, g);
    for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii) {
        result.push_back(index[*ii]);
    }

    return result;
}
