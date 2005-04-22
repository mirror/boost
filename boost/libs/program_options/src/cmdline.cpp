// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_PROGRAM_OPTIONS_SOURCE
#include <boost/program_options/config.hpp>

#include <boost/config.hpp>

#include <boost/program_options/detail/cmdline.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/throw_exception.hpp>

#include <boost/bind.hpp>

#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <cstring>
#include <cctype>

#include <cstdio>

#include <iostream>

namespace boost { namespace program_options {

    using namespace std;
    using namespace boost::program_options::command_line_style;
    
    invalid_command_line_syntax::
    invalid_command_line_syntax(const std::string& tokens, kind_t kind)
    : invalid_syntax(tokens, error_message(kind)), m_kind(kind)
    {}

    std::string 
    invalid_command_line_syntax::error_message(kind_t kind)
    {
        // Initially, store the message in 'const char*' variable,
        // to avoid conversion to std::string in all cases.
        const char* msg;
        switch(kind)
        {
        case long_not_allowed:
            msg = "long options are not allowed";
            break;
        case long_adjacent_not_allowed:
            msg = "parameters adjacent to long options not allowed";
            break;
        case short_adjacent_not_allowed:
            msg = "parameters adjust to short options are not allowed";
            break;
        case empty_adjacent_parameter:
            msg = "adjacent parameter is empty";
            break;
        case missing_parameter:
            msg = "required parameter is missing";
            break;
        case extra_parameter:
            msg = "extra parameter";
            break;
        default:
            msg = "unknown error";
        }
        return msg;
    }

    invalid_command_line_syntax::kind_t 
    invalid_command_line_syntax::kind() const
    {
        return m_kind;
    }


}}


namespace boost { namespace program_options { namespace detail {

    // vc6 needs this, but borland chokes when this is added.
#if BOOST_WORKAROUND(_MSC_VER, <= 1200)
    using namespace std;
    using namespace program_options;
#endif


    cmdline::cmdline(const std::vector<std::string>& args, int style,
                     bool allow_unregistered)
    {
        init(args, style, allow_unregistered);
    }

    cmdline::cmdline(int argc, const char*const * argv, int style,
                     bool allow_unregistered)
    {
#if defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
        vector<string> args;
        copy(argv+1, argv+argc, inserter(args, args.end()));
        init(args, style, allow_unregistered);
#else
        init(vector<string>(argv+1, argv+argc), style, allow_unregistered);
#endif
    }

    void
    cmdline::init(const std::vector<std::string>& args, int style,
                  bool allow_unregistered)
    {
        if (style == 0) 
            style = default_style;        

        check_style(style);

        this->args = args;        
        this->style = style_t(style);
        this->allow_unregistered = allow_unregistered,

        m_desc = 0;
    }

    void 
    cmdline::check_style(int style) const
    {
        bool allow_some_long = 
            (style & allow_long) || (style & allow_long_disguise);

        const char* error = 0;
        if (allow_some_long && 
            !(style & long_allow_adjacent) && !(style & long_allow_next))
            error = "style disallows parameters for long options";

        if (!error && (style & allow_short) &&
            !(style & short_allow_adjacent) && !(style & short_allow_next))
            error = "style disallows parameters for short options";

        if (!error && (style & allow_short) &&
            !(style & allow_dash_for_short) && !(style & allow_slash_for_short))
            error = "style disallows all characters for short options";

        if (error)
            throw_exception(invalid_command_line_style(error));

        // Need to check that if guessing and long disguise are enabled
        // -f will mean the same as -foo
    }

    void 
    cmdline::set_options_description(const options_description& desc)
    {
        m_desc = &desc;
    }

    vector<option>
    cmdline::run()
    {
        // The parsing is done by having a set of 'style parsers'
        // and trying then in order. Each 'style parser' can:
        // - return a vector<option>
        // - consume some input
        //
        // When some 'style parser' consumes some input 
        // we start with the first style parser. 

        vector<style_parser> style_parsers;      
        if (style & allow_long)
            style_parsers.push_back(
                bind(&cmdline::parse_long_option, this, _1));

        if ((style & allow_long_disguise))
            style_parsers.push_back(
                bind(&cmdline::parse_disguised_long_option, this, _1));

        if ((style & allow_short) && (style & allow_dash_for_short))
            style_parsers.push_back(
                bind(&cmdline::parse_short_option, this, _1));

        if ((style & allow_short) && (style & allow_slash_for_short))
            style_parsers.push_back(bind(&cmdline::parse_dos_option, this, _1));

        style_parsers.push_back(bind(&cmdline::parse_terminator, this, _1));

        vector<option> result;
        while(!args.empty())
        {
            bool ok = false;
            for(unsigned i = 0; i < style_parsers.size(); ++i)
            {
                unsigned current_size = args.size();
                vector<option> next = style_parsers[i](args);
                for (unsigned j = 0; j < next.size(); ++j)
                    result.push_back(next[j]);

                if (args.size() != current_size) {
                    ok = true;
                    break;                
                }
            }
            
            if (!ok) {
                option opt;
                opt.value.push_back(args[0]);
                result.push_back(opt);
                args.erase(args.begin());
            }
        }
        // Assign position keys to positional options.
        int position_key = 0;
        for(unsigned i = 0; i < result.size(); ++i) {
            if (result[i].string_key.empty())
                result[i].position_key = position_key++;
        }

        return result;
    }

