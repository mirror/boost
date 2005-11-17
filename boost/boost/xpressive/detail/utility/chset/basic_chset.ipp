/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_XPRESSIVE_SPIRIT_BASIC_CHSET_IPP
#define BOOST_XPRESSIVE_SPIRIT_BASIC_CHSET_IPP

///////////////////////////////////////////////////////////////////////////////
#include <bitset>
#include <boost/xpressive/detail/utility/chset/basic_chset.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
//
//  basic_chset: character set implementation
//
///////////////////////////////////////////////////////////////////////////////
template<typename CharT>
inline basic_chset<CharT>::basic_chset()
{
}

//////////////////////////////////
template<typename CharT>
inline basic_chset<CharT>::basic_chset(basic_chset const &arg)
  : rr_(arg.rr_)
{
}

//////////////////////////////////
template<typename CharT>
inline bool basic_chset<CharT>::empty() const
{
    return this->rr_.empty();
}

//////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline bool basic_chset<CharT>::test(CharT v, TraitsT const &, mpl::false_) const // case-sensitive
{
    return this->rr_.test(v);
}

//////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline bool basic_chset<CharT>::test(CharT v, TraitsT const &traits, mpl::true_) const // case-insensitive
{
    return this->rr_.test(v, traits);
}

//////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::set(CharT from, CharT to)
{
    this->rr_.set(range<CharT>(from, to));
}

//////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset<CharT>::set(CharT from, CharT to, TraitsT const &)
{
    this->rr_.set(range<CharT>(from, to));
}

//////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::set(CharT c)
{
    this->rr_.set(range<CharT>(c, c));
}

//////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset<CharT>::set(CharT c, TraitsT const &)
{
    this->rr_.set(range<CharT>(c, c));
}

//////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::clear(CharT c)
{
    this->rr_.clear(range<CharT>(c, c));
}

//////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset<CharT>::clear(CharT c, TraitsT const &)
{
    this->rr_.clear(range<CharT>(c, c));
}

//////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::clear(CharT from, CharT to)
{
    this->rr_.clear(range<CharT>(from, to));
}

//////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset<CharT>::clear(CharT from, CharT to, TraitsT const &)
{
    this->rr_.clear(range<CharT>(from, to));
}

