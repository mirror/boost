// -*- C++ -*-
//  Boost general library 'format'   ---------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2001
//                  krempp@crans.ens-cachan.fr
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// ideas taken from Rüdiger Loos's format class
// and Karl Nelson's ofstream (also took its parsing code as basis for printf parsing)

// ------------------------------------------------------------------------------
// macros_default.hpp : configuration for the format library
//                       provides default values for the stl workaround macros
// ------------------------------------------------------------------------------

#ifndef BOOST_FORMAT_MACROS_DEFAULT_HPP
#define BOOST_FORMAT_MACROS_DEFAULT_HPP

// *** This should go to "boost/config/suffix.hpp".

// make sure our local macros wont override something :
#if defined(BOOST_NO_LOCALE_ISDIGIT) || defined(BOOST_OVERLOAD_FOR_NON_CONST) \
  || defined(BOOST_IO_STD) || defined( BOOST_IO_NEEDS_USING_DECLARATION )
#error "a local macro would overwrite a previously defined macro"
#endif


#ifndef BOOST_IO_STD
#  define BOOST_IO_STD std::
#endif



#if defined(BOOST_NO_STD_LOCALE) || \
 ( BOOST_WORKAROUND(__BORLANDC__, <= 0x564) \
   || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT( 0x570 ) )  )
// some future __BORLANDC__ >0x564  versions might not need this
// 0x570 is Borland's kylix branch
#define BOOST_NO_LOCALE_ISIDIGIT
#endif


#if  BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570) ) || BOOST_WORKAROUND( BOOST_MSVC, BOOST_TESTED_AT(1300))
#define BOOST_NO_OVERLOAD_FOR_NON_CONST
#endif


// **** Workaround for io streams, stlport and msvc.
#ifdef BOOST_IO_NEEDS_USING_DECLARATION
namespace boost {
  using std::char_traits;
  using std::basic_ostream;
  using std::basic_ostringstream;
  namespace io {
    using std::basic_ostream;
    namespace detail {
      using std::basic_ios;
      using std::basic_ostream;
      using std::basic_ostringstream;
    }
  }
}
#endif

// ------------------------------------------------------------------------------

#endif // BOOST_FORMAT_MACROS_DEFAULT_HPP