    std::vector<option> 
    cmdline::parse_option(const std::string& name,
                          const std::string& adjacent_value,                         
                          vector<string>& other_tokens)
    {                                    
        std::vector<option> result;

        // TODO: case-sensitivity.
        const option_description& d = 
            m_desc->find(name, (style & allow_guessing));

        option opt;
        opt.string_key = d.key(name);

        // We check that the min/max number of tokens for the option
        // agrees with the number of tokens we have. The 'adjacent_value'
        // (the value in --foo=1) counts as a separate token, and if present
        // must be consumed. The following tokens on the command line may be
        // left unconsumed.

        // We don't check if those tokens look like option, or not!

        unsigned min_tokens = d.semantic()->min_tokens();
        unsigned max_tokens = d.semantic()->max_tokens();
        
        unsigned present_tokens = other_tokens.size() 
            + int(!adjacent_value.empty());
        
        if (present_tokens >= min_tokens)
        {
            if (!adjacent_value.empty() && max_tokens == 0) {
                throw_exception(invalid_command_line_syntax(name,
                    invalid_command_line_syntax::extra_parameter));                                                                
            }

            // Everything's OK, move the values to the result.
            if (!adjacent_value.empty())
            {
                opt.value.push_back(adjacent_value);
                --min_tokens;
                --max_tokens;
            }
            else if (min_tokens == 0 && max_tokens == 1)
            {
                // hack to handle implicit options.
                max_tokens = 0;
            }

            
            for(;!other_tokens.empty() && max_tokens--; ) {
                opt.value.push_back(other_tokens[0]);
                other_tokens.erase(other_tokens.begin());
            }
        }
        else
        {
            throw_exception(invalid_command_line_syntax(name,
                invalid_command_line_syntax::missing_parameter));                                                                

        }
        result.push_back(opt);
        return result;
    }

    std::vector<option> 
    cmdline::parse_long_option(std::vector<string>& args)
    {
        const std::string& tok = args[0];
        if (tok.size() >= 3 && tok[0] == '-' && tok[1] == '-')
        {   
            string name, adjacent;

            unsigned p = tok.find('=');
            if (p != tok.npos)
            {
                name = tok.substr(2, p-2);
                adjacent = tok.substr(p+1);
                if (adjacent.empty())
                    throw_exception(invalid_command_line_syntax(name,
                      invalid_command_line_syntax::empty_adjacent_parameter));
            }
            else
            {
                name = tok.substr(2);
            }
            args.erase(args.begin());
            return parse_option(name, adjacent, args);

        }
        return vector<option>();
    }


    std::vector<option> 
    cmdline::parse_short_option(std::vector<string>& args)
    {
        const std::string& tok = args[0];
        if (tok.size() >= 2 && tok[0] == '-' && tok[1] != '-')
        {   
            vector<option> result;

            string name = tok.substr(0,2);
            string adjacent = tok.substr(2);

            // Short options can be 'grouped', so that
            // "-d -a" becomes "-da". Loop, processing one
            // option at a time. We exit the loop when either
            // we've processed all the token, or when the remainder
            // of token is considered to be value, not further grouped
            // option.
            for(;;) {
                const option_description& d = m_desc->find(name, false);

                // FIXME: check for 'allow_sticky'.
                if ((style & allow_sticky) &&
                    d.semantic()->max_tokens() == 0 && !adjacent.empty()) {
                    // 'adjacent' is in fact further option.
                    vector<std::string> dummy;
                    vector<option> n = parse_option(name, std::string(), dummy);
                    for (unsigned i = 0; i < n.size(); ++i)
                        result.push_back(n[i]);

                    if (adjacent.empty())
                    {
                        args.erase(args.begin());
                        break;
                    }

                    name = string("-") + adjacent[0];
                    adjacent.erase(adjacent.begin());
                } else {

                    args.erase(args.begin());                    
                    // The current option accepts some tokens for value,
                    // parse it in a regular way.
                    vector<option> n = parse_option(name, adjacent,
                                                    args);
                    for (unsigned i = 0; i < n.size(); ++i)
                        result.push_back(n[i]);

                    break;

                }
            }
            return result;
        }
        return std::vector<option>();
    }

    std::vector<option> 
    cmdline::parse_dos_option(std::vector<string>& args)
    {
        const std::string& tok = args[0];
        if (tok.size() >= 2 && tok[0] == '/')
        {   
            vector<option> result;

            string name = "-" + tok.substr(1,1);
            string adjacent = tok.substr(2);

            args.erase(args.begin());
            return parse_option(name, adjacent, args);
        }
        return std::vector<option>();
    }

    std::vector<option> 
    cmdline::parse_disguised_long_option(std::vector<string>& args)
    {
        const std::string& tok = args[0];
        if (tok.size() >= 2 && 
            ((tok[0] == '-' && tok[1] != '-') ||
             ((style & allow_slash_for_short) && tok[0] == '/')))            
        {
            if (m_desc->find_nothrow(tok.substr(1, tok.find('=')-1), 
                                     style & allow_guessing)) {
                args[0].insert(0, "-");
                if (args[0][1] == '/')
                    args[0][1] = '-';
                return parse_long_option(args);
            }
        }
        return vector<option>();
    }

    std::vector<option> 
    cmdline::parse_terminator(std::vector<std::string>& args)
    {
        vector<option> result;
        const std::string& tok = args[0];
        if (tok == "--")
        {
            for(unsigned i = 1; i < args.size(); ++i)
            {
                option opt;
                opt.value.push_back(args[i]);
                result.push_back(opt);
            }
            args.clear();
        }
        return result;
    }




#if 0

    void 
    cmdline::set_additional_parser(additional_parser p)
    {
        m_additional_parser = p;
    }
#endif


}}}
