//  html.hpp - HTML format writer and reader header  -------------------------//

//  (C) Copyright Beman Dawes 2001. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice
//  appears in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

//  Revision History
//   31 Jan 01 Initial version (Beman Dawes)

#ifndef BOOST_HTML_HPP
#define BOOST_HTML_HPP

#include <boost/text.hpp>

namespace boost
{

  class html_writer : public text_writer
  {
   public:
    explicit html_writer(std::ostream & strm) : text_writer(strm) {}
    void start_sequence(std::size_t n) { os << "\n<table border=\"1\" cellspacing=\"0\" cellpadding=\"5\">\n"; }
    void start_sequence_element()      { os << " <tr>\n"; }
    void separate_sequence_elements()  {}
    void end_sequence_element()        { os << "\n </tr>\n"; }
    void end_sequence()                { os << "</table>\n"; }
    void start_struct()                {}
    void separate_struct_members()     { os << "\n"; }
    void end_struct()                  {}
    void start_value()                 { os << "  <td>"; }
    void end_value()                   { os << "</td>"; }
  };

/// html_reader to be supplied

}

#endif // BOOST_HTML_HPP
