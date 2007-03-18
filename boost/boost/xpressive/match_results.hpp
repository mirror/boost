///////////////////////////////////////////////////////////////////////////////
/// \file match_results.hpp
/// Contains the definition of the match_results type and associated helpers.
/// The match_results type holds the results of a regex_match() or
/// regex_search() operation.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_MATCH_RESULTS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_MATCH_RESULTS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <iterator>
#include <boost/assert.hpp>
#include <boost/integer.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/iterator_adaptors.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/converter.hpp>
#if BOOST_ITERATOR_ADAPTORS_VERSION >= 0x0200
# include <boost/iterator/filter_iterator.hpp>
#endif
#include <boost/xpressive/regex_constants.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/sub_match_vector.hpp>
#include <boost/xpressive/detail/utility/sequence_stack.hpp>
#include <boost/xpressive/detail/core/results_cache.hpp>
#include <boost/xpressive/detail/core/action_state.hpp>
#include <boost/xpressive/detail/utility/literals.hpp>
#include <boost/xpressive/detail/utility/algorithm.hpp>
#include <boost/xpressive/detail/utility/counted_base.hpp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// results_extras
//
template<typename BidiIter>
struct results_extras
  : counted_base<results_extras<BidiIter> >
{
    sequence_stack<sub_match_impl<BidiIter> > sub_match_stack_;
    results_cache<BidiIter> results_cache_;
};

///////////////////////////////////////////////////////////////////////////////
// char_overflow_handler_
//
struct char_overflow_handler_
{
    void operator ()(numeric::range_check_result result) const // throw(regex_error)
    {
        if(numeric::cInRange != result)
        {
            throw regex_error(regex_constants::error_escape,
                "character escape too large to fit in target character type");
        }
    }
};

///////////////////////////////////////////////////////////////////////////////
// transform_op enum
//
enum transform_op { None, Upper, Lower };
enum transform_scope { Next, Rest };

///////////////////////////////////////////////////////////////////////////////
// case_converting_iterator
//
template<typename OutputIterator, typename Char>
struct case_converting_iterator
  : std::iterator<std::output_iterator_tag, Char, void, void, void>
{
    case_converting_iterator(OutputIterator const &out, traits<Char> const *traits)
      : out_(out)
      , traits_(traits)
      , next_(None)
      , rest_(None)
    {}

    OutputIterator base() const
    {
        return this->out_;
    }

    case_converting_iterator &operator ++()
    {
        ++this->out_;
        return *this;
    }

    case_converting_iterator operator ++(int)
    {
        case_converting_iterator tmp(*this);
        ++*this;
        return tmp;
    }

    case_converting_iterator &operator *()
    {
        return *this;
    }

    friend bool set_transform(case_converting_iterator &iter, transform_op trans, transform_scope scope)
    {
        (scope == Next ? iter.next_ : iter.rest_) = trans;
        return true;
    }

    case_converting_iterator &operator =(Char const &ch)
    {
        switch(this->next_)
        {
        case Lower:
            *this->out_ = this->traits_->tolower(ch);
            this->next_ = None;
            break;

        case Upper:
            *this->out_ = this->traits_->toupper(ch);
            this->next_ = None;
            break;

        default:
            switch(this->rest_)
            {
            case Lower:
                *this->out_ = this->traits_->tolower(ch);
                break;

            case Upper:
                *this->out_ = this->traits_->toupper(ch);
                break;

            default:
                *this->out_ = ch;
            }
        }

        return *this;
    }

private:
    OutputIterator out_;
    traits<Char> const *traits_;
    transform_op next_, rest_;
};

