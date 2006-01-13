///////////////////////////////////////////////////////////////////////////////
// test.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_TEST_TEST_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_TEST_TEST_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <string>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <functional>
#include <boost/range/iterator_range.hpp>
#include <boost/xpressive/xpressive_static.hpp>
#include "./test_minimal.hpp"
using namespace boost::xpressive;

#define L(x) BOOST_XPR_CSTR_(char_type, x)

#define BOOST_XPR_CHECK(pred)                                                   \
    if( pred ) {} else { BOOST_ERROR( this->format_msg(#pred).c_str() ); }

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

template<typename BidiIter>
struct test_case;

template<typename BidiIter>
std::string format_msg(test_case<BidiIter> const &test, char const *msg);

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
    typedef std::vector<string_type> backrefs_type;

    test_case(std::string section, string_type str, regex_type rex, backrefs_type brs)
      : section_(section)
      , str_(str)
      , rex_(rex)
      , brs_(brs)
    {
    }

    test_case(std::string section, string_type str, regex_type rex, no_match_t)
      : section_(section)
      , str_(str)
      , rex_(rex)
      , brs_()
    {
    }

    void run() const
    {
        char_type const empty[] = {0};
        match_results<BidiIter> what;
        if(regex_search(this->str_, what, this->rex_))
        {
            // match succeeded: was it expected to succeed?
            BOOST_XPR_CHECK(what.size() == this->brs_.size());

            for(std::size_t i = 0; i < what.size() && i < this->brs_.size(); ++i)
            {
                BOOST_XPR_CHECK(!what[i].matched && this->brs_[i] == empty || this->brs_[i] == what[i].str());
            }
        }
        else
        {
            // match failed: was it expected to fail?
            BOOST_XPR_CHECK(0 == this->brs_.size());
        }
    }

private:

    std::string format_msg(char const *msg) const
    {
        return this->section_ + " : " + msg;
    }

    std::string section_;
    string_type str_;
    regex_type rex_;
    std::vector<string_type> brs_;
};

///////////////////////////////////////////////////////////////////////////////
// test_runner
template<typename BidiIter>
struct test_runner
  : std::unary_function<test_case<BidiIter>, void>
{
    void operator ()(test_case<BidiIter> const &test) const
    {
        test.run();
    }
};

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
