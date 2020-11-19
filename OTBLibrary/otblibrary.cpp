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
    std::vector<std::string> sorted_symbols;
    std::for_each(sorted_indices.begin(), sorted_indices.end(), [&results, &sorted_symbols](const int & index) {
        sorted_symbols.push_back(results.first[index]);
    });
    std::string result_string;
    result_string = boost::algorithm::join(sorted_symbols, " ");

    // return the sorted list of vertices symbols as a string.
    return result_string;
}


std::pair<SymbolList, EdgeList>
OTBLibrary::parse_adjacency_list(
        const std::string & source,
        const std::string & symbol_separator,
        const std::string & rule_separator)
{
    typedef std::vector<std::pair<std::string,std::string>> EdgeListStr;
    EdgeListStr els;
    SymbolList lines, symbols;

    // Split the string into lines by \n
    boost::algorithm::split(lines, source, boost::algorithm::is_any_of(rule_separator));

    // Split the lines into symbols on =>,
    for (const auto & line : lines) {
        SymbolList linesymbs, ls_tmp;
        boost::algorithm::split(linesymbs, line, boost::algorithm::is_any_of(symbol_separator));

        // trim the vertex symbols to remove whitespace and remove empty symbols
        for (auto & symbol : linesymbs) {
            boost::algorithm::trim(symbol);
            if (symbol != "") {
                ls_tmp.push_back(symbol);
            }
        }
        linesymbs.swap(ls_tmp);

        if (linesymbs.size() > 1) {
            // we have a dependancy so define an edge
            els.push_back(std::make_pair(linesymbs[0], linesymbs[1]));
        }

        std::sort(linesymbs.begin(), linesymbs.end());

        std::for_each(linesymbs.begin(), linesymbs.end(), [&linesymbs](const std::string & symbol){
            if (std::count(linesymbs.begin(), linesymbs.end(), symbol) > 1) {
                throw std::invalid_argument("Self reference detected. The job symbol '" + symbol + "' can not depend on itself");
                // This check ensures symbols are unique within a dependancy line, so we don't need to perform a unique before merging symbols
            }
        });

        // build list of vertex symbols - we'll need this for supplying the total number of vertices to the algorithm, and generating the return string
        std::vector<std::string> tmp;
        std::set_union(symbols.begin(), symbols.end(), linesymbs.begin(), linesymbs.end(), std::back_inserter(tmp)); // merge
        symbols.swap(tmp);

        // sort prior to unique
        std::sort(symbols.begin(), symbols.end());
        // remove duplicate concurrent symbols
        auto last = std::unique(symbols.begin(), symbols.end());
        symbols.erase(last, symbols.end());
    }

    // create a mapping of symbol to index position
    std::map<std::string, int> symbol_indices;
    int i=0;
    for (std::string &symbol : symbols) {
        symbol_indices.emplace(symbol, i++);
    }

    // build list of Edges - mapping the symbol string to index
    EdgeList el;
    std::for_each(els.begin(), els.end(), [&symbol_indices, &el](const std::pair<std::string,std::string> & edge_symbols){
        el.push_back(std::make_pair(
            symbol_indices.find(edge_symbols.first)->second,
            symbol_indices.find(edge_symbols.second)->second
        ));
    });

    return std::make_pair(symbols, el);
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

    try {
        topological_sort(g, std::back_inserter(c));
    }
    catch (boost::not_a_dag & e) {
        throw std::invalid_argument(e.what());
    }

    std::vector<int> result;
    IndexMap index = get(vertex_index, g);
    for ( container::iterator ii=c.begin(); ii!=c.end(); ++ii) {
        result.push_back(index[*ii]);
    }

    return result;
}
