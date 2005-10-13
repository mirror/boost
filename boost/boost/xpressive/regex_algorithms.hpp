///////////////////////////////////////////////////////////////////////////////
/// \file regex_algorithms.hpp
/// Contains the regex_match(), regex_search() and regex_replace() algorithms.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_ALGORITHMS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_ALGORITHMS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <iterator>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/utility/save_restore.hpp>
#include <boost/xpressive/detail/utility/ignore_unused.hpp>

namespace boost { namespace xpressive
{

///////////////////////////////////////////////////////////////////////////////
// regex_match
///////////////////////////////////////////////////////////////////////////////

/// \brief See if a regex matches a sequence from beginning to end.
///
/// Determines whether there is an exact match between the regular expression re,
/// and all of the sequence [begin, end).
///
/// \pre Types BidiIterT and OtherBidiIterT meet the requirements of a Bidirectional Iterator (24.1.4).
/// \pre OtherBidiIterT is convertible to BidiIterT.
/// \pre [begin,end) denotes a valid iterator range.
/// \param begin The beginning of the sequence.
/// \param end The end of the sequence.
/// \param what The match_results struct into which the sub_matches will be written
/// \param re The regular expression object to use
/// \param flags Optional match flags, used to control how the expression is matched against the sequence. (See match_flag_type.)
/// \return true if a match is found, false otherwise
/// \throw regex_error on stack exhaustion
template<typename OtherBidiIterT, typename BidiIterT>
inline bool regex_match
(
    OtherBidiIterT begin
  , OtherBidiIterT end
  , match_results<BidiIterT> &what
  , basic_regex<BidiIterT> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    typedef detail::core_access<BidiIterT> access;

    // an invlid regex matches nothing
    if(!access::invalid(re))
    {
        // the state object holds matching state and
        // is passed by reference to all the matchers
        detail::state_type<BidiIterT> state(begin, end, what, re, flags);
        state.flags_.match_all_ = true;
        state.sub_match(0).begin_ = begin;

        if(access::match(re, state))
        {
            access::set_prefix_suffix(what, begin, end);
            return true;
        }

        // handle partial matches
        else if(state.found_partial_match_ && 0 != (flags & regex_constants::match_partial))
        {
            return state.set_partial_match(), true;
        }
    }

    access::reset(what);
    return false;
}

/// \overload
template<typename OtherBidiIterT, typename BidiIterT>
inline bool regex_match
(
    OtherBidiIterT begin
  , OtherBidiIterT end
  , basic_regex<BidiIterT> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    match_results<BidiIterT> what;
    return regex_match(begin, end, what, re, flags);
}

/// \overload
template<typename CharT>
inline bool regex_match
(
    CharT const *begin
  , match_results<CharT const*> &what
  , basic_regex<CharT const*> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    CharT const *end = begin + std::char_traits<CharT>::length(begin);
    return regex_match(begin, end, what, re, flags);
}

/// \overload
template<typename CharT, typename TraitsT, typename AllocT>
inline bool regex_match
(
    std::basic_string<CharT, TraitsT, AllocT> const &str
  , match_results<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> &what
  , basic_regex<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    return regex_match(str.begin(), str.end(), what, re, flags);
}

/// \overload
template<typename CharT>
inline bool regex_match
(
    CharT const *begin
  , basic_regex<CharT const *> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    match_results<CharT const *> what;
    return regex_match(begin, what, re, flags);
}

/// \overload
template<typename CharT, typename TraitsT, typename AllocT>
inline bool regex_match
(
    std::basic_string<CharT, TraitsT, AllocT> const &str
  , basic_regex<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    match_results<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> what;
    return regex_match(str, what, re, flags);
}


///////////////////////////////////////////////////////////////////////////////
// regex_search
///////////////////////////////////////////////////////////////////////////////

namespace detail
{
///////////////////////////////////////////////////////////////////////////////
// regex_search_impl
template<typename BidiIterT>
inline bool regex_search_impl
(
    state_type<BidiIterT> &state
  , basic_regex<BidiIterT> const &re
  , bool not_initial_null = false
)
{
    typedef core_access<BidiIterT> access;
    typedef typename iterator_value<BidiIterT>::type char_type;
    match_results<BidiIterT> &what = *state.context_.results_ptr_;

    // an invlid regex matches nothing
    if(!access::invalid(re))
    {
        bool const partial_ok = state.flags_.match_partial_;
        bool const not_null = state.flags_.match_not_null_;
        state.flags_.match_prev_avail_ = state.flags_.match_prev_avail_ || !state.bos();
        restore null_restore = save(state.flags_.match_not_null_, not_null || not_initial_null);
        detail::ignore_unused(&null_restore);

        regex_impl<BidiIterT> const &impl = *access::get_regex_impl(re);
        BidiIterT const begin = state.cur_, end = state.end_;
        BidiIterT &sub0begin = state.sub_match(0).begin_;
        sub0begin = state.cur_;

        // If match_continuous is set, we only need to check for a match at the current position
        if(state.flags_.match_continuous_)
        {
            if(access::match(re, state))
            {
                access::set_prefix_suffix(what, begin, end);
                return true;
            }

            // handle partial matches
            else if(partial_ok && state.found_partial_match_)
            {
                return state.set_partial_match(), true;
            }
        }

        // If we have a finder, use it to find where a potential match can start
        else if(impl.finder_)
        {
            finder<BidiIterT> const &find = *impl.finder_;
            if(find(state))
            {
                if(state.cur_ != begin)
                {
                    state.flags_.match_not_null_ = not_null;
                }

                do
                {
                    sub0begin = state.cur_;
                    if(access::match(re, state))
                    {
                        access::set_prefix_suffix(what, begin, end);
                        return true;
                    }

                    // handle partial matches
                    else if(partial_ok && state.found_partial_match_)
                    {
                        return state.set_partial_match(), true;
                    }

                    BOOST_ASSERT(state.cur_ == sub0begin);
                    state.flags_.match_not_null_ = not_null;
                }
                while(state.cur_ != state.end_ && (++state.cur_, find(state)));
            }
        }

        // Otherwise, use brute force search at every position.
        else
        {
            for(;;)
            {
                if(access::match(re, state))
                {
                    access::set_prefix_suffix(what, begin, end);
                    return true;
                }

                // handle partial matches
                else if(partial_ok && state.found_partial_match_)
                {
                    return state.set_partial_match(), true;
                }

                else if(end == sub0begin)
                {
                    break;
                }

                BOOST_ASSERT(state.cur_ == sub0begin);
                state.cur_ = ++sub0begin;
                state.flags_.match_not_null_ = not_null;
            }
        }
    }

    access::reset(what);
    return false;
}
} // namespace detail


/// \brief Determines whether there is some sub-sequence within [begin,end) that matches the regular expression re.
///
/// Determines whether there is some sub-sequence within [begin,end) that matches the regular expression re.
///
/// \pre Types BidiIterT and OtherBidiIterT meet the requirements of a Bidirectional Iterator (24.1.4).
/// \pre OtherBidiIterT is convertible to BidiIterT.
/// \pre [begin,end) denotes a valid iterator range.
/// \param begin The beginning of the sequence
/// \param end The end of the sequence
/// \param what The match_results struct into which the sub_matches will be written
/// \param re The regular expression object to use
/// \param flags Optional match flags, used to control how the expression is matched against the sequence. (See match_flag_type.)
/// \return true if a match is found, false otherwise
/// \throw regex_error on stack exhaustion
template<typename OtherBidiIterT, typename BidiIterT>
inline bool regex_search
(
    OtherBidiIterT begin
  , OtherBidiIterT end
  , match_results<BidiIterT> &what
  , basic_regex<BidiIterT> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    typedef detail::core_access<BidiIterT> access;

    // an invlid regex matches nothing
    if(!access::invalid(re))
    {
        // the state object holds matching state and
        // is passed by reference to all the matchers
        detail::state_type<BidiIterT> state(begin, end, what, re, flags);
        return detail::regex_search_impl(state, re);
    }

    access::reset(what);
    return false;
}

/// \overload
template<typename OtherBidiIterT, typename BidiIterT>
inline bool regex_search
(
    OtherBidiIterT begin
  , OtherBidiIterT end
  , basic_regex<BidiIterT> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    match_results<BidiIterT> what;
    return regex_search(begin, end, what, re, flags);
}

/// \overload
template<typename CharT>
inline bool regex_search
(
    CharT const *begin
  , match_results<CharT const*> &what
  , basic_regex<CharT const*> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    CharT const *end = begin + std::char_traits<CharT>::length(begin);
    return regex_search(begin, end, what, re, flags);
}

/// \overload
template<typename CharT, typename TraitsT, typename AllocT>
inline bool regex_search
(
    std::basic_string<CharT, TraitsT, AllocT> const &str
  , match_results<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> &what
  , basic_regex<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    return regex_search(str.begin(), str.end(), what, re, flags);
}

/// \overload
template<typename CharT>
inline bool regex_search
(
    CharT const *begin
  , basic_regex<CharT const *> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    match_results<CharT const *> what;
    return regex_search(begin, what, re, flags);
}

/// \overload
template<typename CharT, typename TraitsT, typename AllocT>
inline bool regex_search
(
    std::basic_string<CharT, TraitsT, AllocT> const &str
  , basic_regex<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    // BUGBUG this is inefficient
    match_results<typename std::basic_string<CharT, TraitsT, AllocT>::const_iterator> what;
    return regex_search(str, what, re, flags);
}


///////////////////////////////////////////////////////////////////////////////
// regex_replace
///////////////////////////////////////////////////////////////////////////////


/// \brief Build an output sequence given an input sequence, a regex, and a format string.
///
/// Constructs a regex_iterator object: regex_iterator\< BidiIterT \> i(begin, end, re, flags),
/// and uses i to enumerate through all of the matches m of type match_results\< BidiIterT \> that
/// occur within the sequence [begin, end). If no such matches are found and !(flags \& format_no_copy)
/// then calls std::copy(begin, end, out). Otherwise, for each match found, if !(flags \& format_no_copy)
/// calls std::copy(m.prefix().first, m.prefix().last, out), and then calls m.format(out, fmt, flags).
/// Finally if !(flags \& format_no_copy) calls std::copy(last_m.suffix().first, last_m.suffix().last, out)
/// where last_m is a copy of the last match found. If flags \& format_first_only is non-zero then only
/// the first match found is replaced.
///
/// \pre Types BidiIterT and OtherBidiIterT meet the requirements of a Bidirectional Iterator (24.1.4).
/// \pre Type OutIterT meets the requirements of an Output Iterator (24.1.2).
/// \pre OtherBidiIterT is convertible to BidiIterT.
/// \pre [begin,end) denotes a valid iterator range.
///
/// \param out An output iterator into which the output sequence is written.
/// \param begin The beginning of the input sequence.
/// \param end The end of the input sequence.
/// \param re The regular expression object to use.
/// \param fmt The format string used to format the replacement sequence.
/// \param flags Optional match flags, used to control how the expression is matched against the sequence. (See match_flag_type.)
/// \return The value of the output iterator after the output sequence has been written to it.
/// \throw regex_error on stack exhaustion or invalid format string.
template<typename OutIterT, typename OtherBidiIterT, typename BidiIterT>
inline OutIterT regex_replace
(
    OutIterT out
  , OtherBidiIterT begin
  , OtherBidiIterT end
  , basic_regex<BidiIterT> const &re
  , std::basic_string<typename iterator_value<BidiIterT>::type> const &fmt
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    using namespace regex_constants;

    match_results<BidiIterT> what;
    BidiIterT cur = begin;
    detail::state_type<BidiIterT> state(begin, end, what, re, flags);
    bool const yes_copy = (0 == (flags & format_no_copy));

    if(detail::regex_search_impl(state, re))
    {
        if(yes_copy)
        {
            out = std::copy(cur, what[0].first, out);
        }

        out = what.format(out, fmt, flags);
        cur = state.cur_ = what[0].second;

        if(0 == (flags & format_first_only))
        {
            bool not_null = (0 == what.length());
            state.reset(what, re);
            while(detail::regex_search_impl(state, re, not_null))
            {
                if(yes_copy)
                {
                    out = std::copy(cur, what[0].first, out);
                }

                out = what.format(out, fmt, flags);
                cur = state.cur_ = what[0].second;
                not_null = (0 == what.length());
                state.reset(what, re);
            }
        }
    }

    if(yes_copy)
    {
        out = std::copy(cur, static_cast<BidiIterT>(end), out);
    }

    return out;
}

/// \overload
template<typename CharT>
inline std::basic_string<CharT> regex_replace
(
    std::basic_string<CharT> const &str
  , basic_regex<typename std::basic_string<CharT>::const_iterator> const &re
  , std::basic_string<CharT> const &fmt
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    std::basic_string<CharT> result;
    result.reserve(fmt.length() * 2);
    regex_replace(std::back_inserter(result), str.begin(), str.end(), re, fmt, flags);
    return result;
}


}} // namespace boost::xpressive

#endif
