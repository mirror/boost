// binary_warchive
#include <boost/archive/binary_woarchive.hpp>
typedef boost::archive::binary_woarchive test_oarchive;
typedef std::wofstream test_ostream;
#include <boost/archive/binary_wiarchive.hpp>
typedef boost::archive::binary_wiarchive test_iarchive;
typedef std::wifstream test_istream;
#define TEST_STREAM_FLAGS std::wios::binary
