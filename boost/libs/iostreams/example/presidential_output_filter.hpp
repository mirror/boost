// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_EXAMPLE_PRESIDENTIAL_OUTPUT_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_EXAMPLE_PRESIDENTIAL_OUTPUT_FILTER_HPP_INCLUDED

#include <ctype.h>                         // isalpha.
#include <string>
#include <boost/iostreams/concepts.hpp>    // output_filter.
#include <boost/iostreams/operations.hpp>  // boost::iostreams::put.

namespace boost { namespace iostreams { namespace example {

//
// Class name: presidential_output_filter
// Description: OutputFilter which performs the substitutions:
//      
//        subliminable      ->  subliminal
//        nucular           ->  nuclear
//        malfeance         ->  malfeasance
//        misunderestimate  ->  underestimate
//
// Note: See usenet_input_filter.hpp for a similar example which uses a
// a std::map to store associations.
//
class presidential_output_filter : public output_filter {
public:
    template<typename Sink>
    void put(Sink& dest, int c)
        {
            if (isalpha(c)) 
                current_word_ += (char) c;
            else {
                if (!current_word_.empty()) {
                    std::string sub = substitute(current_word_);
                    write( dest, sub.data(), 
                           (std::streamsize) sub.size() );
                }
                boost::iostreams::put(dest, c);
                current_word_.erase();
            }
        }

    template<typename Sink>
    void close(Sink& dest)
        {
            std::string sub = substitute(current_word_);
            write(dest, sub.data(),(std::streamsize) sub.size());
            current_word_.erase();
        }
    static std::string substitute(const std::string& word)
        {
            if (word == "subliminable")
                return "subliminal";
            else if (word == "nucular")
                return "nuclear";
            else if (word == "malfeance")
                return "malfeasance";
            else if (word == "misunderestimate")
                return "underestimate";
            else
                return word;
        }
private:
    std::string current_word_;
};

} } }       // End namespaces example, iostreams, boost.

#endif      // #ifndef BOOST_IOSTREAMS_EXAMPLE_PRESIDENTIAL_OUTPUT_FILTER_HPP_INCLUDED
