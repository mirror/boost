#ifndef BOOST_ARCHIVE_CODECVT_NULL_HPP
#define BOOST_ARCHIVE_CODECVT_NULL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// codecvt_null.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <locale>

#include <boost/config.hpp>

#include <boost/detail/workaround.hpp>
#if BOOST_WORKAROUND(__BORLANDC__, <= 0x564)
    #ifndef _RWSTD_NO_NAMESPACE
    using std::codecvt;
    using std::min;
    #ifdef _RWSTD_NO_MBSTATE_T
    using std::mbstate_t;
    #endif
    #endif
#elif defined(__COMO__) || defined(_MSC_VER) && _MSC_VER <= 1300  || defined(__BORLANDC__)
    typedef ::mbstate_t mbstate_t;
#elif defined(BOOST_NO_STDC_NAMESPACE)
    typedef std::mbstate_t mbstate_t;
    namespace std{ 
        using ::codecvt; 
    } // namespace std
#endif

namespace boost { 
namespace archive {

template<class Ch>
class codecvt_null;

template<>
class codecvt_null<char> : public std::codecvt<char, char, mbstate_t> 
{
    // mbstate_t not available in global namespace
    virtual bool do_always_noconv() const throw() {
        return true;    
    }
public:
    explicit codecvt_null(size_t no_locale_manage = 0) :
        std::codecvt<char, char, mbstate_t>(no_locale_manage)
    {}
};

template<>
class codecvt_null<wchar_t> : public std::codecvt<wchar_t, char, mbstate_t>    
{
    virtual std::codecvt_base::result 
    do_out(
        mbstate_t & state,
        const wchar_t * first1, 
        const wchar_t * last1,
        const wchar_t * & next1,
        char * first2, 
        char * last2, 
        char * & next2
    ) const;
    virtual std::codecvt_base::result  
    do_in(
        mbstate_t & state,
        const char * first1, 
        const char * last1, 
        const char * & next1,
        wchar_t * first2,
        wchar_t * last2,
        wchar_t * & next2
    ) const;
    virtual int do_encoding( ) const throw( ){
        return sizeof(wchar_t) / sizeof(char);
    }
    virtual int do_max_length( ) const throw( ){
        return do_encoding();
    }
};

} // namespace archive
} // namespace boost

#endif //BOOST_ARCHIVE_CODECVT_NULL_HPP
