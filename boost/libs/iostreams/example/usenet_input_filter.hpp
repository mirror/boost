// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_EXAMPLE_USENET_INPUT_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_EXAMPLE_USENET_INPUT_FILTER_HPP_INCLUDED

#include <algorithm>                // copy.
#include <cstdio>                   // EOF.
#include <ctype.h>                  // isalpha.
#include <map>
#include <string>
#include <vector>
#include <boost/iostreams/concepts.hpp>    // input_filter.
#include <boost/iostreams/operations.hpp>  // boost::iostreams::get.

namespace boost { namespace iostreams { namespace example {

//
// Class name: usenet_input_filter.
// Description: InputFilter which expands some common usenet abbreviations.
//      Does not attempt to capitalize the replacement text correctly.
//      See The Jargon File, at http://catb.org/~esr/jargon/html/index.html.
//
class usenet_input_filter : public input_filter {
public:
    usenet_input_filter() : off_(0), eof_(false)
        {
            dictionary_["AFAIK"] =  "as far as I know";
            dictionary_["HAND"] =   "have a nice day";
            dictionary_["HTH"] =    "hope this helps";
            dictionary_["IIRC"] =   "if I recall correctly";
            dictionary_["IMO"] =    "in my opinion";
            dictionary_["IMHO"] =   "in my humble opinion";
            dictionary_["OTOH"] =   "on the other hand";
            dictionary_["RTFM"] =   "consult the documentation";
            dictionary_["STFW"] =   "try Google";
        }
    template<typename Source>
    int get(Source& src)
        {   
            // Handle unfinished business.
            if (eof_) 
                return EOF;
            if (off_ < current_word_.size()) 
                return current_word_[off_++];

            // Compute curent word.
            current_word_.clear();
            while (true) {
                int c;
                if ((c = boost::iostreams::get(src)) == EOF) {
                    eof_ = true;
                    if (current_word_.empty())
                        return EOF;
                    else
                        break;
                } else if (isalpha(c)) {
                    current_word_.push_back(c);
                } else { 

                    // Look up current word in dictionary.
                    map_type::iterator it = 
                        dictionary_.find(current_word_);
                    if (it != dictionary_.end()) 
                        current_word_ = it->second;
                    current_word_.push_back(c);
                    off_ = 0;
                    break;
                }
            }

            return this->get(src); // Note: current_word_ is not empty.
        }

    template<typename Source>
    void close(Source&) 
        { 
            current_word_.clear(); 
            off_ = 0;
            eof_ = false;
        }
private:
    typedef std::map<std::string, std::string> map_type;
    map_type                dictionary_;
    std::string             current_word_;
    std::string::size_type  off_;
    bool                    eof_;
};

} } }       // End namespaces example, iostreams, boost.

#endif      // #ifndef BOOST_IOSTREAMS_EXAMPLE_USENET_INPUT_FILTER_HPP_INCLUDED
