// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from an example of James Kanze, with suggestions from Peter Dimov.
// See http://www.gabi-soft.fr/codebase-en.html. 

#ifndef BOOST_IOSTREAMS_FINITE_STATE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_FINITE_STATE_FILTER_HPP_INCLUDED

#include <cassert>
#include <cstdio>    // EOF.
#include <iostream>  // cin, cout.
#include <locale>
#include <string>
#include <boost/config.hpp>                // JOIN.
#include <boost/iostreams/categories.hpp>  // Localizable.
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/filter/stdio_filter.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost { namespace iostreams { namespace example {
                    
//------------------Definition of basic character classes---------------------//

#define BOOST_IOSTREAMS_CHARACTER_CLASS(class) \
    struct BOOST_JOIN(is_, class) { \
        template<typename Ch> \
        static bool test(Ch event, const std::locale& loc) \
        { return std::BOOST_JOIN(is, class)(event, loc); } \
    }; \
    /**/

BOOST_IOSTREAMS_CHARACTER_CLASS(alnum)
BOOST_IOSTREAMS_CHARACTER_CLASS(alpha)
BOOST_IOSTREAMS_CHARACTER_CLASS(cntrl)
BOOST_IOSTREAMS_CHARACTER_CLASS(digit)
BOOST_IOSTREAMS_CHARACTER_CLASS(graph)
BOOST_IOSTREAMS_CHARACTER_CLASS(lower)
BOOST_IOSTREAMS_CHARACTER_CLASS(print)
BOOST_IOSTREAMS_CHARACTER_CLASS(punct)
BOOST_IOSTREAMS_CHARACTER_CLASS(space)
BOOST_IOSTREAMS_CHARACTER_CLASS(upper)
BOOST_IOSTREAMS_CHARACTER_CLASS(xdigit)

#undef BOOST_IOSTREAMS_CHARACTER_CLASS

template<wchar_t C>
struct is { 
    template<typename Ch>
    static bool test(Ch event, const std::locale& loc) 
    { 
        return event == C; 
    }
};

struct is_any { 
    template<typename Ch>
    static bool test(Ch event, const std::locale& loc) { return true; }
};

//------------------Definition of base class for finite state filters---------//

template<typename Derived, typename Ch>
class finite_state_filter_base {
public:
    typedef Ch char_type;
    //typedef typename Derived::char_type char_type;
    void imbue(const std::locale& loc) { loc_ = loc; }
    const std::locale& getloc() const { return loc_; }
protected:

    // Template whose instantiations make up transition table.

    template< int State, 
              typename CharacterClass, 
              int NextState, 
              void (Derived::*Action)(char_type) >
    struct rule {
        typedef CharacterClass  character_class;
        static const int        state = State;
        static const int        next_state = NextState;
        static void execute(Derived& d, char event)
        {
            (d.*action)(event);
        }
    };

    // Default event handlers.

    void on_eof() { }
    void on_any() { }

    // Stack interface.

    bool empty() const { return buf_.empty(); }
    void push(char_type c) { buf_ += c; }
    char_type pop() 
    {
        char_type result = buf_[off_++];
        if (off_ == buf_.size()) 
            clear();
        return result;
    }
    void clear()
    { 
        buf_.clear();
        off_ = 0;
    }
private:
    typedef std::basic_string<char_type>     string_type;
    typedef typename string_type::size_type  size_type;
    std::locale  loc_;
    string_type  buf_;
    size_type    off_;
};

//------------------Definition of finite_state_filter_impl--------------------//

template<typename FiniteStateFilter>
class finite_state_filter_impl : protected FiniteStateFilter
{
private:
    //typedef finite_state_filter_base<FiniteStateFilter> base_type;
    //BOOST_STATIC_ASSERT((is_base_and_derived<base_type, FiniteStateFilter>::value));

    template<typename First, typename Last>
    struct process_event_impl;
public:
    typedef typename io_char<FiniteStateFilter>::type char_type;

    finite_state_filter_impl() : state_(FiniteStateFilter::initial_state) { }

    template<typename T0>
    finite_state_filter_impl(const T0& t0)  
        : FiniteStateFilter(t0), state_(FiniteStateFilter::initial_state) 
        { }

    template<typename T0, typename T1>
    finite_state_filter_impl(const T0& t0, const T1& t1) 
        : FiniteStateFilter(t0, t1), state_(FiniteStateFilter::initial_state)
        { }

    template<typename T0, typename T1, typename T2>
    finite_state_filter_impl(const T0& t0, const T1& t1, const T1& t2) 
        : FiniteStateFilter(t0, t1, t2), state_(FiniteStateFilter::initial_state) 
        { }
protected:
    int process_event(char_type c)
    {
        typedef typename FiniteStateFilter::transition_table  transitions;
        typedef typename mpl::begin<transitions>:type         first;
        //typedef typename mpl::end<rules>:type                 last;
        //return process_event_impl<first, last>::execute(*this, state_, c);
        return 0;
    }

    int& state() { return state_; }
private:
    template<typename First, typename Last>
    struct process_event_impl {
        static int execute(FiniteStateFilter& filter, int state, char_type event)
        {
            typedef typename mpl::deref<First>::type     rule;
            typedef typename mpl::next<First>::type      next;
            typedef typename rule_type::character_class  character_class;

            if ( state == rule_type::state && 
                 character_class::test(event, filter.getloc()) )
            {
                // Rule applies.
                rule_type::execute(filter, event);
                return rule_type::next_state;
            }

            // Rule is inapplicable: try next rule.
            return process_event_impl<next, Last>::execute(filter, state, event);
        }
    };

    template<typename Last>
    struct process_event_impl<Last, Last> {
        static int execute(FiniteStateFilter& filter, int state, char_type) 
        { 
            filter.on_any(); // Default action.
            return state; 
        }
    };

    int state_;
};

//------------------Definition of base finite_state_stdio_filter--------------//

template<typename FiniteStateFilter>
class finite_state_stdio_filter 
    : public basic_stdio_filter<typename FiniteStateFilter::char_type>,
      public finite_state_filter_impl<FiniteStateFilter>
{
private:
    typedef finite_state_filter_impl<FiniteStateFilter>  base_type;
public:
    typedef typename base_type::char_type                char_type;
    struct io_category : stdio_filter::io_category, localizable_tag { };

    finite_state_stdio_filter() { }

    template<typename T0>
    finite_state_stdio_filter(const T0& t0) 
        : base_type(t0) 
        { }

    template<typename T0, typename T1>
    finite_state_stdio_filter(const T0& t0, const T1& t1) 
        : base_type(t0, t1) 
        { }

    template<typename T0, typename T1, typename T2>
    finite_state_stdio_filter(const T0& t0, const T1& t1, const T1& t2) 
        : base_type(t0, t1, t2) 
        { }
private:
    void do_filter()
    {
        using namespace std;
        while (true) {
            flush();

            int c;
            if ((c = cin.get()) != EOF)
                process_event((char) c);
            else {
                this->on_eof();
                flush();
                break;
            }
        }
    }
    void do_close() {  
        this->clear(); 
        this->state() = FiniteStateFilter::initial_state;
    }
    void flush() { while (!this->empty()) std::cout.put(this->pop()); }
};

} } }       // End namespaces example, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_FINITE_STATE_FILTER_HPP_INCLUDED
