#include <boost/archive/polymorphic_xml_oarchive.hpp>
typedef boost::archive::polymorphic_xml_oarchive test_oarchive;
typedef std::ofstream test_ostream;
#include <boost/archive/polymorphic_xml_iarchive.hpp>
typedef boost::archive::polymorphic_xml_iarchive test_iarchive;
typedef std::ifstream test_istream;
#define TEST_STREAM_FLAGS (std::ios_base::openmode)0
