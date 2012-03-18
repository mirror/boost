
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestWorldThis
#include <boost/test/unit_test.hpp>
#include <boost/config.hpp>
#include <vector>

struct person {};
BOOST_TYPEOF_REGISTER_TYPE(person)

struct world {
    void add_person(person const& a_person);
    size_t population(void) const { return persons_.size(); }

private:
    std::vector<person> persons_;
};
BOOST_TYPEOF_REGISTER_TYPE(world)

void world::add_person(person const& a_person) {
    bool commit = false;

    persons_.push_back(a_person);
    //[world_this_
    BOOST_SCOPE_EXIT(&commit, this_) { // Capture object `this_`.
        if(!commit) this_->persons_.pop_back();
    } BOOST_SCOPE_EXIT_END
    //]

    // ...

    commit = true;
}

BOOST_AUTO_TEST_CASE(test_world_this) {
    world w;
    person p;
    w.add_person(p);
    BOOST_CHECK(w.population() == 1);
}

#else

int main(void) { return 0; } // Trivial test.

#endif

