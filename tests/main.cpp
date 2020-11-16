#define BOOST_TEST_MODULE TopologicalSortTestSuite
#include <boost/test/included/unit_test.hpp>

#include "../OTBLibrary/otblibrary.h"
#include <string>


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
    auto input =
"a =>"
"b =>"
"c =>";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);

    BOOST_TEST( joblist.find("a") != std::string::npos );
    BOOST_TEST( joblist.find("b") != std::string::npos );
    BOOST_TEST( joblist.find("c") != std::string::npos );
}

BOOST_AUTO_TEST_CASE( TestSingleDependancy )
{
    auto input =
"a =>"
"b => c"
"c =>";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);

    BOOST_TEST( joblist.find("a") != std::string::npos );
    BOOST_TEST( joblist.find("b") != std::string::npos );
    BOOST_TEST( joblist.find("c") != std::string::npos );

    BOOST_TEST( joblist.find("c") < joblist.find("b") ); // c is before b
}

BOOST_AUTO_TEST_CASE( TestMultiDependancy )
{
    auto input =
"a =>"
"b => c"
"c => f"
"d => a"
"e => b"
"f =>";

    OTBLibrary otbl;
    auto joblist = otbl.sort_jobs(input);

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
    auto input =
"a =>"
"b =>"
"c => c";

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
    auto input =
"a =>"
"b => c"
"c => f"
"d => a"
"e =>"
"f => b";

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
