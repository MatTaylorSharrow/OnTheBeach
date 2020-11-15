#ifndef OTBLIBRARY_H
#define OTBLIBRARY_H

#include "OTBLibrary_global.h"
#include <string>

class OTBLIBRARY_EXPORT OTBLibrary
{
public:
    OTBLibrary();

    static std::string sort_jobs(const std::string &adj_list_rep);
};

#endif // OTBLIBRARY_H
