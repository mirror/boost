/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// system headers
#include <string>
#include <iostream>
#include <vector>

// include boost
#include <boost/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/detail/workaround.hpp>

//  include Wave 
#include <boost/wave.hpp>

//  include the lexer related stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>      // token type
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>   // lexer type

//  this header includes the cpplexer::new_lexer_gen template used for the 
//  explicit template specialisation below
#include <boost/wave/cpplexer/re2clex/cpp_re2c_lexer.hpp>

//  test application related headers
#include "cmd_line_utils.hpp"
#include "testwave_app.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

///////////////////////////////////////////////////////////////////////////////
// testwave version definitions
#define TESTWAVE_VERSION_MAJOR           0
#define TESTWAVE_VERSION_MINOR           3
#define TESTWAVE_VERSION_SUBMINOR        0

///////////////////////////////////////////////////////////////////////////////
// workaround for missing ostringstream
#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#define TESTWAVE_OSSTREAM std::ostrstream
std::string TESTWAVE_GETSTRING(std::ostrstream& ss)
{
    ss << ends;
    std::string rval = ss.str();
    ss.freeze(false);
    return rval;
}
#else
#include <sstream>
#define TESTWAVE_GETSTRING(ss) ss.str()
#define TESTWAVE_OSSTREAM std::ostringstream
#endif

