// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_REVERSE_HPP_INCLUDED
#define BOOST_IOSTREAMS_REVERSE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <algorithm>                             // copy, min.  
#include <deque>                               
#include <memory>                                // allocator.
#include <boost/config.hpp>                      // BOOST_DEDUCED_TYPENAME.       
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/chain.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/one_step_filter.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

template<typename OutputFilter> class reversing_input_filter;
template<typename InputFilter> class reversing_output_filter;

//
// Template name: reversing_input_filter.
// Template paramters:
//      OutputFilter - A model of OutputFilter.
// Description: An InputFilter implemented in terms of a given
//      instance of OutputFilter.
// Note: Implemented using basic_one_step_input_filter for portability; an 
//      implementation with better memory usage caused an ICE on GCC 3.2.
//
template<typename OutputFilter>
class reversing_input_filter
    : public one_step_filter<BOOST_DEDUCED_TYPENAME io_char<OutputFilter>::type>
{
private:
    typedef one_step_filter<
                BOOST_DEDUCED_TYPENAME 
                io_char<OutputFilter>::type
            >                                                   base_type;
public:
    typedef typename base_type::char_type                       char_type;
    typedef typename base_type::category                        category;
    explicit reversing_input_filter(const OutputFilter& filter)
        : filter_(filter) { }
protected:
    typedef typename base_type::vector_type                     vector_type;
    void do_filter(const vector_type& src, vector_type& dest)
        {
            chain<output, char_type> out;
            out.push(filter_);
            out.push(iostreams::back_inserter(dest));
            out.write(&src[0], (std::streamsize) src.size());
        }
private:
    OutputFilter filter_;
};

//
// Template name: reversing_output_filter.
// Template paramters:
//      InputFilter - A model of InputFilter.
// Description: An OutputFilter implemented in terms of a given
//      instance of InputFilter.
// Note: Implemented using basic_one_step_input_filter for reasonable
//      performance in the unbuffered case; an implementation with better
//      memory usage was unbearably slow when used for unbuffered output.
//
template<typename InputFilter>
class reversing_output_filter
    : public one_step_filter<BOOST_DEDUCED_TYPENAME io_char<InputFilter>::type>
{
private:
    typedef one_step_filter<
                BOOST_DEDUCED_TYPENAME 
                io_char<InputFilter>::type
            >                                                   base_type;
public:
    typedef typename base_type::char_type                       char_type;
    typedef typename base_type::category                        category;
    explicit reversing_output_filter(const InputFilter& filter)
        : filter_(filter) { }
protected:
    typedef typename base_type::vector_type                     vector_type;
    void do_filter(const vector_type& src, vector_type& dest)
        {
            chain<input, char_type> in;
            in.push(filter_);
        #if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
            iterator_range< std::vector<char>::iterator >
                range(make_iterator_range(src));
            in.push(range);
        #else                 
            in.push(make_iterator_range(src));
        #endif
            copy(in, iostreams::back_inserter(dest));
        }
private:
    InputFilter filter_;
};

namespace detail {

template<typename Filter>
struct reverse_traits {
    typedef typename
            mpl::if_<
                is_convertible<
                    BOOST_DEDUCED_TYPENAME category_of<Filter>::type, 
                    input
                >,
                reversing_output_filter<Filter>,
                reversing_input_filter<Filter>
            >::type type;
};

} // End namespace detail.

//
// Template name: reverse.
// Template paramters:
//      Filter - A model of InputFilter or OutputFilter.
// Description: Returns an instance of an appropriate specialization of
//      reversing_input_filter or reversing_output_filter.
//
template<typename Filter>
typename detail::reverse_traits<Filter>::type
reverse(const Filter& f)
{ typedef typename detail::reverse_traits<Filter>::type return_type;
  return return_type(f); }
                    
//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_REVERSE_HPP_INCLUDED
