// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the template codecvt_helper, useful for
// defining specializations of std::codecvt where state_type != mbstate_t.
// Compensates for the fact that some standard library implementations 
// do not derive the primiary codecvt template from locale::facet or 
// provide the correct member types and functions.

// Usage: 
//
// // In global namespace:
// BOOST_IOSTREAMS_CODECVT_SPEC(mystate)
//
// // In user namespace:
// template<typename Intern, typename Extern>
// struct mycodecvt : codecvt_helper<Intern, Extern, State> { ... };
//
// // Or:
// struct mycodecvt : codecvt_helper<wchar_t, char, State> { ... };
// 
// Etc.

#ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HELPER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CODECVT_HELPER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>  // Make sure size_t is in std.
#include <boost/detail/workaround.hpp>
#include <algorithm>         // min.
#include <cstddef>           // size_t.
#include <locale>            // locale, codecvt_base, codecvt.
#include <boost/iostreams/detail/config/locale.hpp>

//------------------Definition of codecvt_impl---------------------------------//

#if defined(BOOST_NO_PRIMARY_CODECVT_DEFINITION) || \
    defined(BOOST_EMPTY_PRIMARY_CODECVT_DEFINITION) || \
    defined(BOOST_NO_STD_LOCALE) \
    /**/

namespace boost { namespace iostreams { namespace detail {

template<typename Intern, typename Extern, typename State>
struct codecvt_impl : std::locale::facet, std::codecvt_base {
public:
    typedef Intern  intern_type;
    typedef Extern  extern_type;
    typedef State   state_type;

    codecvt_impl(std::size_t refs = 0) : std::locale::facet(refs) { } 

    std::codecvt_base::result
    in( State& state, const Extern* first1, const Extern* last1,
        const Extern*& next1, Intern* first2, Intern* last2,
        Intern*& next2 ) const
    {
        return do_in(state, first1, last1, next1, first2, last2, next2);
    }

    std::codecvt_base::result
    out( State& state, const Intern* first1, const Intern* last1,
         const Intern*& next1, Extern* first2, Extern* last2,
         Extern*& next2 ) const
    {
        return do_out(state, first1, last1, next1, first2, last2, next2);
    }

    std::codecvt_base::result
    unshift(State& state, Extern* first2, Extern* last2, Extern*& next2) const
    {
        return do_unshift(state, first2, last2, next2);
    }

    bool always_noconv() const throw() { return do_always_noconv(); }

    int max_length() const throw() { return do_max_length(); }

    int encoding() const throw() { return do_encoding(); }

    int length( BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER State& state, 
                const Extern* first1, const Extern* last1,
                std::size_t len2 ) const throw()
    {
        return do_length(state, first1, last1, len2);
    }
protected:
    std::codecvt_base::result
    virtual do_in( State&, const Extern*, const Extern*, const Extern*&, 
                   Intern*, Intern*, Intern*& ) const
    {
        return std::codecvt_base::noconv;
    }

    std::codecvt_base::result
    virtual do_out( State&, const Intern*, const Intern*, const Intern*&, 
                    Extern*, Extern*, Extern*& ) const
    {
        return std::codecvt_base::noconv;
    }

    std::codecvt_base::result
    virtual do_unshift( State& state, Extern* first2, Extern* last2, 
                        Extern*& next2 ) const
    {
        return std::codecvt_base::ok;
    }

    virtual bool do_always_noconv() const throw() { return true; }

    virtual int do_max_length() const throw() { return 1; }

    virtual int do_encoding() const throw() { return 1; }

    virtual int do_length( BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER State& state, 
                           const Extern* first1, const Extern* last1,
                           std::size_t len2 ) const throw()
    {
        return std::min(static_cast<std::size_t>(last1 - first1), len2);
    }
};

} } } // End namespaces detail, iostreams, boost.

#endif // no primary codecvt definition, or empty definition.

//------------------Definition of BOOST_IOSTREAMS_CODECVT_SPEC----------------//

#if defined(BOOST_NO_PRIMARY_CODECVT_DEFINITION) || \
    defined(BOOST_EMPTY_PRIMARY_CODECVT_DEFINITION) \
    /**/
# define BOOST_IOSTREAMS_CODECVT_SPEC(state) \
    namespace std { \
        template<typename Intern, typename Extern> \
        struct codecvt<Intern, Extern, state> \
            : ::boost::iostreams::detail::codecvt_impl<Intern, Extern, state> \
        { \
            static std::locale::id id; \
        }; \
        template<typename Intern, typename Extern> \
        std::locale::id codecvt<Intern, Extern, state>::id; \
    } \
    /**/
#else
# define BOOST_IOSTREAMS_CODECVT_SPEC(state)
#endif // no primary codecvt definition, or empty definition.

namespace boost { namespace iostreams { namespace detail {
                    
//------------------Definition of codecvt_helper------------------------------//

template<typename Intern, typename Extern, typename State>
struct codecvt_helper : std::codecvt<Intern, Extern, State> { 
    typedef Intern  intern_type;
    typedef Extern  extern_type;
    typedef State   state_type;
    codecvt_helper(std::size_t refs = 0) 
    #if !BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
        : std::codecvt<Intern, Extern, State>(refs)
    #else
        : std::codecvt<Intern, Extern, State>()
    #endif
        { }
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HELPER_HPP_INCLUDED
