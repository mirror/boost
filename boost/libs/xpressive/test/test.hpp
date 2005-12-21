///////////////////////////////////////////////////////////////////////////////
// test.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_TEST_REGRESS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_TEST_REGRESS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <string>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <boost/range/iterator_range.hpp>
#include <boost/xpressive/xpressive.hpp>
using namespace boost::xpressive;

#define L(x) BOOST_XPR_CSTR_(char_type, x)

#define BOOST_XPR_CHECK(test, pred) \
    if( pred ) {} else { BOOST_ERROR( format_msg(test, #pred).c_str() ); }

using namespace boost::xpressive;

///////////////////////////////////////////////////////////////////////////////
// backrefs
//
template<typename Char>
inline std::vector<std::basic_string<Char> > backrefs(Char const *br0, ...)
{
    using namespace std;
    std::vector<std::basic_string<Char> > backrefs;
    if(0 != br0)
    {
        backrefs.push_back(br0);
        va_list va;
        va_start(va, br0);
        Char const *brN;
        while(0 != (brN = va_arg(va, Char const *)))
        {
            backrefs.push_back(brN);
        }
        va_end(va);
    }
    return backrefs;
}

///////////////////////////////////////////////////////////////////////////////
//
struct no_match_t {};
no_match_t const no_match = {};

///////////////////////////////////////////////////////////////////////////////
// test_case
//
template<typename BidiIter>
struct test_case
{
    typedef BidiIter iterator_type;
    typedef typename boost::iterator_value<iterator_type>::type char_type;
    typedef basic_regex<iterator_type> regex_type;
    typedef std::basic_string<char_type> string_type;

    string_type str_;
    string_type pat_;
    regex_constants::syntax_option_type flags_;
    regex_type  dynamicrx_;
    regex_type  staticrx_;
   
    std::vector<string_type> backrefs_;

    test_case
    (
        string_type str
      , string_type dynamicrx
      , regex_type staticrx
      , string_type flags
      , std::vector<string_type> backrefs
    )
      : str_(str)
      , pat_(dynamicrx)
      , flags_(parse_flags(flags))
      , dynamicrx_(regex_type::compile(dynamicrx, flags_))
      , staticrx_(staticrx)
      , backrefs_(backrefs)
    {
    }

    test_case
    (
        string_type str
      , string_type dynamicrx
      , regex_type staticrx
      , string_type flags
      , no_match_t
    )
      : str_(str)
      , pat_(dynamicrx)
      , flags_(parse_flags(flags))
      , dynamicrx_(regex_type::compile(dynamicrx, flags_))
      , staticrx_(staticrx)
      , backrefs_()
    {
    }

private:

    static regex_constants::syntax_option_type parse_flags(string_type const &flg)
    {
        regex_constants::syntax_option_type flags = regex_constants::ECMAScript;

        if( string_type::npos != flg.find(L('i')) )
        {
            flags = flags | regex_constants::icase;
        }
        if( string_type::npos == flg.find(L('m')) )
        {
            flags = flags | regex_constants::single_line;
        }
        if( string_type::npos == flg.find(L('s')) )
        {
            flags = flags | regex_constants::not_dot_newline;
        }
        if( string_type::npos != flg.find(L('x')) )
        {
            flags = flags | regex_constants::ignore_white_space;
        }

        return flags;
    }
};

///////////////////////////////////////////////////////////////////////////////
// format_msg
template<typename BidiIter>
inline std::string format_msg(test_case<BidiIter> const &test, char const *msg)
{
    std::string pat(test.pat_.begin(), test.pat_.end());
    return /*section +*/ " /" + pat + "/ : " + msg;
}

///////////////////////////////////////////////////////////////////////////////
/// INTERNAL ONLY
template<typename BidiIter>
inline void run_impl(basic_regex<BidiIter> const &rx, test_case<BidiIter> const &test)
{
    typedef typename boost::iterator_value<BidiIter>::type char_type;
    match_results<BidiIter> what;
    if(regex_search(test.str_, what, rx))
    {
        // match succeeded: was it expected to succeed?
        BOOST_XPR_CHECK(test, what.size() == test.backrefs_.size());

        for(std::size_t i = 0; i < what.size() && i < test.backrefs_.size(); ++i)
        {
            BOOST_XPR_CHECK(test, test.backrefs_[i] == what[i].str());
        }
    }
    else
    {
        // match failed: was it expected to fail?
        BOOST_XPR_CHECK(test, 0 == test.backrefs_.size());
    }
}

///////////////////////////////////////////////////////////////////////////////
// run_test
template<typename BidiIter>
void run_test(test_case<BidiIter> const &test)
{
    run_impl(test.dynamicrx_, test);
    run_impl(test.staticrx_, test);
}


///////////////////////////////////////////////////////////////////////////////
// helpful debug routines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// remove all occurances of sz from str
inline void string_remove(std::string &str, char const *sz)
{
    std::string::size_type i = 0, n = std::strlen(sz);
    while(std::string::npos != (i=str.find(sz,i)))
    {
        str.erase(i,n);
    }
}

///////////////////////////////////////////////////////////////////////////////
// display_type2
//  for type T, write typeid::name after performing some substitutions
template<typename T>
inline void display_type2()
{
    std::string str = typeid(T).name();

    string_remove(str, "struct ");
    string_remove(str, "boost::");
    string_remove(str, "xpressive::");
    string_remove(str, "detail::");
    string_remove(str, "fusion::");

    //std::printf("%s\n\n", str.c_str());
    std::printf("%s\nwdith=%d\nis_pure=%s\n\n", str.c_str()
        , detail::width_of<T>::value
        , detail::is_pure<T>::value ? "true" : "false");
}

///////////////////////////////////////////////////////////////////////////////
// display_type
//  display the type of the deduced template argument
template<typename T>
inline void display_type(T const &)
{
    display_type2<T>();
}

///////////////////////////////////////////////////////////////////////////////
// test_compile
//  try to compile a given static regular expression
template<typename BidiIter, typename Xpr>
inline void test_compile(Xpr const &xpr)
{
    typedef typename boost::iterator_value<BidiIter>::type char_type;
    typedef boost::xpressive::regex_traits<char_type> traits_type;
    boost::xpressive::detail::xpression_visitor<BidiIter, boost::mpl::false_, traits_type> visitor;

    display_type(boost::proto::compile(
        xpr
      , boost::xpressive::detail::end_xpression()
      , visitor
      , boost::xpressive::detail::seq_tag()
    ));
}

#endif
