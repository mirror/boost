/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_WAVE_LIBS_WAVE_TEST_TESTWAVE_APP_HPP)
#define BOOST_WAVE_LIBS_WAVE_TEST_TESTWAVE_APP_HPP

#include <string>
#include <vector>

// include boost
#include <boost/config.hpp>

#include "cmd_line_utils.hpp"

///////////////////////////////////////////////////////////////////////////////
class testwave_app
{
public:
    testwave_app(boost::program_options::variables_map const& vm);
    
    //  Test the given file (i.e. preprocess the file and compare the result 
    //  against the embedded 'R' comments, if an error occurs compare the error
    //  message against the given 'E' comments).
    bool test_a_file(std::string filename);
    
    //  print the current version of this program
    int print_version();
    
    //  print the copyright statement
    int print_copyright();

    // access the common options used for the command line and the config
    // options inside the test files
    boost::program_options::options_description const& common_options() const
    { 
        return desc_options; 
    }
    
    void set_debuglevel(int debuglevel_)
    {
        debuglevel = debuglevel_;
    }
    int get_debuglevel() const
    {
        return debuglevel;
    }
    
protected:
    //  Read the given file into a string
    bool read_file(std::string const& filename, std::string& instr);

    //  Extract special information from comments marked with the given letter
    bool extract_special_information(std::string const& filename, 
        std::string const& instr, char flag, std::string& content);

    //  Extract the expected output from the given input data
    //  The expected output has to be provided inside of special comments which
    //  start with a capital 'R'. All such comments are concatenated and 
    //  returned through the parameter 'expected'.
    bool extract_expected_output(std::string const& filename, 
        std::string const& instr, std::string& expected);
        
    //  Extracts the required preprocessing options from the given input data 
    //  and initialises the given Wave context object accordingly. 
    //  We allow the same (applicable) options to be used as are valid for the 
    //  wave driver executable.
    template <typename Context>
    bool extract_options(std::string const& filename, 
        std::string const& instr, Context& ctx);

    //  transfers the options collected in the vm parameter into the given 
    //  context
    template <typename Context>
    bool initialise_options(Context& ctx, 
        boost::program_options::variables_map const& vm);

    //  Preprocess the given input data and return the generated output through 
    //  the parameter 'result'.
    bool preprocess_file(std::string filename, std::string const& instr, 
        std::string& result, std::string& error);


private:
    int debuglevel;
    boost::program_options::options_description desc_options;
    boost::program_options::variables_map const& global_vm;
};

#endif // !defined(BOOST_WAVE_LIBS_WAVE_TEST_TESTWAVE_APP_HPP)
