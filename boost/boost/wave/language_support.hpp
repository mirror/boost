/*=============================================================================
    Wave: A Standard compliant C++ preprocessor library
    Definition of the various language support constants
    
    http://spirit.sourceforge.net/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(LANGUAGE_SUPPORT_HPP_93EDD057_2DEF_44BC_BC9F_FDABB9F51AFA_INCLUDED)
#define LANGUAGE_SUPPORT_HPP_93EDD057_2DEF_44BC_BC9F_FDABB9F51AFA_INCLUDED

#include <boost/wave/wave_config.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {

enum language_support {
//  support flags for C++98
    support_normal = 0x01,
    support_cpp = support_normal,
    
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
//  support flags for C99
    support_variadics = 0x02,
    support_c99 = support_variadics,
#endif 
};

///////////////////////////////////////////////////////////////////////////////
//  
//  need_cpp
//
//      Extract, if the language to support is C++98
//
///////////////////////////////////////////////////////////////////////////////
inline bool
need_cpp(language_support language) 
{
    return language == support_cpp;
}

#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0

///////////////////////////////////////////////////////////////////////////////
//  
//  need_variadics
//
//      Extract, if the language to support needs variadics support
//
///////////////////////////////////////////////////////////////////////////////
inline bool 
need_variadics(language_support language) 
{
    return (language & support_variadics) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//  
//  enable_variadics
//
//      Set variadics support in the language to support
//
///////////////////////////////////////////////////////////////////////////////
inline language_support
enable_variadics(language_support language, bool enable = true)
{
    if (enable)
        return static_cast<language_support>(language | support_variadics);
    return static_cast<language_support>(language & ~support_variadics);
}

///////////////////////////////////////////////////////////////////////////////
//  
//  need_c99
//
//      Extract, if the language to support is C99
//
///////////////////////////////////////////////////////////////////////////////
inline bool
need_c99(language_support language) 
{
    return language == support_c99;
}

///////////////////////////////////////////////////////////////////////////////
//  
//  enable_c99
//
//      Set, whether to support C99 (alternatively C++98 is supported)
//
///////////////////////////////////////////////////////////////////////////////
inline language_support
enable_c99(bool enable = true)
{
    return enable ? support_c99 : support_cpp;
}

#else  // BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0

///////////////////////////////////////////////////////////////////////////////
inline bool 
need_variadics(language_support language) 
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
inline language_support
enable_variadics(language_support language, bool enable = true)
{
    return language;
}

//////////////////////////////////////////////////////////////////////////////
inline bool
need_c99(language_support language) 
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
inline language_support
enable_c99(bool enable = true)
{
    return support_cpp;
}

#endif // BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0

///////////////////////////////////////////////////////////////////////////////
}   // namespace wave
}   // namespace boost 

#endif // !defined(LANGUAGE_SUPPORT_HPP_93EDD057_2DEF_44BC_BC9F_FDABB9F51AFA_INCLUDED)
