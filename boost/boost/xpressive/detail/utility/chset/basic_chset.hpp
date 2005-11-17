/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_XPRESSIVE_SPIRIT_BASIC_CHSET_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_SPIRIT_BASIC_CHSET_HPP_EAN_10_04_2005

///////////////////////////////////////////////////////////////////////////////
#include <bitset>
#include <boost/mpl/bool.hpp>
#include <boost/xpressive/detail/utility/chset/range_run.ipp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////
//
//  basic_chset: basic character set implementation using range_run
//
///////////////////////////////////////////////////////////////////////////
template<typename CharT>
struct basic_chset
{
    basic_chset();
    basic_chset(basic_chset const &arg);

    bool empty() const;
    void set(CharT from, CharT to);
    template<typename TraitsT>
    void set(CharT from, CharT to, TraitsT const &traits);
    void set(CharT c);
    template<typename TraitsT>
    void set(CharT c, TraitsT const &traits);

    void clear(CharT from, CharT to);
    template<typename TraitsT>
    void clear(CharT from, CharT to, TraitsT const &traits);
    void clear(CharT c);
    template<typename TraitsT>
    void clear(CharT c, TraitsT const &traits);
    void clear();

    template<typename TraitsT>
    bool test(CharT v, TraitsT const &traits, mpl::false_) const; // case-sensitive
    template<typename TraitsT>
    bool test(CharT v, TraitsT const &traits, mpl::true_) const; // case-insensitive

    void inverse();
    void swap(basic_chset& x);

    basic_chset &operator |=(basic_chset const &x);
    basic_chset &operator &=(basic_chset const &x);
    basic_chset &operator -=(basic_chset const &x);
    basic_chset &operator ^=(basic_chset const &x);

private:
    range_run<CharT> rr_;
};

#if(CHAR_BIT == 8)

///////////////////////////////////////////////////////////////////////////
//
//  basic_chset: specializations for 8 bit chars using std::bitset
//
///////////////////////////////////////////////////////////////////////////
template<typename CharT>
struct basic_chset_8bit
{
    basic_chset_8bit();
    basic_chset_8bit(basic_chset_8bit const &arg);

    bool empty() const;
    
    void set(CharT from, CharT to);
    template<typename TraitsT>
    void set(CharT from, CharT to, TraitsT const &traits);
    void set(CharT c);
    template<typename TraitsT>
    void set(CharT c, TraitsT const &traits);

    void clear(CharT from, CharT to);
    template<typename TraitsT>
    void clear(CharT from, CharT to, TraitsT const &traits);
    void clear(CharT c);
    template<typename TraitsT>
    void clear(CharT c, TraitsT const &traits);
    void clear();

    template<typename TraitsT>
    bool test(CharT v, TraitsT const &traits, mpl::false_) const; // case-sensitive
    template<typename TraitsT>
    bool test(CharT v, TraitsT const &traits, mpl::true_) const; // case-insensitive

    void inverse();
    void swap(basic_chset_8bit& x);

    basic_chset_8bit &operator |=(basic_chset_8bit const &x);
    basic_chset_8bit &operator &=(basic_chset_8bit const &x);
    basic_chset_8bit &operator -=(basic_chset_8bit const &x);
    basic_chset_8bit &operator ^=(basic_chset_8bit const &x);

    std::bitset<256> const &base() const;

private:
    std::bitset<256> bset_; // BUGBUG range-checking slows this down
};

/////////////////////////////////
template<>
struct basic_chset<char>
  : basic_chset_8bit<char>
{
};

/////////////////////////////////
template<>
struct basic_chset<signed char>
  : basic_chset_8bit<signed char>
{
};

/////////////////////////////////
template<>
struct basic_chset<unsigned char>
  : basic_chset_8bit<unsigned char>
{
};

#endif

///////////////////////////////////////////////////////////////////////////////
// helpers
template<typename CharT, typename TraitsT>
void set_char(basic_chset<CharT> &chset, CharT ch, TraitsT const &traits, bool icase);

template<typename CharT, typename TraitsT>
void set_range(basic_chset<CharT> &chset, CharT from, CharT to, TraitsT const &traits, bool icase);

template<typename CharT, typename TraitsT>
void set_class(basic_chset<CharT> &chset, typename TraitsT::char_class_type char_class, bool no, TraitsT const &traits);

}}} // namespace boost::xpressive::detail

#endif
