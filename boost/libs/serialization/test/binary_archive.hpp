// binary_archive
#include <boost/archive/binary_oarchive.hpp>
typedef boost::archive::binary_oarchive test_oarchive;
typedef std::ofstream test_ostream;
#include <boost/archive/binary_iarchive.hpp>
typedef boost::archive::binary_iarchive test_iarchive;
typedef std::ifstream test_istream;
#define TEST_STREAM_FLAGS std::ios::binary