namespace {

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    inline bool 
    handle_next_token(Iterator &it, Iterator const& end, 
        std::string &result)
    {
        typedef typename Iterator::value_type token_type;
        
        token_type tok = *it++;    
        result = result + tok.get_value().c_str();
        return (it == end) ? false : true;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename String>
    String const& handle_quoted_filepath(String &name)
    {
        using boost::wave::util::impl::unescape_lit;
        
        String unesc_name = unescape_lit(name.substr(1, name.size()-2));
        fs::path p (unesc_name.c_str(), fs::native);

        name = String("\"") + p.leaf().c_str() + String("\"");
        return name;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename String>
    String const& handle_filepath(String &name)
    {
        using boost::wave::util::impl::unescape_lit;
        
        String unesc_name = unescape_lit(name);
        fs::path p (unesc_name.c_str(), fs::native);

        name = p.leaf().c_str();
        return name;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    bool handle_line_directive(Iterator &it, Iterator const& end, 
        std::string &result)
    {
        typedef typename Iterator::value_type token_type;
        typedef typename token_type::string_type string_type;
        
        if (!handle_next_token(it, end, result) ||  // #line
            !handle_next_token(it, end, result) ||  // whitespace
            !handle_next_token(it, end, result) ||  // number
            !handle_next_token(it, end, result))    // whitespace
        {
            return false;
        }
        
        using boost::wave::util::impl::unescape_lit;
        
        token_type filename = *it;
        string_type name = filename.get_value();

        handle_quoted_filepath(name);
        result = result + name.c_str();
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  This function compares the real result and the expected one but first 
    //  replaces all occurences of $F in the expected result to the passed
    //  full filepath and $V to the current Boost version number.
    //
    ///////////////////////////////////////////////////////////////////////////
    inline bool 
    got_expected_result(std::string const& filename, 
        std::string const& result, std::string& expected)
    {
        using boost::wave::util::impl::escape_lit;
        
        std::string full_result;
        std::string::size_type pos = 0;
        std::string::size_type pos1 = expected.find_first_of("$");
        
        if (pos1 != std::string::npos) {
            do {
                switch(expected[pos1+1]) {
                case 'F':       // insert base file name
                    full_result = full_result + 
                        expected.substr(pos, pos1-pos) + escape_lit(filename);
                    pos1 = expected.find_first_of ("$", pos = pos1 + 2);
                    break;

                case 'P':       // insert full path
                    {
                        fs::path fullpath = fs::complete(
                            fs::path(filename, fs::native), 
                            fs::current_path());
                        if ('(' == expected[pos1+2]) {
                        // the $P(basename) syntax is used
                            std::size_t p = expected.find_first_of(")", pos1+1);
                            if (std::string::npos == p) {
                                std::cerr 
                                    << "testwave: unmatched parenthesis in $P"
                                       " directive" << std::endl;
                                return false;
                            }
                            std::string base = expected.substr(pos1+3, p-pos1-3);
                            fullpath = fullpath.branch_path() / 
                                fs::path(base, fs::native);
                            full_result = full_result + 
                                expected.substr(pos, pos1-pos) + 
                                escape_lit(fullpath.normalize().native_file_string());
                            pos1 = expected.find_first_of ("$", 
                                pos = pos1 + 4 + base.size());
                        }
                        else {
                        // the $P is used on its own
                            full_result = full_result + 
                                expected.substr(pos, pos1-pos) + 
                                escape_lit(fullpath.native_file_string());
                            pos1 = expected.find_first_of ("$", pos = pos1 + 2);
                        }
                    }
                    break;
                    
                case 'V':       // insert Boost version
                    full_result = full_result + 
                        expected.substr(pos, pos1-pos) + BOOST_LIB_VERSION;
                    pos1 = expected.find_first_of ("$", pos = pos1 + 2);
                    break;
                    
                default:
                    full_result = full_result +
                        expected.substr(pos, pos1-pos);
                    pos1 = expected.find_first_of ("$", (pos = pos1) + 1);
                    break;
                }

            } while(pos1 != std::string::npos);
            full_result += expected.substr(pos);
        }
        else {
            full_result = expected;
        }
        
        expected = full_result;
        return full_result == result;
    }
}

///////////////////////////////////////////////////////////////////////////////
testwave_app::testwave_app(po::variables_map const& vm)
:   debuglevel(1), desc_options("Preprocessor configuration options"), 
    global_vm(vm)
{
    desc_options.add_options()
        ("include,I", po::value<cmd_line_utils::include_paths>()->composing(), 
            "specify an additional include directory")
        ("sysinclude,S", po::value<std::vector<std::string> >()->composing(), 
            "specify an additional system include directory")
        ("define,D", po::value<std::vector<std::string> >()->composing(), 
            "specify a macro to define (as macro[=[value]])")
        ("predefine,P", po::value<std::vector<std::string> >()->composing(), 
            "specify a macro to predefine (as macro[=[value]])")
        ("undefine,U", po::value<std::vector<std::string> >()->composing(), 
            "specify a macro to undefine")
        ("nesting,n", po::value<int>(), 
            "specify a new maximal include nesting depth")
        ("long_long", "enable long long support in C++ mode")
        ("preserve", "preserve comments")
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
        ("variadics", "enable certain C99 extensions in C++ mode")
        ("c99", "enable C99 mode (implies --variadics)")
#endif 
    ;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Test the given file (i.e. preprocess the file and compare the result 
//  against the embedded 'R' comments, if an error occurs compare the error
//  message against the given 'E' comments).
//
///////////////////////////////////////////////////////////////////////////////
bool 
testwave_app::test_a_file(std::string filename)
{
// read the input file into a string
    std::string instr;
    if (!read_file(filename, instr)) 
        return false;     // error was reported already

// extract expected output, preprocess the data and compare results
    std::string expected;
    if (extract_expected_output(filename, instr, expected)) {
        bool retval = true;   // assume success
        std::string result, error;
        bool pp_result = preprocess_file(filename, instr, result, error);
        if (pp_result || !result.empty()) {
        // did we expect an error?
            std::string expected_error;
            if (!extract_special_information(filename, instr, 'E', expected_error))
                return false;

            if (!expected_error.empty() && 
                !got_expected_result(filename, error, expected_error))
            {
            // we expected an error but got none (or a different one)
                if (debuglevel > 2) {
                    std::cerr 
                        << filename << ": failed" << std::endl
                        << "result: " << std::endl << result << std::endl;

                    if (!error.empty()) {
                        std::cerr << "expected result: " << std::endl 
                                  << expected << std::endl;
                    }
                    if (!expected_error.empty()) {
                        std::cerr << "expected error: " << std::endl 
                                  << expected_error << std::endl;
                    }
                }
                else if (debuglevel > 1) {
                    std::cerr << filename << ": failed" << std::endl;
                }
                retval = false;
            }
            else if (!got_expected_result(filename, result, expected)) {
            //  no preprocessing error encountered
                if (debuglevel > 2) {
                    std::cerr 
                        << filename << ": failed" << std::endl
                        << "result: " << std::endl << result << std::endl
                        << "expected: " << std::endl << expected << std::endl;
                }
                else if (debuglevel > 1) {
                    std::cerr << filename << ": failed" << std::endl;
                }
                retval = false;
            }
            else if (debuglevel > 4) {
                std::cerr 
                    << filename << ": succeeded" << std::endl
                    << "result: " << std::endl << result << std::endl;
            }
            else if (debuglevel > 3) {
                std::cerr << filename << ": succeeded" << std::endl;
            }
        }
        
        if (!pp_result) {
        //  there was a preprocessing error, was it expected?
            std::string expected_error;
            if (!extract_special_information(filename, instr, 'E', expected_error))
                return false;
                
            if (!got_expected_result(filename, error, expected_error)) {
            // the error was unexpected
                if (debuglevel > 2) {
                    std::cerr 
                        << filename << ": failed" << std::endl;

                    if (!expected_error.empty()) {
                        std::cerr 
                            << "result: " << std::endl << error << std::endl
                            << "expected error: " << std::endl
                            << expected_error << std::endl;
                    }
                    else {
                        std::cerr << "unexpected error: " << error << std::endl;
                    }
                }
                else if (debuglevel > 1) {
                    std::cerr << filename << ": failed" << std::endl;
                }
                retval = false;
            }
            else if (debuglevel > 4) {
                std::cerr 
                    << filename << ": succeeded" << std::endl
                    << "result: " << std::endl << error << std::endl;
            }
            else if (debuglevel > 3) {
            // caught the expected error message
                std::cerr << filename << ": succeeded" << std::endl;
            }
        }
        return retval;
    }
    else {
        std::cerr 
            << filename << ": no information about expected results found"
            << std::endl;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
//  print the current version of this program
//
///////////////////////////////////////////////////////////////////////////////
int 
testwave_app::print_version()
{
// get time of last compilation of this file
boost::wave::util::time_conversion_helper compilation_time(__DATE__ " " __TIME__);

// calculate the number of days since Feb 12 2005 
// (the day the testwave project was started)
std::tm first_day;

    using namespace std;      // some platforms have memset in namespace std
    memset (&first_day, 0, sizeof(std::tm));
    first_day.tm_mon = 1;           // Feb
    first_day.tm_mday = 12;         // 12
    first_day.tm_year = 105;        // 2005

long seconds = long(std::difftime(compilation_time.get_time(), 
    std::mktime(&first_day)));

    std::cout 
        << TESTWAVE_VERSION_MAJOR << '.' 
        << TESTWAVE_VERSION_MINOR << '.'
        << TESTWAVE_VERSION_SUBMINOR << '.'
        << seconds/(3600*24)        // get number of days from seconds
        << std::endl;
    return 0;                       // exit app
}

///////////////////////////////////////////////////////////////////////////////
//
//  print the copyright statement
//
///////////////////////////////////////////////////////////////////////////////
int 
testwave_app::print_copyright()
{
    char const *copyright[] = {
        "",
        "Testwave: A test driver for the Boost.Wave C++ preprocessor library",
        "http://www.boost.org/",
        "",
        "Copyright (c) 2001-2005 Hartmut Kaiser, Distributed under the Boost",
        "Software License, Version 1.0. (See accompanying file",
        "LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)",
        0
    };
    
    for (int i = 0; 0 != copyright[i]; ++i)
        std::cout << copyright[i] << std::endl;
        
    return 0;                       // exit app
}

///////////////////////////////////////////////////////////////////////////////
//
//  Read the given file into a string
//
///////////////////////////////////////////////////////////////////////////////
bool 
testwave_app::read_file(std::string const& filename, std::string& instr)
{
// open the given file and report error, if appropriate
    std::ifstream instream(filename.c_str());
    if (!instream.is_open()) {
        std::cerr << "testwave: could not open input file: " 
                  << filename << std::endl;
        return false;
    }
    instream.unsetf(std::ios::skipws);

// read the input file into a string
    
#if defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
// this is known to be very slow for large files on some systems
    std::copy (std::istream_iterator<char>(instream),
        std::istream_iterator<char>(), 
        std::inserter(instr, instr.end()));
#else
    instr = std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
        std::istreambuf_iterator<char>());
#endif 
    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//  This explicit template instantiation is needed for the function
//  extract_expected_output below, which needs the lexer to be instantiated 
//  with a std::string::const_iterator template parameter.
//
///////////////////////////////////////////////////////////////////////////////
template 
struct boost::wave::cpplexer::new_lexer_gen<std::string::const_iterator>;

namespace {

    void trim_whitespace(std::string& value)
    {
        std::string::size_type first = value.find_first_not_of(" \t");
        std::string::size_type last = std::string::npos;
        
        if (std::string::npos == first) 
            value.clear();
        else {
            last = value.find_last_not_of(" \t")+1;
            assert(std::string::npos != last);
            value = value.substr(first, last-first);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Extract special information from comments marked with the given letter
//
///////////////////////////////////////////////////////////////////////////////
bool 
testwave_app::extract_special_information(std::string const& filename, 
    std::string const& instr, char flag, std::string& content)
{
// tokenize the input data into C++ tokens using the C++ lexer
    typedef boost::wave::cpplexer::lex_token<> token_type;
    typedef boost::wave::cpplexer::lex_iterator<token_type> lexer_type;
    typedef token_type::position_type position_type;
    
    boost::wave::language_support const lang_opts = 
        (boost::wave::language_support)(
            boost::wave::support_variadics | boost::wave::support_long_long |
            boost::wave::support_option_no_character_validation |
            boost::wave::support_option_convert_trigraphs);
    
    position_type pos(filename.c_str());
    lexer_type it = lexer_type(instr.begin(), instr.end(), pos, lang_opts);
    lexer_type end = lexer_type();

    try {
    // look for C or C++ comments starting with the special character
        for (/**/; it != end; ++it) {
            using namespace boost::wave;
            token_id id = token_id(*it);
            if (T_CCOMMENT == id) {
                std::string value = (*it).get_value().c_str();
                if (flag == value[2]) {
                    content += value.substr(3, value.size()-5);
                    trim_whitespace(content);
                }
            }
            else if (T_CPPCOMMENT == id) {
                std::string value = (*it).get_value().c_str();
                if (flag == value[2])
                    content += value.substr((' ' == value[3]) ? 4 : 3);
            }
        }
    }
    catch (boost::wave::cpplexer::lexing_exception &e) {
    // some lexing error
        std::cerr 
            << e.file_name() << "(" << e.line_no() << "): "
            << e.description() << std::endl;
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Extract the expected output from the given input data
//
//  The expected output has to be provided inside of special comments which
//  start with a capital 'R'. All such comments are concatenated and returned
//  through the parameter 'expected'.
//
///////////////////////////////////////////////////////////////////////////////
inline bool 
testwave_app::extract_expected_output(std::string const& filename, 
    std::string const& instr, std::string& expected)
{
    return extract_special_information(filename, instr, 'R', expected);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Extracts the required preprocessing options from the given input data and
//  initialises the given Wave context object accordingly. 
//  We allow the same (applicable) options to be used as are valid for the wave 
//  driver executable.
//
///////////////////////////////////////////////////////////////////////////////
template <typename Context>
bool 
testwave_app::extract_options(std::string const& filename, 
    std::string const& instr, Context& ctx)
{
//  extract the required information from the comments flagged by a 
//  capital 'O'
    std::string options;
    if (!extract_special_information(filename, instr, 'O', options))
        return false;

    try {        
    //  parse the configuration information into a program_options_description
    //  object
        po::variables_map local_vm;
        cmd_line_utils::read_config_options(options, desc_options, local_vm);
        initialise_options(ctx, local_vm);
    }
    catch (std::exception &e) {
        std::cerr << filename << ": exception caught: " << e.what() 
            << std::endl;
        return false;
    }
    
    return true;
}

namespace {

    template <typename T>
    inline T const&
    variables_map_as(po::variable_value const& v, T*)
    {
#if (__GNUC__ == 3 && (__GNUC_MINOR__ == 2 || __GNUC_MINOR__ == 3)) || \
    BOOST_WORKAROUND(__MWERKS__, < 0x3200)
// gcc 3.2.x and  3.3.x choke on vm[...].as<...>()
// CW 8.3 has problems with the v.as<T>() below
        T const* r = boost::any_cast<T>(&v.value());
        if (!r)
            throw boost::bad_any_cast();
        return *r;
#else
        return v.as<T>();
#endif
    }
}

template <typename Context>
bool 
testwave_app::initialise_options(Context& ctx, po::variables_map const& vm)
{
//  initialise the given context from the parsed options
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
// enable C99 mode, if appropriate (implies variadics)
    if (vm.count("c99")) {
        ctx.set_language(boost::wave::support_c99);
    }
    else if (vm.count("variadics")) {
    // enable variadics and placemarkers, if appropriate
        ctx.set_language(boost::wave::enable_variadics(ctx.get_language()));
    }
#endif // BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0

// enable long_long mode, if appropriate
    if (vm.count("long_long")) {
        ctx.set_language(boost::wave::enable_long_long(ctx.get_language()));
    }
    
// enable preserving comments mode, if appropriate
    if (vm.count("preserve")) {
        ctx.set_language(
            boost::wave::enable_preserve_comments(ctx.get_language()));
    }
    
// enable trigraph conversion
    ctx.set_language(boost::wave::set_support_options(ctx.get_language(), 
        (boost::wave::language_support)(
            boost::wave::get_support_options(ctx.get_language()) | 
            boost::wave::support_option_convert_trigraphs)
        )
    );

//  add include directories to the system include search paths
    if (vm.count("sysinclude")) {
    std::vector<std::string> const& syspaths = 
        variables_map_as(vm["sysinclude"], (std::vector<std::string> *)NULL);
    
        std::vector<std::string>::const_iterator end = syspaths.end();
        for (std::vector<std::string>::const_iterator cit = syspaths.begin(); 
              cit != end; ++cit)
        {
            ctx.add_sysinclude_path((*cit).c_str());
        }
    }
    
//  add include directories to the user include search paths
    if (vm.count("include")) {
        cmd_line_utils::include_paths const &ip = 
            variables_map_as(vm["include"], (cmd_line_utils::include_paths*)NULL);
        std::vector<std::string>::const_iterator end = ip.paths.end();

        for (std::vector<std::string>::const_iterator cit = ip.paths.begin(); 
              cit != end; ++cit)
        {
            ctx.add_include_path((*cit).c_str());
        }

    // if on the command line was given -I- , this has to be propagated
        if (ip.seen_separator) 
            ctx.set_sysinclude_delimiter();
              
    // add system include directories to the include path
        std::vector<std::string>::const_iterator sysend = ip.syspaths.end();
        for (std::vector<std::string>::const_iterator syscit = ip.syspaths.begin(); 
              syscit != sysend; ++syscit)
        {
            ctx.add_sysinclude_path((*syscit).c_str());
        }
    }

//  add additional defined macros 
    if (vm.count("define")) {
        std::vector<std::string> const &macros = 
            variables_map_as(vm["define"], (std::vector<std::string>*)NULL);
        std::vector<std::string>::const_iterator end = macros.end();
        for (std::vector<std::string>::const_iterator cit = macros.begin(); 
              cit != end; ++cit)
        {
            ctx.add_macro_definition(*cit);
        }
    }

//  add additional predefined macros 
    if (vm.count("predefine")) {
        std::vector<std::string> const &predefmacros = 
            variables_map_as(vm["predefine"], (std::vector<std::string>*)NULL);
        std::vector<std::string>::const_iterator end = predefmacros.end();
        for (std::vector<std::string>::const_iterator cit = predefmacros.begin(); 
              cit != end; ++cit)
        {
            ctx.add_macro_definition(*cit, true);
        }
    }

//  undefine specified macros
    if (vm.count("undefine")) {
        std::vector<std::string> const &undefmacros = 
            variables_map_as(vm["undefine"], (std::vector<std::string>*)NULL);
        std::vector<std::string>::const_iterator end = undefmacros.end();
        for (std::vector<std::string>::const_iterator cit = undefmacros.begin(); 
              cit != end; ++cit)
        {
            ctx.remove_macro_definition((*cit).c_str(), true);
        }
    }

//  maximal include nesting depth
    if (vm.count("nesting")) {
        int max_depth = variables_map_as(vm["nesting"], (int*)NULL);
        if (max_depth < 1 || max_depth > 100000) {
            std::cerr << "testwave: bogus maximal include nesting depth: " 
                << max_depth << std::endl;
            return false;
        }
        ctx.set_max_include_nesting_depth(max_depth);
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocess the given input data and return the generated output through 
//  the parameter 'result'.
//
///////////////////////////////////////////////////////////////////////////////
bool 
testwave_app::preprocess_file(std::string filename, std::string const& instr, 
    std::string& result, std::string& error)
{
//  create the wave::context object and initialise it from the file to 
//  preprocess (may contain options inside of special comments)
    typedef boost::wave::cpplexer::lex_token<> token_type;
    typedef boost::wave::cpplexer::lex_iterator<token_type> lexer_type;
    typedef boost::wave::context<std::string::const_iterator, lexer_type> 
        context_type;

    try {    
    //  create preprocesing context
        context_type ctx(instr.begin(), instr.end(), filename.c_str());

    //  initialise the context from the options given on the command line
        if (!initialise_options(ctx, global_vm))
            return false;

    //  extract the options from the input data and initialise the context 
        if (!extract_options(filename, instr, ctx))
            return false;

    //  preprocess the input, loop over all generated tokens collecting the 
    //  generated text 
        context_type::iterator_type end = ctx.end();
        for (context_type::iterator_type it = ctx.begin(); it != end; ++it) 
        {
            using namespace boost::wave;
            
            if (T_PP_LINE == token_id(*it)) {
            // special handling of the whole #line directive is required to
            // allow correct file name matching
                if (!handle_line_directive(it, end, result))
                    return false;   // unexpected eof
            }
            else {
                // add the value of the current token 
                result = result + (*it).get_value().c_str();  
            }
        }
        
        error.clear();
    }
    catch (boost::wave::cpplexer::lexing_exception const& e) {
    // some lexer error
        TESTWAVE_OSSTREAM strm;
        std::string filename = e.file_name();
        strm 
            << handle_filepath(filename) << "(" << e.line_no() << "): "
            << e.description() << std::endl;
            
        error = TESTWAVE_GETSTRING(strm);
        return false;
    }
    catch (boost::wave::cpp_exception const& e) {
    // some preprocessing error
        TESTWAVE_OSSTREAM strm;
        std::string filename = e.file_name();
        strm 
            << handle_filepath(filename) << "(" << e.line_no() << "): "
            << e.description() << std::endl;
            
        error = TESTWAVE_GETSTRING(strm);
        return false;
    }
    
    return true;
}

