#include <boost/archive/polymorphic_text_woarchive.hpp>
typedef boost::archive::polymorphic_text_woarchive test_oarchive;
typedef std::wofstream test_ostream;
#include <boost/archive/polymorphic_text_wiarchive.hpp>
typedef boost::archive::polymorphic_text_wiarchive test_iarchive;
typedef std::wifstream test_istream;
#define TEST_STREAM_FLAGS (std::ios_base::openmode)0
