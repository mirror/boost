// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_FORWARD_CONTAINER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FORWARD_CONTAINER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/categories.hpp>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Container, typename Mode>
class forward_container {
public:
    BOOST_STATIC_ASSERT((!is_convertible<Mode, random_access>::value));
    typedef Container                       container_type;
    typedef typename Container::value_type  char_type;
    struct category 
        : device_tag,
          Mode
        { };
    forward_container(Container* cnt, bool owns)
        : pimpl_(new impl(cnt, owns)) 
        { }
    std::streamsize read(char_type* s, std::streamsize n)
    {
        BOOST_STATIC_ASSERT((is_convertible<Mode, input>::value));
        iterator        last   = cnt().end();
        std::streamsize result = 0;
        while (pimpl_->ptr_ != last && result < n) {
            *s++ = *pimpl_->ptr_++;
            ++result;
        }
        return result != 0 ? result : -1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    {
        BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
        const char_type* s_end = s + n;
        iterator         p_end = cnt().end();
        while (pimpl_->ptr_ != p_end && s != s_end)
            *pimpl_->ptr_++ = *s++;
        if (s != s_end) {
            cnt().insert(cnt().end(), s, s_end);
            pimpl_->ptr_ = cnt().end();
        }
        return n;
    }
    Container container() const { return *pimpl_->cnt_; }
    void container(const Container& cnt)
    { 
        shared_ptr<impl> pimpl(new impl(new Container(cnt), true));
        pimpl_.swap(pimpl);
    }
private:
    Container& cnt() { return *pimpl_->cnt_; }
    typedef typename Container::iterator iterator;
    struct impl {
        impl(Container* cnt, bool owns) 
            : cnt_(cnt), owns_(owns), ptr_(cnt->begin()) { }
        ~impl() { if (owns_) delete cnt_; }
        Container*  cnt_;
        bool        owns_;
        iterator    ptr_;
    };
    shared_ptr<impl> pimpl_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FORWARD_CONTAINER_HPP_INCLUDED
