//  boost cast.hpp header file  ----------------------------------------------//

//  (C) Copyright boost.org 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  30 Jun 00  More MSVC6 wordarounds.  See comments below.  (Dave Abrahams)
//  28 Jun 00  Removed implicit_cast<>.  See comment below. (Beman Dawes)
//  27 Jun 00  More MSVC6 workarounds 
//  15 Jun 00  Add workarounds for MSVC6
//   2 Feb 00  Remove bad_numeric_cast ";" syntax error (Doncho Angelov)
//  26 Jan 00  Add missing throw() to bad_numeric_cast::what(0 (Adam Levar)
//  29 Dec 99  Change using declarations so usages in other namespaces work
//             correctly (Dave Abrahams)
//  23 Sep 99  Change polymorphic_downcast assert to also detect M.I. errors
//             as suggested Darin Adler and improved by Valentin Bonnard.  
//   2 Sep 99  Remove controversial asserts, simplify, rename.
//  30 Aug 99  Move to cast.hpp, replace value_cast with numeric_cast,
//             place in nested namespace.
//   3 Aug 99  Initial version

#ifndef BOOST_CAST_HPP
#define BOOST_CAST_HPP

# include <boost/config.hpp>
# include <cassert>
# include <typeinfo> 
# include <limits>

//  It has been demonstrated numerous times that MSVC 6.0 fails silently at link
//  time if you use a template function which has template parameters that don't
//  appear in the function's argument list.
//
//  TODO: Add this to config.hpp?
# if defined(BOOST_MSVC) && BOOST_MSVC <= 1200 // 1200 = VC6
#  define BOOST_EXPLICIT_DEFAULT_TARGET , ::boost::detail::type_wrapper<Target>* = 0
#  define BOOST_EXPLICIT_TARGET ,::boost::detail::type_wrapper<Target>*
# else
#  define BOOST_EXPLICIT_DEFAULT_TARGET
#  define BOOST_EXPLICIT_TARGET
# endif

namespace boost
{
  namespace detail {
    template <class T> struct type_wrapper {};
  }
#if !(defined(BOOST_MSVC) && BOOST_MSVC <= 1200) // 1200 = VC6
  namespace cast
  {
#endif

//  See the documentation for descriptions of how to choose between
//  static_cast<>, dynamic_cast<>, polymorphic_cast<>. and down_cast<>

//  polymorphic_cast  --------------------------------------------------------//

    //  Runtime checked polymorphic downcasts and crosscasts.
    //  Suggested in The C++ Programming Language, 3rd Ed, Bjarne Stroustrup, 
    //  section 15.8 exercise 1, page 425.

    template <class Target, class Source>
    inline Target polymorphic_cast(Source* x BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        Target tmp = dynamic_cast<Target>(x);
        if ( tmp == 0 ) throw std::bad_cast();
        return tmp;
    }

//  polymorphic_downcast  ----------------------------------------------------//

    //  assert() checked polymorphic downcast.  Crosscasts prohibited.

    //  WARNING: Because this cast uses assert(), it violates the One Definition
    //  Rule if NDEBUG is inconsistently defined across translation units.

    //  Contributed by Dave Abrahams

    template <class Target, class Source>
    inline Target polymorphic_downcast(Source* x BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        assert( dynamic_cast<Target>(x) == x );  // detect logic error
        return static_cast<Target>(x);
    }

//  implicit_cast  -----------------------------------------------------------//
//
//  Removed due to uncertain purpose.  Use either numeric_cast (see below)
//  or static_cast according to the need. 

//  numeric_cast and related exception  --------------------------------------//

//  Contributed by Kevlin Henney

//  bad_numeric_cast  --------------------------------------------------------//

    // exception used to indicate runtime numeric_cast failure
    class bad_numeric_cast : public std::bad_cast
    {
    public:
        // constructors, destructors and assignment operator defaulted

        // function inlined for brevity and consistency with rest of library
        virtual const char *what() const throw()
        {
            return "bad numeric cast: loss of range in numeric_cast";
        }
    };

//  numeric_cast  ------------------------------------------------------------//

    template<typename Target, typename Source>
    inline Target numeric_cast(Source arg BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        // typedefs abbreviating respective trait classes
        typedef std::numeric_limits<Source> arg_traits;
        typedef std::numeric_limits<Target> result_traits;

        // typedefs that act as compile time assertions
        // (to be replaced by boost compile time assertions
        // as and when they become available and are stable)
        typedef bool argument_must_be_numeric[arg_traits::is_specialized];
        typedef bool result_must_be_numeric[result_traits::is_specialized];

        if( (arg < 0 && !result_traits::is_signed) ||  // loss of negative range
              (arg_traits::is_signed &&
                 arg < result_traits::min()) ||        // underflow
               arg > result_traits::max() )            // overflow
            throw bad_numeric_cast();
        return static_cast<Target>(arg);
    }

//  Visual C++ workarounds  --------------------------------------------------//

#  if !(defined(BOOST_MSVC) && BOOST_MSVC <= 1200) // 1200 = VC6
  } // namespace cast

  using ::boost::cast::polymorphic_cast;
  using ::boost::cast::polymorphic_downcast;
  using ::boost::cast::bad_numeric_cast;
  using ::boost::cast::numeric_cast;
#  else
  namespace cast {
    using ::boost::polymorphic_cast;
    using ::boost::polymorphic_downcast;
    using ::boost::bad_numeric_cast;
    using ::boost::numeric_cast;
  }
#  endif

#  undef BOOST_EXPLICIT_DEFAULT_TARGET
#  undef BOOST_EXPLICIT_TARGET

} // namespace boost

#endif  // BOOST_CAST_HPP