//////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::clear()
{
    this->rr_.clear();
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::inverse()
{
    // BUGBUG is this right? Does this handle icase correctly?
    basic_chset<CharT> inv;
    inv.set((std::numeric_limits<CharT>::min)(), (std::numeric_limits<CharT>::max)());
    inv -= *this;
    this->swap(inv);
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset<CharT>::swap(basic_chset<CharT> &that)
{
    this->rr_.swap(that.rr_);
}

/////////////////////////////////
template<typename CharT>
inline basic_chset<CharT> &
basic_chset<CharT>::operator |=(basic_chset<CharT> const &that)
{
    typedef typename range_run<CharT>::const_iterator const_iterator;
    for(const_iterator iter = that.rr_.begin(); iter != that.rr_.end(); ++iter)
    {
        this->rr_.set(*iter);
    }
    return *this;
}

/////////////////////////////////
template<typename CharT>
inline basic_chset<CharT> &
basic_chset<CharT>::operator &=(basic_chset<CharT> const &that)
{
    basic_chset<CharT> inv;
    inv.set((std::numeric_limits<CharT>::min)(), (std::numeric_limits<CharT>::max)());
    inv -= that;
    *this -= inv;
    return *this;
}

/////////////////////////////////
template<typename CharT>
inline basic_chset<CharT> &
basic_chset<CharT>::operator -=(basic_chset<CharT> const &that)
{
    typedef typename range_run<CharT>::const_iterator const_iterator;
    for(const_iterator iter = that.rr_.begin(); iter != that.rr_.end(); ++iter)
    {   
        this->rr_.clear(*iter);
    }
    return *this;
}

/////////////////////////////////
template<typename CharT>
inline basic_chset<CharT> &
basic_chset<CharT>::operator ^=(basic_chset<CharT> const &that)
{
    basic_chset bma = that;
    bma -= *this;
    *this -= that;
    *this |= bma;
    return *this;
}

#if(CHAR_BIT == 8)

///////////////////////////////////////////////////////////////////////////////
//
//  basic_chset: specializations for 8 bit chars using std::bitset
//
///////////////////////////////////////////////////////////////////////////////
template<typename CharT>
inline basic_chset_8bit<CharT>::basic_chset_8bit()
{
}

/////////////////////////////////
template<typename CharT>
inline basic_chset_8bit<CharT>::basic_chset_8bit(basic_chset_8bit<CharT> const &arg)
  : bset_(arg.bset_)
{
}

/////////////////////////////////
template<typename CharT>
inline bool basic_chset_8bit<CharT>::empty() const
{
    return !this->bset_.any();
}

/////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline bool basic_chset_8bit<CharT>::test(CharT v, TraitsT const &, mpl::false_) const // case-sensitive
{
    return this->bset_.test((unsigned char)v);
}

/////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline bool basic_chset_8bit<CharT>::test(CharT v, TraitsT const &traits, mpl::true_) const // case-insensitive
{
    return this->bset_.test((unsigned char)traits.translate_nocase(v));
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::set(CharT from, CharT to)
{
    for(int i = from; i <= to; ++i)
    {
        this->bset_.set((unsigned char)i);
    }
}

/////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset_8bit<CharT>::set(CharT from, CharT to, TraitsT const &traits)
{
    for(int i = from; i <= to; ++i)
    {
        this->bset_.set((unsigned char)traits.translate_nocase((CharT)i));
    }
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::set(CharT c)
{
    this->bset_.set((unsigned char)c);
}

/////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset_8bit<CharT>::set(CharT c, TraitsT const &traits)
{
    this->bset_.set((unsigned char)traits.translate_nocase(c));
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::clear(CharT from, CharT to)
{
    for(int i = from; i <= to; ++i)
    {
        this->bset_.reset((unsigned char)i);
    }
}

/////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset_8bit<CharT>::clear(CharT from, CharT to, TraitsT const &traits)
{
    for(int i = from; i <= to; ++i)
    {
        this->bset_.reset((unsigned char)traits.translate_nocase((CharT)i));
    }
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::clear(CharT c)
{
    this->bset_.reset((unsigned char)c);
}

/////////////////////////////////
template<typename CharT>
template<typename TraitsT>
inline void basic_chset_8bit<CharT>::clear(CharT c, TraitsT const &traits)
{
    this->bset_.reset((unsigned char)traits.tranlsate_nocase(c));
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::clear()
{
    this->bset_.reset();
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::inverse()
{
    this->bset_.flip();
}

/////////////////////////////////
template<typename CharT>
inline void basic_chset_8bit<CharT>::swap(basic_chset_8bit<CharT> &that)
{
    std::swap(this->bset_, that.bset_);
}

/////////////////////////////////
template<typename CharT>
inline basic_chset_8bit<CharT> &
basic_chset_8bit<CharT>::operator |=(basic_chset_8bit<CharT> const &that)
{
    this->bset_ |= that.bset_;
    return *this;
}

/////////////////////////////////
template<typename CharT>
inline basic_chset_8bit<CharT> &
basic_chset_8bit<CharT>::operator &=(basic_chset_8bit<CharT> const &that)
{
    this->bset_ &= that.bset_;
    return *this;
}

/////////////////////////////////
template<typename CharT>
inline basic_chset_8bit<CharT> &
basic_chset_8bit<CharT>::operator -=(basic_chset_8bit<CharT> const &that)
{
    this->bset_ &= ~that.bset_;
    return *this;
}

/////////////////////////////////
template<typename CharT>
inline basic_chset_8bit<CharT> &
basic_chset_8bit<CharT>::operator ^=(basic_chset_8bit<CharT> const &that)
{
    this->bset_ ^= that.bset_;
    return *this;
}

template<typename CharT>
inline std::bitset<256> const &
basic_chset_8bit<CharT>::base() const
{
    return this->bset_;
}

#endif // if(CHAR_BIT == 8)


///////////////////////////////////////////////////////////////////////////////
// helpers
template<typename CharT, typename TraitsT>
inline void set_char(basic_chset<CharT> &chset, CharT ch, TraitsT const &traits, bool icase)
{
    icase ? chset.set(ch, traits) : chset.set(ch);
}

template<typename CharT, typename TraitsT>
inline void set_range(basic_chset<CharT> &chset, CharT from, CharT to, TraitsT const &traits, bool icase)
{
    icase ? chset.set(from, to, traits) : chset.set(from, to);
}

template<typename CharT, typename TraitsT>
inline void set_class(basic_chset<CharT> &chset, typename TraitsT::char_class_type char_class, bool no, TraitsT const &traits)
{
    BOOST_MPL_ASSERT_RELATION(1, ==, sizeof(CharT));
    for(std::size_t i = 0; i <= UCHAR_MAX; ++i)
    {
        typedef typename std::char_traits<CharT>::int_type int_type;
        CharT ch = std::char_traits<CharT>::to_char_type(static_cast<int_type>(i));
        if(no != traits.isctype(ch, char_class))
        {
            chset.set(ch);
        }
    }
}

}}} // namespace boost::xpressive::detail

#endif

