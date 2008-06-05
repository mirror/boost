// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2007-2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

template<class T>
struct print {
    enum { value = false };
};

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/units/base_unit.hpp>
#include <boost/units/derived_dimension.hpp>
#include <boost/units/make_system.hpp>
#include <boost/units/operators.hpp>
#include <boost/units/reduce_unit.hpp>
#include <boost/units/unit.hpp>

#include <boost/units/physical_dimensions/current.hpp>
#include <boost/units/physical_dimensions/electric_potential.hpp>
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/physical_dimensions/force.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/time.hpp>

// the base units in the system will be:
//
// volts  = kg m^2 s^-2 C^-1
// newtons = kg m s^-2
// joules = kg m^2 s^-2

// we will find the representation of m^-1 C^-1 = V N J^-2 = m^-1 C^-1 

struct volt : boost::units::base_unit<volt, boost::units::electric_potential_dimension, 1> {};
struct newton : boost::units::base_unit<newton, boost::units::force_dimension, 2> {};
struct joule : boost::units::base_unit<joule, boost::units::energy_dimension, 3> {};

typedef boost::units::make_system<volt, newton, joule>::type complicated_system;

typedef boost::units::derived_dimension<
    boost::units::length_base_dimension, -1,
    boost::units::time_base_dimension, -1,
    boost::units::current_base_dimension, -1
>::type dimension;

typedef boost::units::reduce_unit<boost::units::unit<dimension, complicated_system> >::type reduced;

typedef boost::units::divide_typeof_helper<
    boost::units::multiply_typeof_helper<volt::unit_type, newton::unit_type>::type,
    boost::units::power_typeof_helper<joule::unit_type, boost::units::static_rational<2> >::type
>::type expected;

int main() {
    BOOST_MPL_ASSERT((boost::is_same<reduced, expected>));
}
