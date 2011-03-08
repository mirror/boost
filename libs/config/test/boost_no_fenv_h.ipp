//  (C) Copyright John Maddock 2001.
//  (C) Copyright Bryce Lelbach 2010. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for most recent version.

//  MACRO:         BOOST_NO_FENV_H
//  TITLE:         fenv.h
//  DESCRIPTION:   There is no standard <fenv.h> available. If <fenv.h> is
//                 available, <boost/detail/fenv.hpp> should be included
//                 instead of directly including <fenv.h>.

#include <boost/detail/fenv.hpp>

namespace boost_no_fenv_h {

int test()
{
  /// C++0x required typedefs
  typedef ::fenv_t has_fenv_t;
  typedef ::fexcept_t has_fexcept_t;

  /// C++0x required macros
  #if !defined(FE_DIVBYZERO)
    #error platform does not define FE_DIVBYZERO
  #endif
  
  #if !defined(FE_INEXACT)
    #error platform does not define FE_INEXACT
  #endif

  #if !defined(FE_ALL_EXCEPT)
    #error platform does not define FE_ALL_EXCEPT
  #endif
  
   int (*has_feclearexcept)(int ) = ::feclearexcept;
   int (*has_fegetexceptflag)(fexcept_t *, int ) = fegetexceptflag;
   int (*has_feraiseexcept)(int ) = feraiseexcept;
   int (*has_fesetexceptflag)(const fexcept_t *, int ) = fesetexceptflag;
   int (*has_fetestexcept)(int ) = fetestexcept;
   int (*has_fegetround)(void) = fegetround;
   int (*has_fesetround)(int ) = fesetround;
   int (*has_fegetenv)(fenv_t *) = fegetenv;
   int (*has_feholdexcept)(fenv_t *) = feholdexcept;
   int (*has_fesetenv)(const fenv_t *) = fesetenv;
   int (*has_feupdateenv)(const fenv_t *) = feupdateenv;

   return 0;
}

}

