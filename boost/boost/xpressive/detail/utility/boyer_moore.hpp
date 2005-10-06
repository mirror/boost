///////////////////////////////////////////////////////////////////////////////
/// \file boyer_moore.hpp
///   Contains the boyer-moore implementation. Note: this is *not* a general-
///   purpose boyer-moore implementation. It truncates the search string at
///   256 characters, but it is sufficient for the needs of xpressive.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_BOYER_MOORE_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_BOYER_MOORE_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <climits>  // for UCHAR_MAX
#include <cstddef>  // for std::ptrdiff_t
#include <utility>  // for std::max
#include <vector>
#include <boost/mpl/bool.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>

namespace boost { namespace xpressive { namespace detail
{

/////////////////////////////////////////////////////////////////////////////////
//// case_fold
//template<typename TraitsT>
//struct case_fold
//  : is_convertible<
//        typename TraitsT::version_tag *
//      , regex_traits_version_1_case_fold_tag *
//    >
//{
//};

///////////////////////////////////////////////////////////////////////////////
// boyer_moore
//
template<typename BidiIterT, typename TraitsT> //, bool CaseFoldT = case_fold<TraitsT>::value>
struct boyer_moore
{
    typedef typename iterator_value<BidiIterT>::type char_type;
    typedef TraitsT traits_type;
    typedef is_convertible<
        typename TraitsT::version_tag *
      , regex_traits_version_1_case_fold_tag *
    > case_fold;
    typedef typename TraitsT::string_type string_type;

    // initialize the Boyer-Moore search data structure, using the
    // search sub-sequence to prime the pump.
    boyer_moore(char_type const *begin, char_type const *end, TraitsT const &traits, bool icase)
      : begin_(begin)
      , last_(begin)
      , fold_()
      , find_fun_(
              icase
            ? (case_fold() ? &boyer_moore::find_nocase_fold_ : &boyer_moore::find_nocase_)
            : &boyer_moore::find_
        )
    {
        std::ptrdiff_t const uchar_max = UCHAR_MAX;
        std::ptrdiff_t diff = std::distance(begin, end);
        this->length_  = static_cast<unsigned char>((std::min)(diff, uchar_max));
        std::fill_n(this->offsets_, uchar_max + 1, this->length_);
        --this->length_;

        icase ? this->init_(traits, case_fold()) : this->init_(traits, mpl::false_());
    }

    BidiIterT find(BidiIterT begin, BidiIterT end, TraitsT const &traits) const
    {
        return (this->*this->find_fun_)(begin, end, traits);
    }

private:

    void init_(TraitsT const &traits, mpl::false_)
    {
        for(unsigned char offset = this->length_; offset; --offset, ++this->last_)
        {
            this->offsets_[traits.hash(*this->last_)] = offset;
        }
    }

    void init_(TraitsT const &traits, mpl::true_)
    {
        this->fold_.reserve(this->length_ + 1);
        for(unsigned char offset = this->length_; offset; --offset, ++this->last_)
        {
            this->fold_.push_back(traits.fold_case(*this->last_));
            for(typename string_type::const_iterator beg = this->fold_.back().begin(), end = this->fold_.back().end();
                beg != end; ++beg)
            {
                this->offsets_[traits.hash(*beg)] = offset;
            }
        }
        this->fold_.push_back(traits.fold_case(*this->last_));
    }

    // case-sensitive Boyer-Moore search
    BidiIterT find_(BidiIterT begin, BidiIterT end, TraitsT const &traits) const
    {
        typedef typename boost::iterator_difference<BidiIterT>::type diff_type;
        diff_type const endpos = std::distance(begin, end);
        diff_type offset = static_cast<diff_type>(this->length_);

        for(diff_type curpos = offset; curpos < endpos; curpos += offset)
        {
            std::advance(begin, offset);

            char_type const *pat_tmp = this->last_;
            BidiIterT str_tmp = begin;

            for(; traits.translate(*str_tmp) == *pat_tmp; --pat_tmp, --str_tmp)
            {
                if(pat_tmp == this->begin_)
                {
                    return str_tmp;
                }
            }

            offset = this->offsets_[traits.hash(traits.translate(*begin))];
        }

        return end;
    }

    // case-insensitive Boyer-Moore search
    BidiIterT find_nocase_(BidiIterT begin, BidiIterT end, TraitsT const &traits) const
    {
        typedef typename boost::iterator_difference<BidiIterT>::type diff_type;
        diff_type const endpos = std::distance(begin, end);
        diff_type offset = static_cast<diff_type>(this->length_);

        for(diff_type curpos = offset; curpos < endpos; curpos += offset)
        {
            std::advance(begin, offset);

            char_type const *pat_tmp = this->last_;
            BidiIterT str_tmp = begin;

            for(; traits.translate_nocase(*str_tmp) == *pat_tmp; --pat_tmp, --str_tmp)
            {
                if(pat_tmp == this->begin_)
                {
                    return str_tmp;
                }
            }

            offset = this->offsets_[traits.hash(traits.translate_nocase(*begin))];
        }

        return end;
    }

    // case-insensitive Boyer-Moore search with case-folding
    BidiIterT find_nocase_fold_(BidiIterT begin, BidiIterT end, TraitsT const &traits) const
    {
        typedef typename boost::iterator_difference<BidiIterT>::type diff_type;
        diff_type const endpos = std::distance(begin, end);
        diff_type offset = static_cast<diff_type>(this->length_);

        for(diff_type curpos = offset; curpos < endpos; curpos += offset)
        {
            std::advance(begin, offset);

            string_type const *pat_tmp = &this->fold_.back();
            BidiIterT str_tmp = begin;

            for(; pat_tmp->end() != std::find(pat_tmp->begin(), pat_tmp->end(), *str_tmp);
                --pat_tmp, --str_tmp)
            {
                if(pat_tmp == &this->fold_.front())
                {
                    return str_tmp;
                }
            }

            offset = this->offsets_[traits.hash(*begin)];
        }

        return end;
    }

private:

    char_type const *begin_;
    char_type const *last_;
    std::vector<string_type> fold_;
    BidiIterT (boyer_moore::*const find_fun_)(BidiIterT, BidiIterT, TraitsT const &) const;
    unsigned char length_;
    unsigned char offsets_[UCHAR_MAX + 1];
};

}}} // namespace boost::xpressive::detail

#endif
