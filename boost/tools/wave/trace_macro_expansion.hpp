/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(TRACE_MACRO_EXPANSION_HPP_D8469318_8407_4B9D_A19F_13CA60C1661F_INCLUDED)
#define TRACE_MACRO_EXPANSION_HPP_D8469318_8407_4B9D_A19F_13CA60C1661F_INCLUDED

#include <cstdio>
#include <ostream>
#include <string>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/wave/token_ids.hpp>
#include <boost/wave/util/macro_helpers.hpp>
#include <boost/wave/preprocessing_hooks.hpp>
#include <boost/wave/whitespace_handling.hpp>
#include <boost/wave/language_support.hpp>

#include "stop_watch.hpp"

#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#define BOOST_WAVE_OSSTREAM std::ostrstream
std::string BOOST_WAVE_GETSTRING(std::ostrstream& ss)
{
    ss << ends;
    std::string rval = ss.str();
    ss.freeze(false);
    return rval;
}
#else
#include <sstream>
#define BOOST_WAVE_GETSTRING(ss) ss.str()
#define BOOST_WAVE_OSSTREAM std::ostringstream
#endif

//  trace_flags:  enable single tracing functionality
enum trace_flags {
    trace_nothing = 0,      // disable tracing
    trace_macros = 1,       // enable macro tracing
    trace_includes = 2      // enable include file tracing
};

