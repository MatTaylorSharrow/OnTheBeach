#define BOOST_TEST_MODULE TopologicalSortTestSuite
#include <boost/test/included/unit_test.hpp>

#include "../OTBLibrary/otblibrary.h"

BOOST_AUTO_TEST_CASE( TopologicalSortTestCase )
{
    BOOST_TEST( true /* test assertion */ );
    BOOST_TEST( OTBLibrary::sort_jobs("input string") == "test" );
}
