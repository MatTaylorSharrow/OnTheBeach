#include <iostream>

#include "../OTBLibrary/otblibrary.h"
#include <string>

using namespace std;

int main()
{
    auto input = R"INPUT(a =>
b => c
c => f
d => a
e => b
f =>)INPUT";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);

    std::cout << joblist << std::endl;

    return 0;
}
