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
    catch (boost::not_a_dag & e) {
//        std::string const * fn = boost::get_error_info<boost::not_a_dag>(e);
//        std::cout << "File name: " << *fn << "\n";
    }
    /*catch (std::logic_error & e) {

    }*/

    return 0;
}
