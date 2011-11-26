//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_DURATION_STYLE_HPP
#define BOOST_CHRONO_IO_DURATION_STYLE_HPP
#include <iostream>

namespace boost
{
  namespace chrono
  {
    /**
     * Scoped enumeration emulation stating whether the duration I/O style is long or short.
     * prefix means duration::rep with whatever stream/locale settings are set for it followed by a long name representing the unit
     * symbol means duration::rep with whatever stream/locale settings are set for it followed by a SI unit abbreviation
     */
    struct duration_style
    {
      enum type
      {
        prefix, symbol
      };
    };
    typedef duration_style::type duration_style_type;


  } // chrono

}

#endif  // header
