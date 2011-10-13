//
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_TRANSLATE_HPP
#define BOOST_CHRONO_IO_TRANSLATE_HPP

#include <boost/chrono/config.hpp>
#include <string>

namespace boost
{
  namespace chrono
  {


#if !defined BOOST_CHRONO_SPECIFIC_TRANSLATE
    template <class CharT, class Rep>
    std::basic_string<CharT> duration_prefix_translate(std::basic_string<CharT> const &singular, std::basic_string<CharT> const &plural, Rep v)
    {
      if ( v == 1  ) return singular;
      if ( v == -1  ) return singular;
      return plural;
    }

    template <class CharT>
    std::basic_string<CharT> duration_symbol_translate(std::basic_string<CharT> const &symbol)
    {
      return symbol;
    }

    template <class CharT>
    std::basic_string<CharT> epoch_translate(std::basic_string<CharT> const &epoch)
    {
      return epoch;
    }

#endif



  } // chrono

}

#endif  // BOOST_CHRONO_CHRONO_IO_HPP
