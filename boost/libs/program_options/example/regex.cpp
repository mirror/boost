// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/program_options.hpp>
#include <boost/regex.hpp>

using namespace boost;
using namespace boost::program_options;

#include <iostream>
using namespace std;

/* This validator makes sure that value is of form
   XXX-XXX 
   where X are digits. It then converts the second group to a integer
   value. This has no practical meaning, meant only to show how
   regex can be used to validate values.
*/
void fancy_parameter_validator(boost::any& a, 
                               const std::vector<std::string>& values)
{
    static regex r("\\d\\d\\d-(\\d\\d\\d)");

    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurence(a);
    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    const string& s = validators::get_single_string(values);

    // Do regex match and convert the interesting part to 
    // int.
    smatch match;
    if (regex_match(s, match, r)) {
        a = any(lexical_cast<int>(match[1]));
    } else {
        throw validation_error("invalid value");
    }        
}


int main(int ac, const char **av)
{
    try {
        options_description desc("Allowed options");
        desc.add_options()
        ("help", "", "produce a help screen")
        ("version,v", "", "print the version number")
        ("magic,m", "arg", "magic value (in NNN-NNN format)").
             validator(fancy_parameter_validator)
        ;
        
        options_and_arguments oa = parse_command_line(ac, av, desc);
        variables_map vm;
        store(oa, vm, desc);
   
        if (oa.count("help")) {
            cout << "Usage: regex [options]\n";
            cout << desc;
            return 0;
        }
        if (oa.count("version")) {
            cout << "Version 1.\n";
            return 0;
        }
        if (oa.count("magic")) {
            cout << "The magic is \"" << vm["magic"].as<int>() << "\"\n";
        }
    }
    catch(exception& e)
    {
        cout << e.what() << "\n";
    }    
}
