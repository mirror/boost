
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include "scope_exit.hpp"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestScopeExit
#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>
#include <sstream>

class person; BOOST_TYPEOF_REGISTER_TYPE(person)
class person {
    friend class world;
public:
    typedef unsigned int id_t;
    typedef unsigned int evolution_t;

    person(void): id_(0), evolution_(0) {}

    friend std::ostream& operator<<(std::ostream& o, person const& p) {
        return o << "person(" << p.id_ << ", " << p.evolution_ << ")";
    }
private:
    id_t id_;
    evolution_t evolution_;
};

class world; BOOST_TYPEOF_REGISTER_TYPE(world)
class world {
public:
    typedef unsigned int id_t;

    world(void): next_id_(1) {}

    void add_person(person const& a_person);

    friend std::ostream& operator<<(std::ostream& o, world const& w) {
        o << "world(" << w.next_id_ << ", {";
        BOOST_FOREACH(person const& p, w.persons_) {
            o << " " << p << ", ";
        }
        return o << "})";
    }
private:
    id_t next_id_;
    std::vector<person> persons_;
};

void world::add_person(person const& a_person) {
    persons_.push_back(a_person);

    // This block must be no-throw.
    //[scope_exit
    person& p = persons_.back();
    person::evolution_t checkpoint = p.evolution_;

    SCOPE_EXIT(const bind checkpoint, const bind& p, bind this_) {
        if (checkpoint == p.evolution_) this_->persons_.pop_back();
    } SCOPE_EXIT_END
    //]

    // ...

    checkpoint = ++p.evolution_;

    // Assign new id to the person.
    world::id_t const prev_id = p.id_;
    p.id_ = next_id_++;
    SCOPE_EXIT(const bind checkpoint, const bind prev_id, bind& p,
            bind& next_id_) {
        if (checkpoint == p.evolution_) {
            next_id_ = p.id_;
            p.id_ = prev_id;
        }
    } SCOPE_EXIT_END

    // ...

    checkpoint = ++p.evolution_;
}

BOOST_AUTO_TEST_CASE( test_scope_exit ) {
    person adam, eva;
    std::ostringstream oss;
    oss << adam;
    std::cout << oss.str() << std::endl;
    BOOST_CHECK( oss.str() == "person(0, 0)" );

    oss.str("");
    oss << eva;
    std::cout << oss.str() << std::endl;
    BOOST_CHECK( oss.str() == "person(0, 0)" );

    world w;
    w.add_person(adam);
    w.add_person(eva);
    oss.str("");
    oss << w;
    std::cout << oss.str() << std::endl;
    BOOST_CHECK( oss.str() == "world(3, { person(1, 2),  person(2, 2), })" );
}

