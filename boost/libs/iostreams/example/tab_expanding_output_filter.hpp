// 
// Adapted by Jonathan Turkanis and Rob Steward from James Kanze's 
// ExpandTabsInserter.hh. See http://www.gabi-soft.fr/codebase-en.html. 
// The original copyright notice follows.
// 

// See http://www.boost.org/libs/iostreams for documentation.

/****************************************************************************/
/*  File:       ExpandTabsInserter.hh                                       */
/*  Author:     J. Kanze                                                    */
/*  Date:       06/11/1997                                                  */
/*      Copyright (c) 1997 James Kanze                                      */
/* ------------------------------------------------------------------------ */

//      tab_expanding_output_filter:
//      ===================
//
//      Expand tabs in output. Unix line-breaks are assumed.
//
//

#ifndef BOOST_IOSTREAMS_EXAMPLE_TAB_EXPANDING_OUTPUT_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_EXAMPLE_TAB_EXPANDING_OUTPUT_FILTER_HPP_INCLUDED

#include <boost/iostreams/concepts.hpp>      // output_filter.
#include <boost/iostreams/operations.hpp>    // boost::iostreams::put.

namespace boost { namespace iostreams { namespace example {

class tab_expanding_output_filter : public output_filter {
public:
    explicit tab_expanding_output_filter(int tab_size = 8)
        : tab_size_(tab_size), col_no_(0) 
    { assert(tab_size > 0); }

    template<typename Sink>
    void put(Sink& dest, int c)
        {
            if (c == '\t')
            {
                int count = tab_size_ - (col_no_ % tab_size_);
                for (; count > 0; --count)
                {
                    put_char(dest, ' ');
                }
            }
            else
            {
                put_char(dest, c);
            }
        }

    template<typename Sink>
    void close(Sink&) { col_no_ = 0; }
private:
    template<typename Sink>
    void put_char(Sink & dest, int c)
    {
       boost::iostreams::put(dest, c);
       if (c == '\n')
       {
          col_no_ = 0;
       }
       else
       {
          ++col_no_;
       }
    }
    int  tab_size_;
    int  col_no_;
};

} } }       // End namespaces example, iostreams, boost.

#endif      // #ifndef BOOST_IOSTREAMS_EXAMPLE_TAB_EXPANDING_OUTPUT_FILTER_HPP_INCLUDED
