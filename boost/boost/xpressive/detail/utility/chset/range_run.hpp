/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_XPRESSIVE_SPIRIT_RANGE_RUN_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_SPIRIT_RANGE_RUN_HPP_EAN_10_04_2005

///////////////////////////////////////////////////////////////////////////////
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////
//
//  range class
//
//      Implements a closed range of values. This class is used in
//      the implementation of the range_run class.
//
//      { Low level implementation detail }
//      { Not to be confused with spirit::range }
//
///////////////////////////////////////////////////////////////////////////
template<typename CharT>
struct range
{
    range(CharT first, CharT last);

    bool is_valid() const;
    bool includes(CharT v) const;
    bool includes(range const &r) const;
    bool overlaps(range const &r) const;
    void merge(range const &r);

    CharT first_;
    CharT last_;
};

//////////////////////////////////
template<typename CharT>
struct range_char_compare
{
    bool operator()(range<CharT> const &x, const CharT y) const
    {
        return x.first_ < y;
    }
};

//////////////////////////////////
template<typename CharT>
struct range_compare
{
    bool operator()(range<CharT> const &x, range<CharT> const &y) const
    {
        return x.first_ < y.first_;
    }
};

///////////////////////////////////////////////////////////////////////////
//
//  range_run
//
//      An implementation of a sparse bit (boolean) set. The set uses
//      a sorted vector of disjoint ranges. This class implements the
//      bare minimum essentials from which the full range of set
//      operators can be implemented. The set is constructed from
//      ranges. Internally, adjacent or overlapping ranges are
//      coalesced.
//
//      range_runs are very space-economical in situations where there
//      are lots of ranges and a few individual disjoint values.
//      Searching is O(log n) where n is the number of ranges.
//
//      { Low level implementation detail }
//
///////////////////////////////////////////////////////////////////////////
template<typename CharT>
struct range_run
{
    typedef range<CharT> range_type;
    typedef std::vector<range_type> run_type;
    typedef typename run_type::iterator iterator;
    typedef typename run_type::const_iterator const_iterator;

    void swap(range_run& rr);
    bool empty() const;
    bool test(CharT v) const;
    template<typename TraitsT>
    bool test(CharT v, TraitsT const &traits) const;
    void set(range_type const &r);
    void clear(range_type const &r);
    void clear();

    const_iterator begin() const;
    const_iterator end() const;

private:
    void merge(iterator iter, range_type const &r);

    run_type run_;
};

}}} // namespace boost::xpressive::detail

#endif

