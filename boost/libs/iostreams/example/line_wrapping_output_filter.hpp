// 
// Adapted by Jonathan Turkanis from James Kanze's LineWrappingInserter.hh. See
// http://www.gabi-soft.fr/codebase-en.html. The original copyright notice 
// follows.
// 

// See http://www.boost.org/libs/iostreams for documentation.

/****************************************************************************/
/*  File:       LineWrappingInserter.hh                                     */
/*  Author:     J. Kanze                                                    */
/*  Date:       06/11/1997                                                  */
/*      Copyright (c) 1997 James Kanze                                      */
/* ------------------------------------------------------------------------ */


//      line_wrapping_output_filter:
//      =====================
//
//      Wrap lines in output.  This class will automatically insert a
//      '\n' anytime the line extends beyond a predefined point.  It
//      does this very naïvely, however, breaking the line in the
//      middle of a word, for example, and is really only adequate as
//      an example -- a production class would require something more
//      complicated.
//
//      Unix line-breaks are assumed.
//

#ifndef BOOST_IOSTREAMS_EXAMPLE_LINE_WRAPPING_OUTPUT_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_EXAMPLE_LINE_WRAPPING_OUTPUT_FILTER_HPP_INCLUDED

#include <boost/iostreams/concepts.hpp>    // output_filter.
#include <boost/iostreams/operations.hpp>  // boost::iostreams::put.

namespace boost { namespace iostreams { namespace example {

class line_wrapping_output_filter : public output_filter {
public:
    explicit line_wrapping_output_filter(int line_length = 80)
        : line_length_(line_length), col_no_(0) { }

    template<typename Sink>
    void put(Sink& dest, int c) 
        {
            if (c == '\n') 
                col_no_ = 0;
            else {
                if (col_no_ >= line_length_) 
                    this->put(dest, '\n');
                ++col_no_;
            }
            boost::iostreams::put(dest, c);
        }

    template<typename Sink>
    void close(Sink& dest) { boost::iostreams::put(dest, '\n'); col_no_ = 0; }
private:
    int  line_length_;
    int  col_no_;
};

} } }       // End namespaces example, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_EXAMPLE_LINE_WRAPPING_OUTPUT_FILTER_HPP_INCLUDED