///////////////////////////////////////////////////////////////////////////////
//  
//  The trace_macro_expansion policy is used to trace the macro expansion of
//  macros whenever it is requested from inside the input stream to preprocess
//  through the '#pragma wave_option(trace: enable)' directive. The macro 
//  tracing is disabled with the help of a '#pragma wave_option(trace: disable)'
//  directive.
//
//  This policy type is used as a template parameter to the boost::wave::context<>
//  object.
//
///////////////////////////////////////////////////////////////////////////////
template <typename TokenT>
class trace_macro_expansion
:   public boost::wave::context_policies::eat_whitespace<TokenT>
{
    typedef boost::wave::context_policies::eat_whitespace<TokenT> 
        whitespace_base_type;
    
public:
    trace_macro_expansion(bool preserve_comments, std::ostream &tracestrm_, 
            std::ostream &includestrm_, trace_flags flags_)
    :   whitespace_base_type(preserve_comments),
        tracestrm(tracestrm_), includestrm(includestrm_), level(0), 
        flags(flags_), logging_flags(trace_nothing)
    {
    }
    ~trace_macro_expansion()
    {
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'expanding_function_like_macro' is called, whenever a 
    //  function-like macro is to be expanded.
    //
    //  The 'macrodef' parameter marks the position, where the macro to expand 
    //  is defined.
    //  The 'formal_args' parameter holds the formal arguments used during the
    //  definition of the macro.
    //  The 'definition' parameter holds the macro definition for the macro to 
    //  trace.
    //
    //  The 'macrocall' parameter marks the position, where this macro invoked.
    //  The 'arguments' parameter holds the macro arguments used during the 
    //  invocation of the macro
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContainerT>
    void expanding_function_like_macro(
        TokenT const &macrodef, std::vector<TokenT> const &formal_args, 
        ContainerT const &definition,
        TokenT const &macrocall, std::vector<ContainerT> const &arguments) 
    {
        if (!enabled_macro_tracing()) return;
        
        if (0 == get_level()) {
        // output header line
        BOOST_WAVE_OSSTREAM stream;

            stream 
                << macrocall.get_position() << ": "
                << macrocall.get_value() << "(";

        // argument list
            for (typename ContainerT::size_type i = 0; i < arguments.size(); ++i) {
                stream << boost::wave::util::impl::as_string(arguments[i]);
                if (i < arguments.size()-1)
                    stream << ", ";
            }
            stream << ")" << std::endl; 
            output(BOOST_WAVE_GETSTRING(stream));
            increment_level();
        }        
        
    // output definition reference
        {
        BOOST_WAVE_OSSTREAM stream;

            stream 
                << macrodef.get_position() << ": see macro definition: "
                << macrodef.get_value() << "(";

        // formal argument list
            for (typename std::vector<TokenT>::size_type i = 0; 
                i < formal_args.size(); ++i) 
            {
                stream << formal_args[i].get_value();
                if (i < formal_args.size()-1)
                    stream << ", ";
            }
            stream << ")" << std::endl; 
            output(BOOST_WAVE_GETSTRING(stream));
        }

        if (formal_args.size() > 0) {
        // map formal and real arguments
            open_trace_body("invoked with\n");
            for (typename std::vector<TokenT>::size_type j = 0; 
                j < formal_args.size(); ++j) 
            {
                using namespace boost::wave;

                BOOST_WAVE_OSSTREAM stream;
                stream << formal_args[j].get_value() << " = ";
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
                if (T_ELLIPSIS == token_id(formal_args[j])) {
                // ellipsis
                    for (typename ContainerT::size_type k = j; 
                        k < arguments.size(); ++k) 
                    {
                        stream << boost::wave::util::impl::as_string(arguments[k]);
                        if (k < arguments.size()-1)
                            stream << ", ";
                    }
                } 
                else 
#endif
                {
                    stream << boost::wave::util::impl::as_string(arguments[j]);
                }
                stream << std::endl;
                output(BOOST_WAVE_GETSTRING(stream));
            }
            close_trace_body();
        }
        open_trace_body();
    }

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'expanding_object_like_macro' is called, whenever a 
    //  object-like macro is to be expanded .
    //
    //  The 'macrodef' parameter marks the position, where the macro to expand 
    //  is defined.
    //  The 'definition' parameter holds the macro definition for the macro to 
    //  trace.
    //
    //  The 'macrocall' parameter marks the position, where this macro invoked.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContainerT>
    void expanding_object_like_macro(TokenT const &macrodef, 
        ContainerT const &definition, TokenT const &macrocall)
    {
        if (!enabled_macro_tracing()) return;
        
        if (0 == get_level()) {
        // output header line
        BOOST_WAVE_OSSTREAM stream;

            stream 
                << macrocall.get_position() << ": "
                << macrocall.get_value() << std::endl;
            output(BOOST_WAVE_GETSTRING(stream));
            increment_level();
        }
        
    // output definition reference
        {
        BOOST_WAVE_OSSTREAM stream;

            stream 
                << macrodef.get_position() << ": see macro definition: "
                << macrodef.get_value() << std::endl;
            output(BOOST_WAVE_GETSTRING(stream));
        }
        open_trace_body();
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'expanded_macro' is called, whenever the expansion of a 
    //  macro is finished but before the rescanning process starts.
    //
    //  The parameter 'result' contains the token sequence generated as the 
    //  result of the macro expansion.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContainerT>
    void expanded_macro(ContainerT const &result)
    {
        if (!enabled_macro_tracing()) return;
        
        BOOST_WAVE_OSSTREAM stream;
        stream << boost::wave::util::impl::as_string(result) << std::endl;
        output(BOOST_WAVE_GETSTRING(stream));

        open_trace_body("rescanning\n");
    }

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'rescanned_macro' is called, whenever the rescanning of a 
    //  macro is finished.
    //
    //  The parameter 'result' contains the token sequence generated as the 
    //  result of the rescanning.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContainerT>
    void rescanned_macro(ContainerT const &result)
    {
        if (!enabled_macro_tracing() || get_level() == 0) 
            return;

        BOOST_WAVE_OSSTREAM stream;
        stream << boost::wave::util::impl::as_string(result) << std::endl;
        output(BOOST_WAVE_GETSTRING(stream));
        close_trace_body();
        close_trace_body();
        
        if (1 == get_level())
            decrement_level();
    }

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'interpret_pragma' is called, whenever a #pragma wave 
    //  directive is found, which isn't known to the core Wave library. 
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'pending' may be used to push tokens back into the input 
    //  stream, which are to be used as the replacement text for the whole 
    //  #pragma wave() directive.
    //
    //  The parameter 'option' contains the name of the interpreted pragma.
    //
    //  The parameter 'values' holds the values of the parameter provided to 
    //  the pragma operator.
    //
    //  The parameter 'act_token' contains the actual #pragma token, which may 
    //  be used for error output.
    //
    //  If the return value is 'false', the whole #pragma directive is 
    //  interpreted as unknown and a corresponding error message is issued. A
    //  return value of 'true' signs a successful interpretation of the given 
    //  #pragma.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename ContainerT>
    bool 
    interpret_pragma(ContextT const &ctx, ContainerT &pending, 
        typename ContextT::token_type const &option, ContainerT const &values, 
        typename ContextT::token_type const &act_token)
    {
        typedef typename ContextT::token_type token_type;
        
        if (option.get_value() == "timer") {
        // #pragma wave timer(value)
            if (0 == values.size()) {
            // no value means '1'
                using namespace boost::wave;
                timer(token_type(T_INTLIT, "1", act_token.get_position()));
            }
            else {
                timer(values.front());
            }
            return true;
        }
        else if (option.get_value() == "trace") {
        // enable/disable tracing option
            return interpret_pragma_trace(ctx, values, act_token);
        }
        else if (option.get_value() == "system") {
        // try to spawn the given argument as a system command and return the
        // std::cout of this process as the replacement of this _Pragma
            return interpret_pragma_system(ctx, pending, values, act_token);
        }
        if (option.get_value() == "stop") {
        // stop the execution and output the argument
            BOOST_WAVE_THROW(preprocess_exception, error_directive,
                boost::wave::util::impl::as_string(values).c_str(), 
                act_token.get_position());
        }
        return false;
    }
        
    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'opened_include_file' is called, whenever a file referred 
    //  by an #include directive was successfully located and opened.
    //
    //  The parameter 'filename' contains the file system path of the 
    //  opened file (this is relative to the directory of the currently 
    //  processed file or a absolute path depending on the paths given as the
    //  include search paths).
    //
    //  The include_depth parameter contains the current include file depth.
    //
    //  The is_system_include parameter denotes, whether the given file was 
    //  found as a result of a #include <...> directive.
    //  
    ///////////////////////////////////////////////////////////////////////////
    void 
    opened_include_file(std::string const &relname, std::string const &absname, 
        std::size_t include_depth, bool is_system_include) 
    {
        if (enabled_include_tracing()) {
            // print indented filename
            for (std::size_t i = 0; i < include_depth; ++i)
                includestrm << " ";
                
            if (is_system_include)
                includestrm << "<" << relname << "> (" << absname << ")";
            else
                includestrm << "\"" << relname << "\" (" << absname << ")";

            includestrm << std::endl;
        }
    }

protected:
    //  Interpret the different Wave specific pragma directives/operators
    template <typename ContextT, typename ContainerT>
    bool 
    interpret_pragma_trace(ContextT const &/*ctx*/, ContainerT const &values, 
        typename ContextT::token_type const &act_token)
    {
        typedef typename ContextT::token_type token_type;
        typedef typename token_type::string_type string_type;

    bool valid_option = false;

        if (1 == values.size()) {
        token_type const &value = values.front();
        
            if (value.get_value() == "enable" ||
                value.get_value() == "on" || 
                value.get_value() == "1") 
            {
            // #pragma wave trace(enable)
                enable_tracing(static_cast<trace_flags>(
                    tracing_enabled() | trace_macros));
                valid_option = true;
            }
            else if (value.get_value() == "disable" ||
                value.get_value() == "off" || 
                value.get_value() == "0") 
            {
            // #pragma wave trace(disable)
                enable_tracing(static_cast<trace_flags>(
                    tracing_enabled() & ~trace_macros));
                valid_option = true;
            }
        }
        if (!valid_option) {
        // unknown option value
        string_type option_str ("trace");

            if (values.size() > 0) {
                option_str += "(";
                option_str += boost::wave::util::impl::as_string(values);
                option_str += ")";
            }
            BOOST_WAVE_THROW(preprocess_exception, ill_formed_pragma_option,
                option_str.c_str(), act_token.get_position());
        }
        return true;
    }

    template <typename ContextT, typename ContainerT>
    bool
    interpret_pragma_system(ContextT const &ctx, ContainerT &pending, 
        ContainerT const &values, 
        typename ContextT::token_type const &act_token)
    {
        typedef typename ContextT::token_type token_type;
        typedef typename token_type::string_type string_type;

        if (0 == values.size()) return false;   // ill_formed_pragma_option
        
    string_type stdout_file(std::tmpnam(0));
    string_type stderr_file(std::tmpnam(0));
    string_type system_str(boost::wave::util::impl::as_string(values));
    string_type native_cmd(system_str);

        system_str += " >" + stdout_file + " 2>" + stderr_file;
        if (0 != std::system(system_str.c_str())) {
        // unable to spawn the command
        string_type error_str("unable to spawn command: ");
        
            error_str += native_cmd;
            BOOST_WAVE_THROW(preprocess_exception, ill_formed_pragma_option,
                error_str.c_str(), act_token.get_position());
        }
        
    // rescan the content of the stdout_file and insert it as the 
    // _Pragma replacement
        typedef typename ContextT::lexer_type lexer_type;
        typedef typename ContextT::input_policy_type input_policy_type;
        typedef boost::wave::iteration_context<lexer_type, input_policy_type> 
            iteration_context_type;

    iteration_context_type iter_ctx(stdout_file.c_str(), 
        act_token.get_position(), ctx.get_language());
    ContainerT pragma;

        for (/**/; iter_ctx.first != iter_ctx.last; ++iter_ctx.first) 
            pragma.push_back(*iter_ctx.first);

    // prepend the newly generated token sequence to the 'pending' container
        pending.splice(pending.begin(), pragma);

    // erase the created tempfiles
        std::remove(stdout_file.c_str());
        std::remove(stderr_file.c_str());
        return true;
    }

    //  The function enable_tracing is called, whenever the status of the 
    //  tracing was changed.
    //  The parameter 'enable' is to be used as the new tracing status.
    void enable_tracing(trace_flags flags) 
        { logging_flags = flags; }

    //  The function tracing_enabled should return the current tracing status.
    trace_flags tracing_enabled() 
        { return logging_flags; }

    //  Helper functions for generating the trace output
    void open_trace_body(char const *label = 0)
    {
        if (label)
            output(label);
        output("[\n");
        increment_level();
    }
    void close_trace_body()
    {
        if (get_level() > 0) {
            decrement_level();
            output("]\n");
            tracestrm << std::flush;      // flush the stream buffer
        }
    }

    template <typename StringT>
    void output(StringT const &outstr) const
    {
        indent(get_level());
        tracestrm << outstr;          // output the given string
    }

    void indent(int level) const
    {
        for (int i = 0; i < level; ++i)
            tracestrm << "  ";        // indent
    }

    int increment_level() { return ++level; }
    int decrement_level() { BOOST_ASSERT(level > 0); return --level; }
    int get_level() const { return level; }
    
    bool enabled_macro_tracing() const 
    { 
        return (flags & trace_macros) && (logging_flags & trace_macros); 
    }
    bool enabled_include_tracing() const 
    { 
        return (flags & trace_includes); 
    }
    
    void timer(TokenT const &value)
    {
        if (value.get_value() == "0" || value.get_value() == "restart") {
        // restart the timer
            elapsed_time.restart();
        }
        else if (value.get_value() == "1") {
        // print out the current elapsed time
            std::cerr 
                << value.get_position() << ": " 
                << elapsed_time.format_elapsed_time()
                << std::endl;
        }
        else if (value.get_value() == "suspend") {
        // suspend the timer
            elapsed_time.suspend();
        }
        else if (value.get_value() == "resume") {
        // resume the timer
            elapsed_time.resume();
        }
    }

private:
    std::ostream &tracestrm;        // trace output stream
    std::ostream &includestrm;      // included list output stream
    int level;                      // indentation level
    trace_flags flags;              // enabled globally
    trace_flags logging_flags;      // enabled by a #pragma
    
    stop_watch elapsed_time;        // trace timings
};

#undef BOOST_WAVE_GETSTRING
#undef BOOST_WAVE_OSSTREAM

#endif // !defined(TRACE_MACRO_EXPANSION_HPP_D8469318_8407_4B9D_A19F_13CA60C1661F_INCLUDED)
