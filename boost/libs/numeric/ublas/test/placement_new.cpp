/*
 * Test placement new and array placement new for uBLAS
 *  See if base pointer is effected by array count cookie
 */

#include <boost/numeric/ublas/config.hpp>
#include <iostream>

// User defined type to capture base pointer on construction
class udt;
udt* base_pointer;

class udt {
public:
    udt () {
       base_pointer = this;
    }
    ~udt () {}      // required for GCC prior to 3.4 to generate cookie
};


int main ()
{
    udt a;
    udt* ap = &a;

    // Capture placement new offsets for a udt    
    new (ap) udt;
    int new_offset = int (base_pointer - ap);
    new (ap) udt [1];
    int array_new_offset = int (base_pointer - ap);
    
    // Print offsets - we expect 0,0 or 0,sizeof(std::size_t)
    std::cout << new_offset <<','<< array_new_offset << std::endl;

    // FIXME find out what version Intel 7.1 for linux says it is
#ifdef BOOST_INTEL
    std::cout << "intel " << BOOST_INTEL <<std::endl;
#endif

    // Return status
    if (new_offset != 0)
        return -1;          // Very bad if new has an offset

#ifdef BOOST_UBLAS_USEFUL_ARRAY_PLACEMENT_NEW
    bool expect_array_offset = false;
#else
    bool expect_array_offset = true;
#endif
        // Check match between config and array
    if (!expect_array_offset && array_new_offset != 0) {
        return -2;          // Bad config should not enable array new
    }
    if (expect_array_offset && array_new_offset == 0) {
        return -3;          // Config could enable array new
    }

    return 0;
}
