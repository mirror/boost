// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2009 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** 
\file
    
\brief test_output.cpp

\detailed
Test unit and quantity printing

**/

#include <boost/units/quantity.hpp>
#include <boost/units/io.hpp>
#include <boost/units/unit.hpp>
#include <boost/units/scale.hpp>
#include <boost/units/scaled_base_unit.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/make_system.hpp>
#include <boost/units/absolute.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/time.hpp>
#include <boost/units/physical_dimensions/velocity.hpp>
#include <boost/units/physical_dimensions/volume.hpp>
#include <boost/units/physical_dimensions/acceleration.hpp>
#include <boost/units/physical_dimensions/area.hpp>

#include <sstream>
#include <boost/config.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

struct meter_base_unit : boost::units::base_unit<meter_base_unit, boost::units::length_dimension, 1> {
    static const char* name() { return("meter"); }
    static const char* symbol() { return("m"); }
};

struct second_base_unit : boost::units::base_unit<meter_base_unit, boost::units::time_dimension, 2> {
    static const char* name() { return("second"); }
    static const char* symbol() { return("s"); }
};

typedef boost::units::make_system<meter_base_unit, second_base_unit>::type my_system;

typedef boost::units::unit<boost::units::length_dimension, my_system> length;
typedef boost::units::unit<boost::units::velocity_dimension, my_system> velocity;

typedef boost::units::make_scaled_unit<length, boost::units::scale<10, boost::units::static_rational<3> > >::type scaled_length;
typedef boost::units::make_scaled_unit<velocity, boost::units::scale<10, boost::units::static_rational<3> > >::type scaled_velocity1;

typedef boost::units::scaled_base_unit<second_base_unit, boost::units::scale<10, boost::units::static_rational<-3> > > millisecond_base_unit;

typedef boost::units::make_system<meter_base_unit, millisecond_base_unit>::type scaled_system;

typedef boost::units::unit<boost::units::time_dimension, scaled_system> scaled_time;
typedef boost::units::unit<boost::units::velocity_dimension, scaled_system> scaled_velocity2;

typedef boost::units::unit<boost::units::area_dimension, my_system> area;
typedef boost::units::make_scaled_unit<area, boost::units::scale<10, boost::units::static_rational<3> > >::type scaled_area;

typedef boost::units::make_scaled_unit<scaled_length, boost::units::scale<2, boost::units::static_rational<10> > >::type double_scaled_length;

typedef boost::units::scaled_base_unit<meter_base_unit, boost::units::scale<100, boost::units::static_rational<1> > > scaled_length_base_unit;
namespace boost {
namespace units {
template<>
struct base_unit_info<scaled_length_base_unit> {
    static const char* symbol() { return("scm"); }
    static const char* name() { return("scaled_meter"); }
};
}
}
typedef boost::units::scaled_base_unit<scaled_length_base_unit, boost::units::scale<10, boost::units::static_rational<3> > > double_scaled_length_base_unit;
typedef double_scaled_length_base_unit::unit_type double_scaled_length2;

typedef boost::units::reduce_unit<boost::units::unit<boost::units::volume_dimension, my_system> >::type custom1;

std::string name_string(const custom1&) { return("custom1"); }
std::string symbol_string(const custom1&) { return("c1"); }

typedef boost::units::reduce_unit<boost::units::unit<boost::units::acceleration_dimension, my_system> >::type custom2;

const char* name_string(const custom2&) { return("custom2"); }
const char* symbol_string(const custom2&) { return("c2"); }

typedef boost::units::make_scaled_unit<custom1, boost::units::scale<10, boost::units::static_rational<3> > >::type scaled_custom1;
typedef boost::units::make_scaled_unit<custom2, boost::units::scale<10, boost::units::static_rational<3> > >::type scaled_custom2;

#ifndef BOOST_NO_CWCHAR

#define BOOST_UNITS_TEST_OUTPUT(v, expected)                \
{                                                           \
    std::ostringstream ss;                                  \
    ss FORMATTERS << v;                                     \
    BOOST_CHECK_EQUAL(ss.str(), expected);                  \
}                                                           \
{                                                           \
    std::wostringstream ss;                                 \
    ss FORMATTERS << v;                                     \
    BOOST_CHECK(ss.str() == BOOST_PP_CAT(L, expected));     \
}

#else

#define BOOST_UNITS_TEST_OUTPUT(v, expected)                \
{                                                           \
    std::ostringstream ss;                                  \
    ss FORMATTERS << v;                                     \
    BOOST_CHECK_EQUAL(ss.str(), expected);                  \
}

#endif

