// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED

#include <boost/config.hpp>                  // make sure ptrdiff_t is in std.
#include <algorithm>                         // copy, min.
#include <cstddef>                           // ptrdiff_t.
#include <iosfwd>                            // streamsize.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/assert_convertible.hpp>    
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/traits.hpp>       // io_mode.
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_trats/is_convertible.hpp>    

namespace boost { namespace iostreams { namespace detail {

template<typename Direct>
class direct_adapter {
public:
    typedef typename Direct::value_type char_type;
    struct io_category 
        : io_mode<Direct>::type,
          device_tag,
          closable_tag,
          localizable_tag
        { };
    direct_adapter(const Direct& d);
    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek( std::streamoff, std::ios::seekdir,
                         std::ios::openmode = std::ios::in | std::ios::out );
    void close();
    void close(std::ios_base::openmode which);
    void imbue(const std::locale&);
private:
    typedef is_convertible<io_category, two_sequence> is_double;
    struct pointers {
        char_type *beg, *ptr, *end;
    };
    void init_input(mpl::true_);
    void init_input(mpl::false_) { }
    void init_output(mpl::true_);
    void init_output(mpl::false_) { }
    double_object<pointers, is_double>  ptrs_;
    Direct                              d_;
};

//--------------Implementation of direct_adapter------------------------------//

template<typename Direct>
direct_adapter<Direct>::direct_adapter(const Direct& d) : d_(d)
{
    init_input(is_convertible<io_category, input>());
    init_output(is_convertible<io_category, output>());
}

template<typename Direct>
inline std::streamsize direct_adapter<Direct>::read
    (char_type* s, std::streamsize n)
{
    using namespace std;
    pointers& get = ptrs_.first();
    streamsize avail = 
        static_cast<streamsize>(get.end - get.ptr);
    streamsize result = std::min(n, avail);
    std::copy(get.ptr, get.ptr + result, s);
    get.ptr += result;
    return result;
}

template<typename Direct>
inline void direct_adapter<Direct>::write
    (const char_type* s, std::streamsize n)
{
    using namespace std;
    pointers& put = ptrs_.second();
    streamsize capacity = 
        static_cast<streamsize>(put.end - put.ptr);
    streamsize amt = std::min(n, avail);
    std::copy(s, s + amt, put.ptr);
    put.ptr += amt;
}

template<typename Direct>
inline std::streamoff direct_adapter<Direct>::seek
    ( std::streamoff off, std::ios::seekdir way, 
      std::ios::openmode which )
{
    using namespace std;
    pointers& get = impl_.first();
    pointers& put = impl_.second();
    if (way == ios::cur && get.ptr != put.ptr)
       bad_seek();
    if ((which & ios::in) || !is_double::value) {
        ptrdiff_t next;
        switch (way) {
        case ios::beg:
            next = off; 
            break;
        case ios::cur:
            next = get.ptr - get.begin + off; 
            break;
        case ios::end: 
            next = get.end - get.begin + off; 
            break;
        }
        if (next >= 0 && next < get.end - get.begin)
            get.ptr = get.beg + next;
        else
            bad_seek();
    }
    if ((which & ios::out) && is_double::value) {
        ptrdiff_t next;
        switch (way) {
        case ios::beg:
            next = off; 
            break;
        case ios::cur:
            next = put.ptr - put.begin + off; 
            break;
        case ios::end: 
            next = put.end - put.begin + off; 
            break;
        }
        if (next >= 0 && next < put.end - put.begin)
            put.ptr = put.beg + next;
        else
            bad_seek();
    }
    return static_cast<std::streamoff>((which & ios::in) ? get.ptr : put.ptr);
}

template<typename Direct>
void direct_adapter<Direct>::close() 
{ 
    BOOST_IOSTREAMS_ASSERT_NOT_CONVERTIBLE(io_category, two_sequence); 
    boost::iostreams::close(*d_, std::ios::in | std::ios::out);
}

template<typename Direct>
void direct_adapter<Direct>::close(std::ios_base::openmode which) 
{ 
    BOOST_IOSTREAMS_ASSERT_CONVERTIBLE(io_category, two_sequence); 
    boost::iostreams::close(*d_, which);
}

template<typename Direct>
void direct_adapter<Direct>::imbue(const std::locale&) 
{ boost::iostreams::imbue(*d_); }

template<typename Direct>
void direct_adapter<Direct>::init_input(mpl::true_) 
{
    std::pair<char_type*, char_type*> seq = iostreams::input_sequence(*d_);
    ptrs_.first().beg = seq.first;
    ptrs_.first().ptr = seq.first;
    ptrs_.first().end = seq.second;
}

template<typename Direct>
void direct_adapter<Direct>::init_output(mpl::true_) 
{
    std::pair<char_type*, char_type*> seq = iostreams::output_sequence(*d_);
    ptrs_.second().beg = seq.first;
    ptrs_.second().ptr = seq.first;
    ptrs_.second().end = seq.second;
}

template<typename Direct>
void direct_adapter<Direct>::bad_seek()
{ throw std::ios::failure("bad seek"); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED
