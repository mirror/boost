// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <algorithm>                               // min.
#include <cassert>
#include <memory>                                  // allocator.
#include <string>
#include <boost/config.hpp>                        // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/closer.hpp>
#include <boost/iostreams/detail/ios.hpp>          // openmode, streamsize.
#include <boost/iostreams/detail/newline.hpp>

#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1 C4244.

namespace boost { namespace iostreams {

//
// Template name: line_filter.
// Template paramters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Filter which processes data one line at a time.
//
template<typename Ch, typename Alloc = std::allocator<Ch> >
class basic_line_filter  {
public:
    typedef Ch                                         char_type;
    typedef BOOST_IOSTREAMS_CHAR_TRAITS(Ch)            traits_type;
    typedef std::basic_string<Ch, traits_type, Alloc>  string_type;
    struct io_category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    basic_line_filter() : state_(0) { }
    virtual ~basic_line_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        assert(!(state_ & f_write));
        state_ |= f_read;

        streamsize result = 0;
        if (!cur_line_.empty() && (result = read_line(s, n)) == n)
            return n;

        bool not_done = true;
        while (result < n && not_done) {
            not_done = next_line(src);
            result += read_line(s + result, n - result);
        }

        return result;
    }

    template<typename Sink>
    void write(Sink& snk, const char_type* s, std::streamsize n)
    {
        using namespace std;
        assert(!(state_ & f_read));
        state_ |= f_write;

        const char_type *cur = s, *next;
        while (true) {
            typename string_type::size_type rest = n - (cur - s);
            if ((next = traits_type::find(cur, rest, newline()))) {
                cur_line_.append(cur, next - cur);
                cur = next + 1;
                write_line(snk);
            } else {
                cur_line_.append(cur, rest);
                return;
            }
        }
    }

    typedef basic_line_filter<Ch, Alloc> self;
    friend struct detail::closer<self>;

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        if ((state_ & f_read) && (which & BOOST_IOS::in))
            close();

        if ((state_ & f_write) && (which & BOOST_IOS::out)) {
            detail::closer<self> closer(*this);
            if (!cur_line_.empty())
                write_line(snk);
        }
    }
private:
    virtual string_type do_filter(const string_type& line) = 0;

    std::streamsize read_line(char_type* s, std::streamsize n)
    {
        using namespace std;
        streamsize result =
            (std::min) (n, static_cast<streamsize>(cur_line_.size()));
        traits_type::copy(s, cur_line_.data(), result);
        cur_line_.erase(0, result);
        return result;
    }

    template<typename Source>
    bool next_line(Source& src)
    {
        using namespace std;
        typename traits_type::int_type c;
        while (!is_eof(c = iostreams::get(src)) && c != newline())
            cur_line_ += traits_type::to_int_type(c);
        cur_line_ = do_filter(cur_line_);
        if (c == newline())
            cur_line_ += newline();
        return c == newline();
    }

    template<typename Sink>
    void write_line(Sink& snk)
    {
        using namespace std;
        string_type line = do_filter(cur_line_) + newline();
        iostreams::write(snk, line.data(), static_cast<streamsize>(line.size()));
        clear();
    }

    bool is_eof(typename traits_type::int_type c)
    {
        return traits_type::eq_int_type(c, traits_type::eof());
    }

    Ch newline() const { return detail::newline<Ch>::value; }

    void close()
    {
        clear();
        state_ = 0;
    }

    void clear()
    {
    #if (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
        cur_line_ = string_type();
    #else
        cur_line_.clear();
    #endif
    }

    enum {
        f_read   = 1,
        f_write  = f_read << 1
    };

    string_type  cur_line_;
    int          state_;
};

typedef basic_line_filter<char>     line_filter;
typedef basic_line_filter<wchar_t>  wline_filter;

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED
