#include <iostream>

#include "../OTBLibrary/otblibrary.h"
#include <string>
#include <boost/exception/all.hpp>
#include <boost/graph/exception.hpp>

using namespace std;

int main()
{
    std::string inputs[6];
    inputs[0] = "a =>";
    inputs[1] = R"INPUT(a =>
b =>
c =>)INPUT";
    inputs[2] = R"INPUT(a =>
b => c
c =>)INPUT";
    inputs[3] = R"INPUT(a =>
b => c
c => f
d => a
e => b
f =>)INPUT";
    inputs[4] = R"INPUT(a =>
b =>
c => c)INPUT";
    inputs[5] = R"INPUT(a =>
b => c
c => f
d => a
e =>
f => b)INPUT";

    OTBLibrary otbl;
    for(auto & input : inputs) {

        try {
            std::cout << "About to sort the input: " << std::endl << input << std::endl;

            auto joblist = otbl.sort_jobs(input);

            std::cout << std::endl << "Output:" << std::endl;
            std::cout << joblist << std::endl << std::endl;
        }
        catch (std::invalid_argument & e) {
            std::cerr << std::endl << "Sorting input jobs failed. Because: " << e.what() << std::endl << std::endl;
        }
    }

    return 0;
}
