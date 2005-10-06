/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_XPRESSIVE_SPIRIT_RANGE_RUN_IPP
#define BOOST_XPRESSIVE_SPIRIT_RANGE_RUN_IPP

///////////////////////////////////////////////////////////////////////////////
#include <algorithm> // for std::lower_bound
#include <boost/limits.hpp>
#include <boost/assert.hpp>
#include <boost/xpressive/detail/utility/chset/range_run.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////
//
//  range class implementation
//
///////////////////////////////////////////////////////////////////////
template<typename CharT>
inline range<CharT>::range(CharT first, CharT last)
  : first_(first)
  , last_(last)
{
}

//////////////////////////////////
template<typename CharT>
inline bool range<CharT>::is_valid() const
{
    return this->first_ <= this->last_;
}

//////////////////////////////////
template<typename CharT>
inline bool range<CharT>::includes(range<CharT> const &r) const
{
    return (this->first_ <= r.first_) && (this->last_ >= r.last_);
}

//////////////////////////////////
template<typename CharT>
inline bool range<CharT>::includes(CharT v) const
{
    return (this->first_ <= v) && (this->last_ >= v);
}

//////////////////////////////////
template<typename CharT>
inline bool range<CharT>::overlaps(range<CharT> const &r) const
{
    CharT decr_first =
        this->first_ == (std::numeric_limits<CharT>::min)() ? this->first_ : this->first_-1;
    CharT incr_last =
        this->last_ == (std::numeric_limits<CharT>::max)() ? this->last_ : this->last_+1;

    return (decr_first <= r.last_) && (incr_last >= r.first_);
}

//////////////////////////////////
template<typename CharT>
inline void range<CharT>::merge(range<CharT> const &r)
{
    this->first_ = (std::min)(this->first_, r.first_);
    this->last_ = (std::max)(this->last_, r.last_);
}

///////////////////////////////////////////////////////////////////////
//
//  range_run class implementation
//
///////////////////////////////////////////////////////////////////////
template<typename CharT>
inline bool range_run<CharT>::empty() const
{
    return this->run_.empty();
}

template<typename CharT>
inline bool range_run<CharT>::test(CharT v) const
{
    if(this->run_.empty())
    {
        return false;
    }

    const_iterator iter = std::lower_bound(this->run_.begin(), this->run_.end(), v, range_char_compare<CharT>());
    return (iter != this->run_.end() && iter->includes(v))
        || (iter != this->run_.begin() && (--iter)->includes(v));
}

template<typename CharT>
template<typename TraitsT>
inline bool range_run<CharT>::test(CharT v, TraitsT const &traits) const
{
    const_iterator begin = this->run_.begin();
    const_iterator end = this->run_.end();

    for(; begin != end; ++begin)
    {
        if(traits.in_range_nocase(begin->first_, begin->last_, v))
        {
            return true;
        }
    }
    return false;
}

//////////////////////////////////
template<typename CharT>
inline void range_run<CharT>::swap(range_run<CharT> &rr)
{
    this->run_.swap(rr.run_);
}

//////////////////////////////////
template<typename CharT>
void range_run<CharT>::merge(iterator iter, range<CharT> const &r)
{
    BOOST_ASSERT(iter != this->run_.end());
    iter->merge(r);

    iterator i = iter;
    while(++i != this->run_.end() && iter->overlaps(*i))
    {
        iter->merge(*i);
    }

    this->run_.erase(++iter, i);
}

//////////////////////////////////
template<typename CharT>
void range_run<CharT>::set(range<CharT> const &r)
{
    BOOST_ASSERT(r.is_valid());
    if(!this->run_.empty())
    {
        iterator iter = std::lower_bound(this->run_.begin(), this->run_.end(), r, range_compare<CharT>());

        if((iter != this->run_.end() && iter->includes(r)) ||
           (iter != this->run_.begin() && (iter - 1)->includes(r)))
        {
            return;
        }
        else if(iter != this->run_.begin() && (iter - 1)->overlaps(r))
        {
            this->merge(--iter, r);
        }
        else if(iter != this->run_.end() && iter->overlaps(r))
        {
            this->merge(iter, r);
        }
        else
        {
            this->run_.insert(iter, r);
        }
    }
    else
    {
        this->run_.push_back(r);
    }
}

//////////////////////////////////
template<typename CharT>
void range_run<CharT>::clear(range<CharT> const &r)
{
    BOOST_ASSERT(r.is_valid());
    if(!this->run_.empty())
    {
        iterator iter = std::lower_bound(this->run_.begin(), this->run_.end(), r, range_compare<CharT>());
        iterator left_iter;

        if((iter != this->run_.begin()) &&
           (left_iter = (iter - 1))->includes(r.first_))
        {
            if(left_iter->last_ > r.last_)
            {
                CharT save_last = left_iter->last_;
                left_iter->last_ = r.first_-1;
                this->run_.insert(iter, range<CharT>(r.last_+1, save_last));
                return;
            }
            else
            {
                left_iter->last_ = r.first_-1;
            }
        }

        iterator i = iter;
        for(; i != this->run_.end() && r.includes(*i); ++i) {}
        if(i != this->run_.end() && i->includes(r.last_))
        {
            i->first_ = r.last_+1;
        }
        this->run_.erase(iter, i);
    }
}

//////////////////////////////////
template<typename CharT>
inline void range_run<CharT>::clear()
{
    this->run_.clear();
}

//////////////////////////////////
template<typename CharT>
inline typename range_run<CharT>::const_iterator range_run<CharT>::begin() const
{
    return this->run_.begin();
}

//////////////////////////////////
template<typename CharT>
inline typename range_run<CharT>::const_iterator range_run<CharT>::end() const
{
    return this->run_.end();
}

}}} // namespace boost::xpressive::detail

#endif
