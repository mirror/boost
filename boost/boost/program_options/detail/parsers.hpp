// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARSERS_HPP_VP_2004_05_06
#define BOOST_PARSERS_HPP_VP_2004_05_06

namespace boost { namespace program_options {

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::options(const options_description& desc)
    {
        m_desc = &desc;
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::positional(
        const positional_options_description& desc)
    {
        m_positional = &desc;
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::style(int style)
    {
        m_style = style;
        return *this;
    }

    template<class charT>
    basic_command_line_parser<charT>& 
    basic_command_line_parser<charT>::extra_parser(ext_parser ext)
    {
        m_ext = ext;
        return *this;
    }

    template<class charT>
    basic_parsed_options<charT>
    parse_command_line(int argc, charT* argv[],
                       const options_description& desc,
                       int style = 0,
                       function1<std::pair<std::string, std::string>, 
                                 const std::string&> ext)
    {
        return basic_command_line_parser<charT>(argc, argv).options(desc).
            style(style).extra_parser(ext).run();
    }

}}

#endif
