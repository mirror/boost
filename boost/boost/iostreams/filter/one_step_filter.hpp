// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ONE_STEP_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_ONE_STEP_FILTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC.

#include <algorithm>                             // copy, min.
#include <cassert>
#include <ios>                                   // openmode.
#include <iterator>                              // back_inserter
#include <vector>
#include <boost/bind.hpp>                        // Used w/ scope_guard.
#include <boost/ref.hpp>                         // Used w/ scope_guard.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/scope_guard.hpp>

namespace boost { namespace iostreams {

//
// Template name: one_step_filter.
// Template paramters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Utility for defining DualUseFilters which filter an
//      entire stream at once. To use, override the protected virtual
//      member do_filter.
// Note: This filter should not be copied while it is in use.
//
template<typename Ch, typename Alloc = std::allocator<Ch> >
class one_step_filter  {
public:
    typedef Ch char_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    one_step_filter() : ptr_(0), state_(0) { }
    virtual ~one_step_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        assert(!(state_ & f_write));
        state_ |= f_read;
        if (!(state_ & f_eof))
            do_read(src);
        streamsize amt =
            std::min(n, static_cast<streamsize>(data_.size() - ptr_));
        std::char_traits<char_type>::copy(s, &data_[ptr_], amt);
        ptr_ += amt;
        return amt;
    }

    template<typename Sink>
    void write(Sink&, const char_type* s, std::streamsize n)
    {
        assert(!(state_ & f_read));
        state_ |= f_write;
        data_.insert(data_.end(), s, s + n);
    }
    
    #include <boost/iostreams/detail/scope_guard_prefix.hpp> // CW workaround
    template<typename Sink>
    void close(Sink& sink, std::ios::openmode which)
    {
        if ((state_ & f_read) && (which & std::ios::in)) 
            close_impl();

        if ((state_ & f_write) && (which & std::ios::out)) {
            typedef one_step_filter<Ch, Alloc> self;
            BOOST_SCOPE_GUARD(boost::bind(&self::close_impl, boost::ref(*this)));
            vector_type filtered;
            do_filter(data_, filtered);
            boost::iostreams::write( 
                sink, &filtered[0],
                static_cast<std::streamsize>(filtered.size())
            );
        }
    }
    #include <boost/iostreams/detail/scope_guard_suffix.hpp>

protected:
    typedef std::vector<Ch, Alloc>        vector_type;
private:
    virtual void do_filter(const vector_type& src, vector_type& dest) = 0;

    template<typename Source>
    void do_read(Source& src)
    {
        Ch buf[default_buffer_size];
        vector_type data;
        while (true) {
            std::streamsize n = 
                boost::iostreams::read(src, buf, default_buffer_size);
            data.insert(data.end(), buf, buf + n);
            if (n < default_buffer_size) break;
        }
        do_filter(data, data_);
        state_ |= f_eof;
    }

    void close_impl()
    {
        data_.clear();
        ptr_ = 0;
        state_ = 0;
    }

    enum {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1
    };

    // Note: typically will not be copied while vector contains data.
    vector_type      data_;
    std::streamsize  ptr_;
    int              state_;
};

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_ONE_STEP_FILTER_HPP_INCLUDED
