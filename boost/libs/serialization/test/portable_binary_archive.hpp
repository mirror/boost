// file includes for testing a custom archive.
// as an example this tests the portable binary archive

// #include output archive header
#include "../example/portable_binary_oarchive.hpp"
// define output archive class to be used 
typedef portable_binary_oarchive test_oarchive;
// and corresponding stream
typedef std::ofstream test_ostream;

// repeat the above for correspondng input archive
#include "../example/portable_binary_iarchive.hpp"
typedef portable_binary_iarchive test_iarchive;
typedef std::ifstream test_istream;

// and stream open flags
#define TEST_STREAM_FLAGS std::ios::binary
