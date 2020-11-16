#include <string>
#include "otblibrary.h"
#include <boost/algorithm/string.hpp>

OTBLibrary::OTBLibrary()
{
}


std::string OTBLibrary::sort_jobs(const std::string &adj_list_rep) {

    std::string adj_list_rep_copy = adj_list_rep;
    boost::algorithm::trim(adj_list_rep_copy);

    if (adj_list_rep_copy == "") {
        return "";
    }

    // parse the adjacency list representation string for vertices and edges
    //    Split the string into lines by \n
    //    Split the lines into symbols on =>,
    //    trim the vertex symbols to remove whitespace
    //    build list of vertex symbols - we'll need this for supplying the total number of vertices to the algorithm, and generating the return string
    //    build list of Edges - mapping of vertex indices
    //
    // do the topological sort
    // map the output numeric indexes to vertex symbols
    // return the sorted list of vertices symbols as a string.

    return "test";
}