BOOST_AUTO_TEST_CASE(test_output_unit_symbol) {
#define FORMATTERS
    BOOST_UNITS_TEST_OUTPUT(meter_base_unit::unit_type(), "m");
    BOOST_UNITS_TEST_OUTPUT(velocity(), "m s^-1");
    BOOST_UNITS_TEST_OUTPUT(scaled_length(), "km");
    BOOST_UNITS_TEST_OUTPUT(scaled_velocity1(), "k(m s^-1)");
    BOOST_UNITS_TEST_OUTPUT(millisecond_base_unit::unit_type(), "ms");
    BOOST_UNITS_TEST_OUTPUT(scaled_time(), "ms");
    BOOST_UNITS_TEST_OUTPUT(scaled_velocity2(), "m ms^-1");
    BOOST_UNITS_TEST_OUTPUT(area(), "m^2");
    BOOST_UNITS_TEST_OUTPUT(scaled_area(), "k(m^2)");
    BOOST_UNITS_TEST_OUTPUT(double_scaled_length(), "Kikm");
    BOOST_UNITS_TEST_OUTPUT(double_scaled_length2(), "kscm");
    BOOST_UNITS_TEST_OUTPUT(custom1(), "c1");
    BOOST_UNITS_TEST_OUTPUT(custom2(), "c2");
    BOOST_UNITS_TEST_OUTPUT(scaled_custom1(), "kc1");
    BOOST_UNITS_TEST_OUTPUT(scaled_custom2(), "kc2");
    BOOST_UNITS_TEST_OUTPUT(boost::units::absolute<meter_base_unit::unit_type>(), "absolute m");
#undef FORMATTERS
}

BOOST_AUTO_TEST_CASE(test_output_unit_raw) {
#define FORMATTERS << boost::units::raw_format
    BOOST_UNITS_TEST_OUTPUT(meter_base_unit::unit_type(), "m");
    BOOST_UNITS_TEST_OUTPUT(velocity(), "m s^-1");
    BOOST_UNITS_TEST_OUTPUT(scaled_length(), "km");
    BOOST_UNITS_TEST_OUTPUT(scaled_velocity1(), "k(m s^-1)");
    BOOST_UNITS_TEST_OUTPUT(millisecond_base_unit::unit_type(), "ms");
    BOOST_UNITS_TEST_OUTPUT(scaled_time(), "ms");
    BOOST_UNITS_TEST_OUTPUT(scaled_velocity2(), "m ms^-1");
    BOOST_UNITS_TEST_OUTPUT(area(), "m^2");
    BOOST_UNITS_TEST_OUTPUT(scaled_area(), "k(m^2)");
    BOOST_UNITS_TEST_OUTPUT(double_scaled_length(), "Kikm");
    BOOST_UNITS_TEST_OUTPUT(double_scaled_length2(), "kscm");
    // when using raw format, we ignore the user defined overloads
    BOOST_UNITS_TEST_OUTPUT(custom1(), "m^3");
    BOOST_UNITS_TEST_OUTPUT(custom2(), "m s^-2");
    BOOST_UNITS_TEST_OUTPUT(scaled_custom1(), "k(m^3)");
    BOOST_UNITS_TEST_OUTPUT(scaled_custom2(), "k(m s^-2)");
    BOOST_UNITS_TEST_OUTPUT(boost::units::absolute<meter_base_unit::unit_type>(), "absolute m");
#undef FORMATTERS
}

BOOST_AUTO_TEST_CASE(test_output_unit_name) {
#define FORMATTERS << boost::units::name_format
    BOOST_UNITS_TEST_OUTPUT(meter_base_unit::unit_type(), "meter");
    BOOST_UNITS_TEST_OUTPUT(velocity(), "meter second^-1");
    BOOST_UNITS_TEST_OUTPUT(scaled_length(), "kilometer");
    BOOST_UNITS_TEST_OUTPUT(scaled_velocity1(), "kilo(meter second^-1)");
    BOOST_UNITS_TEST_OUTPUT(millisecond_base_unit::unit_type(), "millisecond");
    BOOST_UNITS_TEST_OUTPUT(scaled_time(), "millisecond");
    BOOST_UNITS_TEST_OUTPUT(scaled_velocity2(), "meter millisecond^-1");
    BOOST_UNITS_TEST_OUTPUT(area(), "meter^2");
    BOOST_UNITS_TEST_OUTPUT(scaled_area(), "kilo(meter^2)");
    BOOST_UNITS_TEST_OUTPUT(double_scaled_length(), "kibikilometer");
    BOOST_UNITS_TEST_OUTPUT(double_scaled_length2(), "kiloscaled_meter");
    BOOST_UNITS_TEST_OUTPUT(custom1(), "custom1");
    BOOST_UNITS_TEST_OUTPUT(custom2(), "custom2");
    BOOST_UNITS_TEST_OUTPUT(scaled_custom1(), "kilocustom1");
    BOOST_UNITS_TEST_OUTPUT(scaled_custom2(), "kilocustom2");
    BOOST_UNITS_TEST_OUTPUT(boost::units::absolute<meter_base_unit::unit_type>(), "absolute meter");
#undef FORMATTERS
}


