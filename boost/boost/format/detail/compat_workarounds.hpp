// ------------------------------------------------------------------------------
//  compat_workarounds : general framework for the non-conforming compiler workarounds.
// ------------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ------------------------------------------------------------------------------




//  this file defines 
//    wrapper classes to hide non-conforming std::char_traits<> and std::allocator<> traits
//  and Includes :
//     config_macros.hpp (defines config macros and compiler-specific switches)

// Non-conformant Std-libs fail to supply conformant traits (std::char_traits, std::allocator)
//  and/or  the std::string doesnt support them.
// We don't want to have hundreds of #ifdef workarounds, so we define replacement traits.
// But both char_traits and allocator traits are visible in the interface, 
// (inside the final string type),  thus we need to keep both 
// the replacement type (typedefed to 'compatible_type') for real use,
// and the original stdlib type (typedef to 'type_for_string') for interface visibility.
// This is what Compat* classes do (as well as be transparent when good allocator and char traits are present)

#ifndef BOOST_FORMAT_COMPAT_WORKAROUNDS_HPP
#define BOOST_FORMAT_COMPAT_WORKAROUNDS_HPP

namespace boost {
    namespace io {

        // gcc-2.95 char traits (non-conformantly named string_char_traits) lack several functions
        // so we extend them in a replacement class.
        template<class Tr>
        class CompatTraits; 

        // std::allocator<Ch> in gcc-2.95 is ok, but basic_string only works with plain 'std::alloc'
        // still, alt_stringbuf requires a functionnal alloc template argument, so we
        // need a replacement allocator
        template<class Alloc>
        class CompatAlloc; 
   
        template<class OStream>
        class CompatOStream;
    } // N.S. io
}// N.S. boost


#include <boost/format/detail/config_macros.hpp>
   // sets-up macros and load compiler-specific workarounds headers.

#if !defined( BOOST_FORMAT_STREAMBUF_DEFINED)
#include <streambuf>
#endif

namespace boost {
    namespace io {

        // **** CompatTraits general definitions : ---------------------------------
        template<class Tr>
        class CompatTraits<CompatTraits<Tr> >
        {        // handle imbricated CompatTraits< .. > :
        public:
            typedef typename CompatTraits<Tr>::type_for_string    type_for_string;
            typedef typename CompatTraits<Tr>::compatible_type compatible_type;
        };
        template<class Tr>
        class CompatTraits
        {        // general case : be transparent
        public:
            typedef Tr  type_for_string;
            typedef Tr  compatible_type;
        };

        // **** CompatAlloc general definitions : ---------------------------------
        template<class Alloc>
        class CompatAlloc<CompatAlloc<Alloc> >
        {        // handle imbricated CompatAlloc< .. > :
        public:
            typedef typename CompatAlloc<Alloc>::type_for_string    type_for_string;
            typedef typename CompatAlloc<Alloc>::compatible_type compatible_type;
        };
        template<class Alloc>
        class CompatAlloc
        {        // general case : be transparent
        public:
            typedef Alloc  type_for_string;
            typedef Alloc  compatible_type;
        };


        // **** CompatOStream general definitions : ---------------------------------
        template<class OStream>
        class CompatOStream<CompatOStream<OStream> >
        {        // handle imbricated CompatOStream< .. > :
        public:
            typedef typename CompatOStream<OStream>::type_for_string    type_for_string;
            typedef typename CompatOStream<OStream>::compatible_type compatible_type;
        };
        template<class OStream>
        class CompatOStream
        {        // general case : be transparent
        public:
            typedef OStream  type_for_string;
            typedef OStream  compatible_type;
        };

    } //N.S. io
} // N.S. boost
#endif // include guard