template<typename Iterator>
inline bool set_transform(Iterator &, transform_op, transform_scope)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// noop_output_iterator
//
struct noop_output_iterator
  : std::iterator<std::output_iterator_tag, void, void, void, void>
{
    noop_output_iterator &operator ++()
    {
        return *this;
    }

    noop_output_iterator &operator ++(int)
    {
        return *this;
    }

    noop_output_iterator &operator *()
    {
        return *this;
    }

    template<typename T>
    noop_output_iterator &operator =(T const &)
    {
        return *this;
    }
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// match_results
/// \brief Class template match_results\<\> holds the results of a regex_match() or a
/// regex_search() as a collection of sub_match objects.
///
/// Class template match_results\<\> denotes a collection of sequences representing the result of
/// a regular expression match. Storage for the collection is allocated and freed as necessary by
/// the member functions of class match_results\<\>.
///
/// The class template match_results\<\> conforms to the requirements of a Sequence, as specified
/// in (lib.sequence.reqmts), except that only operations defined for const-qualified Sequences are
/// supported.
template<typename BidiIter>
struct match_results
{
private:
    struct dummy { int i_; };
    typedef int dummy::*bool_type;

public:
    typedef typename iterator_value<BidiIter>::type char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::size_t size_type;
    typedef sub_match<BidiIter> value_type;
    typedef typename iterator_difference<BidiIter>::type difference_type;
    typedef value_type const &reference;
    typedef value_type const &const_reference;

    typedef typename detail::sub_match_vector<BidiIter>::iterator iterator;
    typedef typename detail::sub_match_vector<BidiIter>::const_iterator const_iterator;
    typedef typename detail::nested_results<BidiIter> nested_results_type;

    /// \post regex_id() == 0
    /// \post size()     == 0
    /// \post empty()    == true
    match_results()
      : regex_id_(0)
      , sub_matches_()
      , base_()
      , prefix_()
      , suffix_()
      , nested_results_()
      , action_state_()
      , extras_ptr_()
      , traits_()
    {
    }

    /// \param that The match_results object to copy
    /// \post regex_id()  == that.regex_id().
    /// \post size()      == that.size().
    /// \post empty()     == that.empty().
    /// \post str(n)      == that.str(n) for all positive integers n \< that.size().
    /// \post prefix()    == that.prefix().
    /// \post suffix()    == that.suffix().
    /// \post (*this)[n]  == that[n] for all positive integers n \< that.size().
    /// \post length(n)   == that.length(n) for all positive integers n \< that.size().
    /// \post position(n) == that.position(n) for all positive integers n \< that.size().
    match_results(match_results<BidiIter> const &that)
      : regex_id_(that.regex_id_)
      , sub_matches_()
      , base_()
      , prefix_()
      , suffix_()
      , nested_results_()
      , action_state_(that.action_state_)
      , extras_ptr_()
      , traits_()
    {
        if(that)
        {
            extras_type &extras = this->get_extras_();
            std::size_t size = that.sub_matches_.size();
            detail::sub_match_impl<BidiIter> *sub_matches = extras.sub_match_stack_.push_sequence(size);
            detail::core_access<BidiIter>::init_sub_match_vector(this->sub_matches_, sub_matches, size, that.sub_matches_);

            // BUGBUG this doesn't share the extras::sequence_stack
            this->nested_results_ = that.nested_results_;
            this->prefix_ = that.prefix_;
            this->suffix_ = that.suffix_;
            this->base_ = that.base_;
            this->traits_ = that.traits_;
        }
    }

    ~match_results()
    {
    }

    /// \param that The match_results object to copy.
    /// \post regex_id()  == that.regex_id().
    /// \post size()      == that.size().
    /// \post empty()     == that.empty().
    /// \post str(n)      == that.str(n) for all positive integers n \< that.size().
    /// \post prefix()    == that.prefix().
    /// \post suffix()    == that.suffix().
    /// \post (*this)[n]  == that[n] for all positive integers n \< that.size().
    /// \post length(n)   == that.length(n) for all positive integers n \< that.size().
    /// \post position(n) == that.position(n) for all positive integers n \< that.size().
    match_results<BidiIter> &operator =(match_results<BidiIter> const &that)
    {
        match_results<BidiIter>(that).swap(*this);
        return *this;
    }

    /// Returns the number of sub_match elements stored in *this.
    ///
    size_type size() const
    {
        return this->sub_matches_.size();
    }

    /// Returns size() == 0.
    ///
    bool empty() const
    {
        return 0 == this->size();
    }

    /// Returns (*this)[sub].length().
    ///
    difference_type length(size_type sub = 0) const
    {
        return this->sub_matches_[ sub ].length();
    }

    /// If !(*this)[sub].matched then returns -1. Otherwise returns std::distance(base, (*this)[sub].first),
    /// where base is the start iterator of the sequence that was searched. [Note – unless this is part
    /// of a repeated search with a regex_iterator then base is the same as prefix().first – end note]
    difference_type position(size_type sub = 0) const
    {
        return this->sub_matches_[ sub ].matched ? std::distance(this->base_, this->sub_matches_[ sub ].first) : -1;
    }

    /// Returns string_type((*this)[sub]).
    ///
    string_type str(size_type sub = 0) const
    {
        return this->sub_matches_[ sub ].str();
    }

    /// Returns a reference to the sub_match object representing the sequence that
    /// matched marked sub-expression sub. If sub == 0 then returns a reference to a sub_match object
    /// representing the sequence that matched the whole regular expression.
    /// \pre sub \< (*this).size().
    const_reference operator [](size_type sub) const
    {
        return this->sub_matches_[ sub ];
    }

    /// \overload
    ///
    const_reference operator [](detail::basic_mark_tag const &mark) const
    {
        return this->sub_matches_[ detail::get_mark_number(mark) ];
    }

    /// Returns a reference to the sub_match object representing the character sequence from
    /// the start of the string being matched/searched, to the start of the match found.
    ///
    const_reference prefix() const
    {
        return this->prefix_;
    }

    /// Returns a reference to the sub_match object representing the character sequence from
    /// the end of the match found to the end of the string being matched/searched.
    ///
    const_reference suffix() const
    {
        return this->suffix_;
    }

    /// Returns a starting iterator that enumerates over all the marked sub-expression matches
    /// stored in *this.
    ///
    const_iterator begin() const
    {
        return this->sub_matches_.begin();
    }

    /// Returns a terminating iterator that enumerates over all the marked sub-expression
    /// matches stored in *this.
    ///
    const_iterator end() const
    {
        return this->sub_matches_.end();
    }

    /// Returns a true value if(*this)[0].matched, else returns a false value.
    ///
    operator bool_type() const
    {
        return this->sub_matches_[ 0 ].matched ? &dummy::i_ : 0;
    }

    /// Returns true if empty() || !(*this)[0].matched, else returns false.
    ///
    bool operator !() const
    {
        return this->empty() || !this->sub_matches_[ 0 ].matched;
    }

    /// Returns the id of the basic_regex object most recently used with this match_results object.
    ///
    regex_id_type regex_id() const
    {
        return this->regex_id_;
    }

    /// Returns a Sequence of nested match_results elements.
    ///
    nested_results_type const &nested_results() const
    {
        return this->nested_results_;
    }

    /// Copies the character sequence [fmt.begin(), fmt.end()) to OutputIterator out. For each format
    /// specifier or escape sequence in fmt, replace that sequence with either the character(s) it
    /// represents, or the sequence within *this to which it refers. The bitmasks specified in flags
    /// determines what format specifiers or escape sequences are recognized, by default this is the
    /// format used by ECMA-262, ECMAScript Language Specification, Chapter 15 part 5.4.11 String.prototype.replace.
    template<typename OutputIterator>
    OutputIterator format
    (
        OutputIterator out
      , const string_type &fmt
      , regex_constants::match_flag_type flags = regex_constants::format_default
    ) const
    {
        typename string_type::const_iterator cur = fmt.begin(), end = fmt.end();

        if(0 != (regex_constants::format_literal & flags))
        {
            return std::copy(cur, end, out);
        }
        else if(0 != (regex_constants::format_perl & flags))
        {
            return this->format_perl_(cur, end, out);
        }
        else if(0 != (regex_constants::format_sed & flags))
        {
            return this->format_sed_(cur, end, out);
        }
        else if(0 != (regex_constants::format_all & flags))
        {
            return this->format_all_(cur, end, out);
        }

        return this->format_ecma_262_(cur, end, out);
    }

    /// Returns a copy of the string fmt. For each format specifier or escape sequence in fmt,
    /// replace that sequence with either the character(s) it represents, or the sequence within
    /// *this to which it refers. The bitmasks specified in flags determines what format specifiers
    /// or escape sequences are recognized, by default this is the format used by ECMA-262,
    /// ECMAScript Language Specification, Chapter 15 part 5.4.11 String.prototype.replace.
    string_type format(string_type const &fmt, regex_constants::match_flag_type flags = regex_constants::format_default) const
    {
        string_type result;
        result.reserve(fmt.length() * 2);
        this->format(std::back_inserter(result), fmt, flags);
        return result;
    }

    /// Swaps the contents of two match_results objects. Guaranteed not to throw.
    /// \param that The match_results object to swap with.
    /// \post *this contains the sequence of matched sub-expressions that were in that,
    /// that contains the sequence of matched sub-expressions that were in *this.
    /// \throw nothrow
    void swap(match_results<BidiIter> &that) // throw()
    {
        std::swap(this->regex_id_, that.regex_id_);
        this->sub_matches_.swap(that.sub_matches_);
        std::swap(this->base_, that.base_);
        std::swap(this->prefix_, that.prefix_);
        std::swap(this->suffix_, that.suffix_);
        this->nested_results_.swap(that.nested_results_);
        std::swap(this->action_state_, that.action_state_);
        this->extras_ptr_.swap(that.extras_ptr_);
        this->traits_.swap(that.traits_);
    }

    /// INTERNAL ONLY
    ///
    match_results<BidiIter> const &operator ()(regex_id_type regex_id, size_type index = 0) const
    {
        // BUGBUG this is linear, make it O(1)
        static match_results<BidiIter> const s_null;

        regex_id_filter_predicate<BidiIter> pred(regex_id);
        typename nested_results_type::const_iterator
            begin = this->nested_results_.begin()
          , end = this->nested_results_.end()
          , cur = detail::find_nth_if(begin, end, index, pred);

        return (cur == end) ? s_null : *cur;
    }

    /// INTERNAL ONLY
    ///
    match_results<BidiIter> const &operator ()(basic_regex<BidiIter> const &rex, std::size_t index = 0) const
    {
        return (*this)(rex.regex_id(), index);
    }

    // state:
    /// INTERNAL ONLY
    ///
    template<typename State>
    void set_action_state(State &state)
    {
        this->action_state_.set(state);
    }

    /// INTERNAL ONLY
    ///
    template<typename State>
    State &get_action_state() const
    {
        return this->action_state_.BOOST_NESTED_TEMPLATE get<State>();
    }

private:

    friend struct detail::core_access<BidiIter>;
    typedef detail::results_extras<BidiIter> extras_type;

    /// INTERNAL ONLY
    ///
    void init_
    (
        regex_id_type regex_id
      , intrusive_ptr<detail::traits<char_type> const> const &traits
      , detail::sub_match_impl<BidiIter> *sub_matches
      , size_type size
    )
    {
        this->traits_ = traits;
        this->regex_id_ = regex_id;
        detail::core_access<BidiIter>::init_sub_match_vector(this->sub_matches_, sub_matches, size);
    }

    /// INTERNAL ONLY
    ///
    extras_type &get_extras_()
    {
        if(!this->extras_ptr_)
        {
            this->extras_ptr_ = new extras_type;
        }

        return *this->extras_ptr_;
    }

    /// INTERNAL ONLY
    ///
    void set_prefix_suffix_(BidiIter begin, BidiIter end)
    {
        this->base_ = begin;

        this->prefix_.first = begin;
        this->prefix_.second = this->sub_matches_[ 0 ].first;
        this->prefix_.matched = this->prefix_.first != this->prefix_.second;

        this->suffix_.first = this->sub_matches_[ 0 ].second;
        this->suffix_.second = end;
        this->suffix_.matched = this->suffix_.first != this->suffix_.second;

        typename nested_results_type::iterator ibegin = this->nested_results_.begin();
        typename nested_results_type::iterator iend = this->nested_results_.end();
        for( ; ibegin != iend; ++ibegin )
        {
            ibegin->set_prefix_suffix_(begin, end);
        }
    }

    /// INTERNAL ONLY
    ///
    void reset_()
    {
        detail::core_access<BidiIter>::init_sub_match_vector(this->sub_matches_, 0, 0);
    }

    /// INTERNAL ONLY
    ///
    void set_base_(BidiIter base)
    {
        this->base_ = base;

        typename nested_results_type::iterator ibegin = this->nested_results_.begin();
        typename nested_results_type::iterator iend = this->nested_results_.end();
        for( ; ibegin != iend; ++ibegin )
        {
            ibegin->set_base_(base);
        }
    }

    /// INTERNAL ONLY
    ///
    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_ecma_262_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '$'):
                out = this->format_backref_(++cur, end, out);
                break;

            default:
                *out++ = *cur++;
                break;
            }
        }

        return out;
    }

    /// INTERNAL ONLY
    ///
    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_sed_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '&'):
                ++cur;
                out = std::copy(this->sub_matches_[ 0 ].first, this->sub_matches_[ 0 ].second, out);
                break;

            case BOOST_XPR_CHAR_(char_type, '\\'):
                out = this->format_escape_(++cur, end, out);
                break;

            default:
                *out++ = *cur++;
                break;
            }
        }

        return out;
    }

    /// INTERNAL ONLY
    ///
    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_perl_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        detail::case_converting_iterator<OutputIterator, char_type> iout(out, this->traits_.get());

        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '$'):
                iout = this->format_backref_(++cur, end, iout);
                break;

            case BOOST_XPR_CHAR_(char_type, '\\'):
                iout = this->format_escape_(++cur, end, iout);
                break;

            default:
                *iout++ = *cur++;
                break;
            }
        }

        return iout.base();
    }

    /// INTERNAL ONLY
    ///
    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_all_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        detail::case_converting_iterator<OutputIterator, char_type> iout(out, this->traits_.get());
        iout = this->format_all_impl_(cur, end, iout);
        detail::ensure(cur == end
          , regex_constants::error_paren, "unbalanced parentheses in format string");
        return iout.base();
    }

    /// INTERNAL ONLY
    ///
    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_all_impl_(ForwardIterator &cur, ForwardIterator end, OutputIterator out, bool metacolon = false) const
    {
        int max = 0, sub = 0;
        detail::noop_output_iterator noop;

        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '$'):
                out = this->format_backref_(++cur, end, out);
                break;

            case BOOST_XPR_CHAR_(char_type, '\\'):
                out = this->format_escape_(++cur, end, out);
                break;

            case BOOST_XPR_CHAR_(char_type, '('):
                out = this->format_all_impl_(++cur, end, out);
                detail::ensure(BOOST_XPR_CHAR_(char_type, ')') == *(cur-1)
                  , regex_constants::error_paren, "unbalanced parentheses in format string");
                break;

            case BOOST_XPR_CHAR_(char_type, '?'):
                detail::ensure(++cur != end
                  , regex_constants::error_subreg, "malformed conditional in format string");
                max = static_cast<int>(this->size() - 1);
                sub = detail::toi(cur, end, *this->traits_, 10, max);
                detail::ensure(0 != sub, regex_constants::error_subreg, "invalid back-reference");
                if(this->sub_matches_[ sub ].matched)
                {
                    out = this->format_all_impl_(cur, end, out, true);
                    if(BOOST_XPR_CHAR_(char_type, ':') == *(cur-1))
                        this->format_all_impl_(cur, end, noop);
                }
                else
                {
                    this->format_all_impl_(cur, end, noop, true);
                    if(BOOST_XPR_CHAR_(char_type, ':') == *(cur-1))
                        out = this->format_all_impl_(cur, end, out);
                }
                return out;

            case BOOST_XPR_CHAR_(char_type, ':'):
                if(metacolon)
                {
            case BOOST_XPR_CHAR_(char_type, ')'):
                    ++cur;
                    return out;
                }
                // else fall-through

            default:
                *out++ = *cur++;
                break;
            }
        }

        return out;
    }

    /// INTERNAL ONLY
    ///
    template<typename OutputIterator>
    OutputIterator format_backref_
    (
        typename string_type::const_iterator &cur
      , typename string_type::const_iterator end
      , OutputIterator out
    ) const
    {
        if(cur == end)
        {
            *out++ = BOOST_XPR_CHAR_(char_type, '$');
        }
        else if(BOOST_XPR_CHAR_(char_type, '$') == *cur)
        {
            *out++ = *cur++;
        }
        else if(BOOST_XPR_CHAR_(char_type, '&') == *cur) // whole match
        {
            ++cur;
            out = std::copy(this->sub_matches_[ 0 ].first, this->sub_matches_[ 0 ].second, out);
        }
        else if(BOOST_XPR_CHAR_(char_type, '`') == *cur) // prefix
        {
            ++cur;
            out = std::copy(this->prefix().first, this->prefix().second, out);
        }
        else if(BOOST_XPR_CHAR_(char_type, '\'') == *cur) // suffix
        {
            ++cur;
            out = std::copy(this->suffix().first, this->suffix().second, out);
        }
        else if(-1 != this->traits_->value(*cur, 10)) // a sub-match
        {
            int max = static_cast<int>(this->size() - 1);
            int sub = detail::toi(cur, end, *this->traits_, 10, max);
            detail::ensure(0 != sub, regex_constants::error_subreg, "invalid back-reference");
            if(this->sub_matches_[ sub ].matched)
                out = std::copy(this->sub_matches_[ sub ].first, this->sub_matches_[ sub ].second, out);
        }
        else
        {
            *out++ = BOOST_XPR_CHAR_(char_type, '$');
            *out++ = *cur++;
        }

        return out;
    }

    /// INTERNAL ONLY
    ///
    template<typename OutputIterator>
    OutputIterator format_escape_
    (
        typename string_type::const_iterator &cur
      , typename string_type::const_iterator end
      , OutputIterator out
    ) const
    {
        using namespace regex_constants;
        typename string_type::const_iterator tmp;
        // define an unsigned type the same size as char_type
        typedef typename boost::uint_t<CHAR_BIT * sizeof(char_type)>::least uchar_t;
        BOOST_MPL_ASSERT_RELATION(sizeof(uchar_t), ==, sizeof(char_type));
        typedef numeric::conversion_traits<uchar_t, int> converstion_traits;
        numeric::converter<int, uchar_t, converstion_traits, detail::char_overflow_handler_> converter;

        if(cur == end)
        {
            *out++ = BOOST_XPR_CHAR_(char_type, '\\');
            return out;
        }

        char_type ch = *cur++;
        switch(ch)
        {
        case BOOST_XPR_CHAR_(char_type, 'a'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\a');
            break;

        case BOOST_XPR_CHAR_(char_type, 'e'):
            *out++ = converter(27);
            break;

        case BOOST_XPR_CHAR_(char_type, 'f'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\f');
            break;

        case BOOST_XPR_CHAR_(char_type, 'n'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\n');
            break;

        case BOOST_XPR_CHAR_(char_type, 'r'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\r');
            break;

        case BOOST_XPR_CHAR_(char_type, 't'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\t');
            break;

        case BOOST_XPR_CHAR_(char_type, 'v'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\v');
            break;

        case BOOST_XPR_CHAR_(char_type, 'x'):
            detail::ensure(cur != end, error_escape, "unexpected end of format found");
            if(BOOST_XPR_CHAR_(char_type, '{') == *cur)
            {
                detail::ensure(++cur != end, error_escape, "unexpected end of format found");
                tmp = cur;
                *out++ = converter(detail::toi(cur, end, *this->traits_, 16, 0xffff));
                detail::ensure(4 == std::distance(tmp, cur) && cur != end && BOOST_XPR_CHAR_(char_type, '}') == *cur++
                  , error_escape, "invalid hex escape : must be \\x { HexDigit HexDigit HexDigit HexDigit }");
            }
            else
            {
                tmp = cur;
                *out++ = converter(detail::toi(cur, end, *this->traits_, 16, 0xff));
                detail::ensure(2 == std::distance(tmp, cur), error_escape
                  , "invalid hex escape : must be \\x HexDigit HexDigit");
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'c'):
            detail::ensure(cur != end, error_escape, "unexpected end of format found");
            detail::ensure
            (
                this->traits_->in_range(BOOST_XPR_CHAR_(char_type, 'a'), BOOST_XPR_CHAR_(char_type, 'z'), *cur)
             || this->traits_->in_range(BOOST_XPR_CHAR_(char_type, 'A'), BOOST_XPR_CHAR_(char_type, 'Z'), *cur)
              , error_escape
              , "invalid escape control letter; must be one of a-z or A-Z"
            );
            // Convert to character according to ECMA-262, section 15.10.2.10:
            *out++ = converter(*cur % 32);
            ++cur;
            break;

        case BOOST_XPR_CHAR_(char_type, 'l'):
            if(!set_transform(out, detail::Lower, detail::Next))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'l');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'L'):
            if(!set_transform(out, detail::Lower, detail::Rest))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'L');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'u'):
            if(!set_transform(out, detail::Upper, detail::Next))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'u');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'U'):
            if(!set_transform(out, detail::Upper, detail::Rest))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'U');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'E'):
            if(!set_transform(out, detail::None, detail::Rest))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'E');
            }
            break;

        default:
            if(0 < this->traits_->value(ch, 10))
            {
                int sub = this->traits_->value(ch, 10);
                if(this->sub_matches_[ sub ].matched)
                    out = std::copy(this->sub_matches_[ sub ].first, this->sub_matches_[ sub ].second, out);
            }
            else
            {
                *out++ = ch;
            }
            break;
        }

        return out;
    }

    regex_id_type regex_id_;
    detail::sub_match_vector<BidiIter> sub_matches_;
    BidiIter base_;
    sub_match<BidiIter> prefix_;
    sub_match<BidiIter> suffix_;
    nested_results_type nested_results_;
    detail::action_state action_state_;
    intrusive_ptr<extras_type> extras_ptr_;
    intrusive_ptr<detail::traits<char_type> const> traits_;
};

///////////////////////////////////////////////////////////////////////////////
// action_state_cast
/// INTERNAL ONLY
///
template<typename State, typename BidiIter>
inline State &action_state_cast(match_results<BidiIter> const &what)
{
    return what.BOOST_NESTED_TEMPLATE get_action_state<State>();
}

///////////////////////////////////////////////////////////////////////////////
// regex_id_filter_predicate
//
template<typename BidiIter>
struct regex_id_filter_predicate
  : std::unary_function<match_results<BidiIter>, bool>
{
    regex_id_filter_predicate(regex_id_type regex_id)
      : regex_id_(regex_id)
    {
    }

    bool operator ()(match_results<BidiIter> const &res) const
    {
        return this->regex_id_ == res.regex_id();
    }

private:

    regex_id_type regex_id_;
};

}} // namespace boost::xpressive

#endif
