//  (C) Copyright Eric Niebler 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
  Revision history:
  25 August 2005 : Initial version.
*/

#include <boost/test/minimal.hpp>
#include <boost/foreach.hpp>

#ifndef BOOST_FOREACH_USE_RVALUE_REFERENCE_BINDING
# error Expected failure : non-copyable rvalues disallowed
#else

class my_container
{
public:
    my_container()
    {
        array_[0] = 1;
        array_[1] = 2;
        array_[2] = 3;
        array_[3] = 4;
        array_[4] = 5;
    }

    typedef int* iterator;
    typedef int const* const_iterator;

    iterator begin() { return array_; }
    const_iterator begin() const { return array_; }

    iterator end() { return array_ + 5; }
    const_iterator end() const { return array_ + 5; }

private:
    int array_[5];

    // non-copyable
    my_container(my_container const &);
    my_container &operator =(my_container const &);

    // non-movable
    my_container(my_container &&);
    my_container &operator =(my_container &&);
};

///////////////////////////////////////////////////////////////////////////////
// test_main
//   
int test_main( int, char*[] )
{
    int counter = 0;

    BOOST_REVERSE_FOREACH(int i, my_container())
    {
        counter += i;
    }

    BOOST_CHECK(15 == counter);

    return 0;
}

#endif
