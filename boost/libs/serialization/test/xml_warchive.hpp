// xml_warchive
#include <boost/archive/xml_woarchive.hpp>
typedef boost::archive::xml_woarchive test_oarchive;
typedef std::wofstream test_ostream;
#include <boost/archive/xml_wiarchive.hpp>
typedef boost::archive::xml_wiarchive test_iarchive;
typedef std::wifstream test_istream;
#define TEST_STREAM_FLAGS (std::ios_base::openmode)0


