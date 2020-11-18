#define BOOST_TEST_MODULE TopologicalSortTestSuite
#include <boost/test/included/unit_test.hpp>

#include "../OTBLibrary/otblibrary.h"
#include <string>
#include <boost/exception/all.hpp>
#include <boost/graph/exception.hpp>

BOOST_AUTO_TEST_CASE( TestEmtpyString )
{
    OTBLibrary otbl;
    BOOST_TEST( otbl.sort_jobs("") == "");
}

BOOST_AUTO_TEST_CASE( TestSingleJob )
{
    OTBLibrary otbl;
    BOOST_TEST( otbl.sort_jobs("a =>") == "a");
}

BOOST_AUTO_TEST_CASE( TestNoDependancies )
{
    auto input = R"INPUT(a =>
b =>
c =>)INPUT";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);
    BOOST_TEST( joblist.find("a") != std::string::npos );
    BOOST_TEST( joblist.find("b") != std::string::npos );
    BOOST_TEST( joblist.find("c") != std::string::npos );
}

BOOST_AUTO_TEST_CASE( TestSingleDependancy )
{
    auto input = R"INPUT(a =>
b => c
c =>)INPUT";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);

    BOOST_TEST( joblist.find("a") != std::string::npos );
    BOOST_TEST( joblist.find("b") != std::string::npos );
    BOOST_TEST( joblist.find("c") != std::string::npos );

    BOOST_TEST( joblist.find("c") < joblist.find("b") ); // c is before b
}

BOOST_AUTO_TEST_CASE( TestMultiDependancy )
{
    auto input = R"INPUT(a =>
b => c
c => f
d => a
e => b
f =>)INPUT";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);

    //std::string joblist = "a d f c b e";

    BOOST_TEST( joblist.find("a") != std::string::npos );
    BOOST_TEST( joblist.find("b") != std::string::npos );
    BOOST_TEST( joblist.find("c") != std::string::npos );
    BOOST_TEST( joblist.find("d") != std::string::npos );
    BOOST_TEST( joblist.find("e") != std::string::npos );
    BOOST_TEST( joblist.find("f") != std::string::npos );

    BOOST_TEST( joblist.find("f") < joblist.find("c") ); // f is before c
    BOOST_TEST( joblist.find("c") < joblist.find("b") ); // c is before b
    BOOST_TEST( joblist.find("b") < joblist.find("e") ); // b is before e
    BOOST_TEST( joblist.find("a") < joblist.find("d") ); // a is before d
}


BOOST_AUTO_TEST_CASE( TestSelfReferencialError )
{
    auto input = R"INPUT(a =>
b =>
c => c)INPUT";


    OTBLibrary otbl;
    try {
        auto joblist = otbl.sort_jobs(input);
    }
    catch (std::logic_error &e)
    {
        BOOST_TEST( true );
        return;
    }

    BOOST_TEST( false );
}


BOOST_AUTO_TEST_CASE( TestCircularReferenceError )
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
    }
    catch (boost::not_a_dag & e) {
        BOOST_TEST( true );
        return;
    }
    catch (std::logic_error & e) {
        BOOST_TEST( false );
        return;
    }

    BOOST_TEST( false );
}
