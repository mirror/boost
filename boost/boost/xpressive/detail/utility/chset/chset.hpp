///////////////////////////////////////////////////////////////////////////////
// chset.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CHSET_CHSET_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CHSET_CHSET_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/utility/algorithm.hpp>
#include <boost/xpressive/detail/utility/chset/basic_chset.ipp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// compound_charset
//
template<typename TraitsT>
struct compound_charset
  : private basic_chset<typename TraitsT::char_type>
{
    typedef typename TraitsT::char_type char_type;
    typedef basic_chset<char_type> base_type;
    typedef TraitsT traits_type;
    typedef typename TraitsT::char_class_type char_class_type;

    compound_charset()
      : base_type()
      , complement_(false)
      , has_posix_(false)
      , posix_yes_()
      , posix_no_()
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // accessors
    basic_chset<char_type> const &basic_chset() const
    {
        return *this;
    }

    bool is_inverted() const
    {
        return this->complement_;
    }

    char_class_type posix_yes() const
    {
        return this->posix_yes_;
    }

    std::vector<char_class_type> const &posix_no() const
    {
        return this->posix_no_;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // complement
    void inverse()
    {
        this->complement_ = !this->complement_;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // set
    void set_char(char_type ch, TraitsT const &traits, bool icase)
    {
        icase ? this->base_type::set(ch, traits) : this->base_type::set(ch);
    }

    void set_range(char_type from, char_type to, TraitsT const &traits, bool icase)
    {
        icase ? this->base_type::set(from, to, traits) : this->base_type::set(from, to);
    }

    void set_class(char_class_type const &m, bool no, bool)
    {
        this->has_posix_ = true;

        if(no)
        {
            this->posix_no_.push_back(m);
        }
        else
        {
            this->posix_yes_ |= m;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // test
    template<typename ICaseT>
    bool test(char_type ch, TraitsT const &traits, ICaseT) const
    {
        return this->complement_ !=
            (this->base_type::test(ch, traits, ICaseT()) ||
            (this->has_posix_ && this->test_posix(ch, traits)));
    }

private:

    ///////////////////////////////////////////////////////////////////////////////
    // not_posix_pred
    struct not_posix_pred
    {
        char_type ch_;
        TraitsT const *traits_ptr_;

        bool operator ()(typename call_traits<char_class_type>::param_type m) const
        {
            return !this->traits_ptr_->isctype(this->ch_, m);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // test_posix
    bool test_posix(char_type ch, TraitsT const &traits) const
    {
        not_posix_pred const pred = {ch, &traits};
        return traits.isctype(ch, this->posix_yes_)
            || any(this->posix_no_.begin(), this->posix_no_.end(), pred);
    }

    bool complement_;
    bool has_posix_;
    char_class_type posix_yes_;
    std::vector<char_class_type> posix_no_;
};


///////////////////////////////////////////////////////////////////////////////
// helpers
template<typename CharT, typename TraitsT>
inline void set_char(compound_charset<TraitsT> &chset, CharT ch, TraitsT const &traits, bool icase)
{
    chset.set_char(ch, traits, icase);
}

template<typename CharT, typename TraitsT>
inline void set_range(compound_charset<TraitsT> &chset, CharT from, CharT to, TraitsT const &traits, bool icase)
{
    chset.set_range(from, to, traits, icase);
}

template<typename TraitsT>
inline void set_class(compound_charset<TraitsT> &chset, typename TraitsT::char_class_type char_class, bool no, TraitsT const &, bool icase)
{
    chset.set_class(char_class, no, icase);
}

}}} // namespace boost::xpressive::detail

#endif

