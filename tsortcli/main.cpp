#include <iostream>

#include "../OTBLibrary/otblibrary.h"
#include <string>
#include <boost/exception/all.hpp>
#include <boost/graph/exception.hpp>

using namespace std;

int main()
{
    auto input = R"INPUT(a =>
b => c
c => f
d => a
e =>
f => b)INPUT";

    OTBLibrary otbl;
    try {
        auto joblist = otbl.sort_jobs(input);
        std::cout << joblist << std::endl;
    }
    catch (std::invalid_argument & e) {
        std::cerr << "Sorting Jobs failed. Because: " << e.what() << std::endl;
    }

    return 0;
}
