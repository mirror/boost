
//  (C) Copyright Boost.org 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
// use this header as a workaround for missing <limits>

#ifndef BOOST_LIMITS
#define BOOST_LIMITS

#include <boost/config.hpp>

#ifdef BOOST_NO_LIMITS
# include <boost/detail/limits.hpp>
#else
# include <limits>
#endif

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1200 && !defined(__SGI_STL_PORT) && !defined(_CPPLIB_VER)
// Add missing specializations for MSVC
namespace std
{
  class numeric_limits<__int64> : public _Num_int_base {
   public:
      static __int64 (__cdecl min)() _THROW0()
      {return (_I64_MIN); }
      static __int64 (__cdecl max)() _THROW0()
      {return (_I64_MAX); }
      static __int64 __cdecl epsilon() _THROW0()
      {return 0; }
      static __int64 __cdecl round_error() _THROW0()
      {return 0; }
      static __int64 __cdecl denorm_min() _THROW0()
      {return 0; }
      static __int64 __cdecl infinity() _THROW0()
      {return 0; }
      static __int64 __cdecl quiet_NaN() _THROW0()
      {return 0; }
      static __int64 __cdecl signaling_NaN() _THROW0()
      {return 0; }
    
      _STCONS(bool, is_signed, true);
      _STCONS(int, digits, CHAR_BIT * sizeof (__int64) - 1);
      _STCONS(int, digits10, (CHAR_BIT * sizeof (__int64) - 1)
              * 301L / 1000);
  };

  class numeric_limits<unsigned __int64> : public _Num_int_base {
   public:
      static unsigned __int64 (__cdecl min)() _THROW0()
      {return 0; }
      static unsigned __int64 (__cdecl max)() _THROW0()
      {return (_UI64_MAX); }
      static unsigned __int64 __cdecl epsilon() _THROW0()
      {return 0; }
      static unsigned __int64 __cdecl round_error() _THROW0()
      {return 0; }
      static unsigned __int64 __cdecl denorm_min() _THROW0()
      {return 0; }
      static unsigned __int64 __cdecl infinity() _THROW0()
      {return 0; }
      static unsigned __int64 __cdecl quiet_NaN() _THROW0()
      {return 0; }
      static unsigned __int64 __cdecl signaling_NaN() _THROW0()
      {return 0; }
      _STCONS(bool, is_signed, false);
      _STCONS(int, digits, CHAR_BIT * sizeof (unsigned __int64));
      _STCONS(int, digits10, (CHAR_BIT * sizeof (unsigned __int64))
              * 301L / 1000);
  };
}
#endif 

#endif
