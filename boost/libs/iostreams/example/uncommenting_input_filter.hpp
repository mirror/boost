//
// Adapted by Jonathan Turkanis from James Kanze's ExpandTabsInserter.hh.
// See http://www.gabi-soft.fr/codebase-en.html. The original copyright notice
// follows.
//

// See http://www.boost.org/libs/iostreams for documentation.


/****************************************************************************/
/*  File:       UncommentExtractor.hh                                       */
/*  Author:     J. Kanze                                                    */
/*  Date:       03/10/1997                                                  */
/*      Copyright (c) 1997 James Kanze                                      */
/* ------------------------------------------------------------------------ */

//      uncommenting_input_filter:
//      ----------------------
//
//      Strip comments from input. In this case, a comment starts with
//      the designated character, and terminates at end of line; it
//      cannot handle C nor C++ style comments, but is useful for
//      shell style comments.
//
//      This is a particularly useful class, since ALL configuration
//      file should support comments, and most configuration file
//      syntaxes are too simple to justify anything sophisticated in
//      the line of scanners.
//

#ifndef BOOST_IOSTREAMS_EXAMPLE_UNCOMMENTING_INPUT_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_EXAMPLE_UNCOMMENTING_INPUT_FILTER_HPP_INCLUDED

#include <cstdio>
#include <boost/iostreams/concepts.hpp>    // input_filter.
#include <boost/iostreams/operations.hpp>  // boost::iostreams::get.

namespace boost { namespace iostreams { namespace example {

class uncommenting_input_filter : public input_filter {
public:
    explicit uncommenting_input_filter(char comment_char = '#')
        : comment_char_(comment_char) { }

    template<typename Source>
    int get(Source& src)
        {
            int c = boost::iostreams::get(src);
            if (c == comment_char_)
                while (c != EOF && c != '\n')
                    c = boost::iostreams::get(src);
            return c;
        }
private:
    char comment_char_;
};

} } }       // End namespaces example, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_EXAMPLE_UNCOMMENTING_INPUT_FILTER_HPP_INCLUDED
