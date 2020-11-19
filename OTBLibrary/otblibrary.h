#ifndef OTBLIBRARY_H
#define OTBLIBRARY_H

#include "OTBLibrary_global.h"
#include <string>
#include <algorithm>
#include <utility>


typedef std::vector<std::string>        SymbolList;
typedef std::vector<std::pair<int,int>> EdgeList;

class OTBLIBRARY_EXPORT OTBLibrary
{
public:
    OTBLibrary();

    std::string sort_jobs(const std::string &adj_list_rep);

private:
    std::pair<SymbolList, EdgeList>
    parse_adjacency_list(const std::string & source, const std::string & symbol_separator, const std::string & rule_separator);

    std::vector<int>
    do_topological_sort(const SymbolList & symbols, const EdgeList & edgelist);
};

#endif // OTBLIBRARY_H