BOOST_AUTO_TEST_CASE(test_output_quantity_symbol) {
#define FORMATTERS
    BOOST_UNITS_TEST_OUTPUT(1.5*meter_base_unit::unit_type(), "1.5 m");
    BOOST_UNITS_TEST_OUTPUT(1.5*velocity(), "1.5 m s^-1");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_length(), "1.5 km");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_velocity1(), "1.5 k(m s^-1)");
    BOOST_UNITS_TEST_OUTPUT(1.5*millisecond_base_unit::unit_type(), "1.5 ms");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_time(), "1.5 ms");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_velocity2(), "1.5 m ms^-1");
    BOOST_UNITS_TEST_OUTPUT(1.5*area(), "1.5 m^2");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_area(), "1.5 k(m^2)");
    BOOST_UNITS_TEST_OUTPUT(1.5*double_scaled_length(), "1.5 Kikm");
    BOOST_UNITS_TEST_OUTPUT(1.5*double_scaled_length2(), "1.5 kscm");
    BOOST_UNITS_TEST_OUTPUT(1.5*custom1(), "1.5 c1");
    BOOST_UNITS_TEST_OUTPUT(1.5*custom2(), "1.5 c2");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_custom1(), "1.5 kc1");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_custom2(), "1.5 kc2");
    BOOST_UNITS_TEST_OUTPUT(1.5*boost::units::absolute<meter_base_unit::unit_type>(), "1.5 absolute m");
#undef FORMATTERS
}

BOOST_AUTO_TEST_CASE(test_output_quantity_raw) {
#define FORMATTERS << boost::units::raw_format
    BOOST_UNITS_TEST_OUTPUT(1.5*meter_base_unit::unit_type(), "1.5 m");
    BOOST_UNITS_TEST_OUTPUT(1.5*velocity(), "1.5 m s^-1");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_length(), "1.5 km");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_velocity1(), "1.5 k(m s^-1)");
    BOOST_UNITS_TEST_OUTPUT(1.5*millisecond_base_unit::unit_type(), "1.5 ms");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_time(), "1.5 ms");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_velocity2(), "1.5 m ms^-1");
    BOOST_UNITS_TEST_OUTPUT(1.5*area(), "1.5 m^2");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_area(), "1.5 k(m^2)");
    BOOST_UNITS_TEST_OUTPUT(1.5*double_scaled_length(), "1.5 Kikm");
    BOOST_UNITS_TEST_OUTPUT(1.5*double_scaled_length2(), "1.5 kscm");
    // when using raw format, we ignore the user defined overloads
    BOOST_UNITS_TEST_OUTPUT(1.5*custom1(), "1.5 m^3");
    BOOST_UNITS_TEST_OUTPUT(1.5*custom2(), "1.5 m s^-2");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_custom1(), "1.5 k(m^3)");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_custom2(), "1.5 k(m s^-2)");
    BOOST_UNITS_TEST_OUTPUT(1.5*boost::units::absolute<meter_base_unit::unit_type>(), "1.5 absolute m");
#undef FORMATTERS
}

BOOST_AUTO_TEST_CASE(test_output_quantity_name) {
#define FORMATTERS << boost::units::name_format
    BOOST_UNITS_TEST_OUTPUT(1.5*meter_base_unit::unit_type(), "1.5 meter");
    BOOST_UNITS_TEST_OUTPUT(1.5*velocity(), "1.5 meter second^-1");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_length(), "1.5 kilometer");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_velocity1(), "1.5 kilo(meter second^-1)");
    BOOST_UNITS_TEST_OUTPUT(1.5*millisecond_base_unit::unit_type(), "1.5 millisecond");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_time(), "1.5 millisecond");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_velocity2(), "1.5 meter millisecond^-1");
    BOOST_UNITS_TEST_OUTPUT(1.5*area(), "1.5 meter^2");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_area(), "1.5 kilo(meter^2)");
    BOOST_UNITS_TEST_OUTPUT(1.5*double_scaled_length(), "1.5 kibikilometer");
    BOOST_UNITS_TEST_OUTPUT(1.5*double_scaled_length2(), "1.5 kiloscaled_meter");
    BOOST_UNITS_TEST_OUTPUT(1.5*custom1(), "1.5 custom1");
    BOOST_UNITS_TEST_OUTPUT(1.5*custom2(), "1.5 custom2");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_custom1(), "1.5 kilocustom1");
    BOOST_UNITS_TEST_OUTPUT(1.5*scaled_custom2(), "1.5 kilocustom2");
    BOOST_UNITS_TEST_OUTPUT(1.5*boost::units::absolute<meter_base_unit::unit_type>(), "1.5 absolute meter");
#undef FORMATTERS
}

