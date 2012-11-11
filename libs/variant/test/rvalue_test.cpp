//-----------------------------------------------------------------------------
// boost-libs variant/test/rvalue_test.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2012
// Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/config.hpp"

#include "boost/test/minimal.hpp"
#include "boost/variant.hpp"

// This test requires BOOST_HAS_RVALUE_REFS

#ifndef BOOST_HAS_RVALUE_REFS

void run()
{
    BOOST_CHECK(true);
}

#else 

class move_copy_conting_class {
public:
    static unsigned int moves_count;
    static unsigned int copy_count;

    move_copy_conting_class(){}
    move_copy_conting_class(move_copy_conting_class&&) {
        ++ moves_count;
    }

    move_copy_conting_class& operator=(move_copy_conting_class&&) {
        ++ moves_count;
        return *this;
    }

    move_copy_conting_class(const move_copy_conting_class&) {
        ++ copy_count;
    }
    move_copy_conting_class& operator=(const move_copy_conting_class&) {
        ++ copy_count;
        return *this;
    }
};

unsigned int move_copy_conting_class::moves_count = 0;
unsigned int move_copy_conting_class::copy_count = 0;

void run()
{
    typedef boost::variant<int, move_copy_conting_class> variant_I_type;
    variant_I_type v1, v2;
    
    // Assuring that `move_copy_conting_class` was not created
    BOOST_CHECK(move_copy_conting_class::copy_count == 0);
    BOOST_CHECK(move_copy_conting_class::moves_count == 0);
    
    v1 = move_copy_conting_class();
    // Assuring that `move_copy_conting_class` was moved at least once
    BOOST_CHECK(move_copy_conting_class::moves_count != 0);
    
    unsigned int total_count = move_copy_conting_class::moves_count + move_copy_conting_class::copy_count;
    move_copy_conting_class var;
    v1 = 0;
    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    v1 = var;
    // Assuring that move assignment operator moves/copyes value not more times than copy assignment operator
    BOOST_CHECK(total_count <= move_copy_conting_class::moves_count + move_copy_conting_class::copy_count);

    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    v2 = static_cast<variant_I_type&&>(v1);
    // Assuring that `move_copy_conting_class` in v1 was moved at least once and was not copied
    BOOST_CHECK(move_copy_conting_class::moves_count != 0);
    BOOST_CHECK(move_copy_conting_class::copy_count == 0);

    v1 = move_copy_conting_class();
    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    v2 = static_cast<variant_I_type&&>(v1);
    // Assuring that `move_copy_conting_class` in v1 was moved at least once and was not copied
    BOOST_CHECK(move_copy_conting_class::moves_count != 0);
    BOOST_CHECK(move_copy_conting_class::copy_count == 0);
    total_count = move_copy_conting_class::moves_count + move_copy_conting_class::copy_count;
    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    v1 = v2;
    // Assuring that move assignment operator moves/copyes value not more times than copy assignment operator
    BOOST_CHECK(total_count <= move_copy_conting_class::moves_count + move_copy_conting_class::copy_count);


    typedef boost::variant<move_copy_conting_class, int> variant_II_type;
    variant_II_type v3;
    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    v1 = static_cast<variant_II_type&&>(v3);
    // Assuring that `move_copy_conting_class` in v3 was moved at least once (v1 and v3 have different types)
    BOOST_CHECK(move_copy_conting_class::moves_count != 0);

    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    v2 = static_cast<variant_I_type&&>(v1);
    // Assuring that `move_copy_conting_class` in v1 was moved at least once (v1 and v3 have different types)
    BOOST_CHECK(move_copy_conting_class::moves_count != 0);

    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    variant_I_type v5(static_cast<variant_I_type&&>(v1));
    // Assuring that `move_copy_conting_class` in v1 was moved at least once and was not copied
    BOOST_CHECK(move_copy_conting_class::moves_count != 0);
    BOOST_CHECK(move_copy_conting_class::copy_count == 0);

    total_count = move_copy_conting_class::moves_count + move_copy_conting_class::copy_count;
    move_copy_conting_class::moves_count = 0;
    move_copy_conting_class::copy_count = 0;
    variant_I_type v6(v1);
    // Assuring that move constructor moves/copyes value not more times than copy constructor
    BOOST_CHECK(total_count <= move_copy_conting_class::moves_count + move_copy_conting_class::copy_count);
}


#endif


int test_main(int , char* [])
{
   run();
   return 0;
}