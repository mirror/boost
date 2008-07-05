#ifndef  BOOST_SERIALIZATION_VECTOR_134_HPP
#define BOOST_SERIALIZATION_VECTOR_134_HPP

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector_134.hpp: backwards compatibility with 1.34.1 files

// (C) Copyright 2008 Matthias Troyer 


#ifdef BOOST_SERIALIZATION_VECTOR_VERSION
#if BOOST_SERIALIZATION_VECTOR_VERSION != 4
#error Boost.Serialization cannot be compatible with both 1.34.1. and 1.35 files. Please include boost/serialization/vector_134.hpp before vector.hpp to be compatible with 1.34.1 files
#endif
#else
#define BOOST_SERIALIZATION_VECTOR_VERSION 4
#endif

#include <boost/serialization/vector.hpp>

#endif // BOOST_SERIALIZATION_VECTOR_134_HPP
