#ifndef BOOST_ARCHIVE_ARRAY_IARCHIVE_HPP
#define BOOST_ARCHIVE_ARRAY_IARCHIVE_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/array.hpp>
#include <boost/pfto.hpp>

namespace boost { namespace archive { namespace array {

  // To conveniently array-optimize an input archive X:
  //
  //   * Derive it from iarchive<X, Impl>, where Impl is an 
  //     archive implementation base class from 
  //     Boost.Serialization
  //
  //   * add a member function template that implements the
  //     procedure for serializing arrays of T (for appropriate T)
  //
  //       template <class T>
  //       load_array(serialization::array<T> &, unsigned int)
  //
  //   * add a unary MPL lambda expression member called
  //     use_array_optimization whose result is convertible to
  //     mpl::true_ iff array elements of type T can be serialized
  //     with the load_array member function, and to mpl::false_ if
  //     the unoptimized procedure must be used. 
  //
  //  *  declare your archive to make use of array optimization
  //     by setting the appropriate trait with the 
  //     BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION macro


template <class Archive>
class iarchive
 : public archive::detail::common_iarchive<Archive>
{
  typedef archive::detail::common_iarchive<Archive> Base;
public:
  iarchive(unsigned int flags)
   : archive::detail::common_iarchive<Archive>(flags)
  {}


  // load_override for std::vector and serialization::array dispatches to 
  // load_optimized with an additional argument.
  // 
  // If that argument is of type mpl::true_, an optimized serialization is provided
  // If it is false, we just forward to the default serialization in the base class
  
  //the default version dispatches to the base class
  template<class T>
  void load_optimized(T &t, unsigned int version, mpl::false_)
  {
    Base::load_override(t, version);
  }

  // the optimized implementation for serialization::array uses save_array
  template<class ValueType>
  void load_optimized(
    serialization::array<ValueType> &t, unsigned int version, mpl::true_)
  {
    this->This()->load_array(t,version);
  }

  // dispatch loading of arrays to the optimized version where supported
  template<class ValueType>
  void load_override(serialization::array<ValueType> const& x, unsigned int version)
  {
    typedef BOOST_DEDUCED_TYPENAME serialization
                              ::use_array_optimization<Archive>
	                      ::template apply<ValueType>::type use_optimized;
    load_optimized(const_cast<serialization::array<ValueType>&>(x),version,use_optimized());
  }

  // Load everything else in the usual way, forwarding on to the base class
  template<class T>
  void load_override(T & x, unsigned BOOST_PFTO int version)
  {
    Base::load_override(x, static_cast<unsigned int>(version));
  }
};

} } } // end namespace boost::archive::array

#endif // BOOST_ARCHIVE_ARRAY_OARCHIVE_HPP

