// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
using namespace boost::program_options;
// We'll use po::value everywhere to workaround vc6 bug.
namespace po = boost::program_options;

#include <boost/function.hpp>
using namespace boost;

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>

#include <sstream>
using namespace std;

// Test that unicode input is forwarded to unicode option without
// problems.
void test_unicode_to_unicode()
{
    options_description desc;

    desc.add_options()
        ("foo", po::wvalue<wstring>(), "unicode option")
        ;

    vector<wstring> args;
    args.push_back(L"--foo=\x044F");

    variables_map vm;
    store(wcommand_line_parser(args).options(desc).run(), vm);

    BOOST_CHECK(vm["foo"].as<wstring>() == L"\x044F");           
}

// Test that unicode input is property converted into
// local 8 bit string. To test this, make local 8 bit encoding
// be utf8.
void test_unicode_to_native()
{
    std::codecvt<wchar_t, char, mbstate_t>* facet = 
        new boost::program_options::detail::utf8_codecvt_facet<wchar_t, char>;
    locale::global(locale(locale(), facet));

    options_description desc;

    desc.add_options()
        ("foo", po::value<string>(), "unicode option")
        ;

    vector<wstring> args;
    args.push_back(L"--foo=\x044F");

    variables_map vm;
    store(wcommand_line_parser(args).options(desc).run(), vm);

    BOOST_TEST(vm["foo"].as<string>() == "\xD1\x8F");    
}

void test_native_to_unicode()
{
    std::codecvt<wchar_t, char, mbstate_t>* facet = 
        new boost::program_options::detail::utf8_codecvt_facet<wchar_t, char>;
    locale::global(locale(locale(), facet));

    options_description desc;

    desc.add_options()
        ("foo", po::wvalue<wstring>(), "unicode option")
        ;

    vector<string> args;
    args.push_back("--foo=\xD1\x8F");

    variables_map vm;
    store(command_line_parser(args).options(desc).run(), vm);

    BOOST_TEST(vm["foo"].as<wstring>() == L"\x044F");    
}

// Since we've already tested conversion between parser encoding and
// option encoding, all we need to check for config file is that
// when reading wistream, it generates proper UTF8 data.
void test_config_file()
{
    std::codecvt<wchar_t, char, mbstate_t>* facet = 
        new boost::program_options::detail::utf8_codecvt_facet<wchar_t, char>;
    locale::global(locale(locale(), facet));

    options_description desc;

    desc.add_options()
        ("foo", po::value<string>(), "unicode option")
        ;

    std::wstringstream stream(L"foo = \x044F");

    variables_map vm;
    store(parse_config_file(stream, desc), vm);

    BOOST_TEST(vm["foo"].as<string>() == "\xD1\x8F");    
}

int test_main(int, char* [])
{
    test_unicode_to_unicode();
    test_unicode_to_native();
    test_native_to_unicode();
    test_config_file();
    return 0;
}

