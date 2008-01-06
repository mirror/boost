
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/algorithm/string/predicate.hpp>

//[case_insensitive_functions
    struct iequal_to
        : std::binary_function<std::string, std::string, bool>
    {
        bool operator()(std::string const& x,
            std::string const& y) const
        {
            return boost::algorithm::iequals(x, y, std::locale());
        }
    };

    struct ihash
        : std::unary_function<std::string, std::size_t>
    {
        std::size_t operator()(std::string const& x) const
        {
            std::size_t seed = 0;
            std::locale locale;

            for(std::string::const_iterator it = x.begin();
                it != x.end(); ++it)
            {
                boost::hash_combine(seed, std::toupper(*it, locale));
            }

            return seed;
        }
    };

    struct word_info;
//]

    struct word_info {
        int tag;
        explicit word_info(int t = 0) : tag(t) {}
    };

int main() {
//[case_insensitive_dictionary
    boost::unordered_map<std::string, word_info, ihash, iequal_to>
        idictionary;
//]

    BOOST_TEST(idictionary.empty());

    idictionary["one"] = word_info(1);
    BOOST_TEST(idictionary.size() == 1);
    BOOST_TEST(idictionary.find("ONE") != idictionary.end() &&
        idictionary.find("ONE") == idictionary.find("one"));

    idictionary.insert(std::make_pair("ONE", word_info(2)));
    BOOST_TEST(idictionary.size() == 1);
    BOOST_TEST(idictionary.find("ONE") != idictionary.end() &&
            idictionary.find("ONE")->first == "one" &&
            idictionary.find("ONE")->second.tag == 1);

    idictionary["One"] = word_info(3);
    BOOST_TEST(idictionary.size() == 1);
    BOOST_TEST(idictionary.find("ONE") != idictionary.end() &&
            idictionary.find("ONE")->first == "one" &&
            idictionary.find("ONE")->second.tag == 3);

    idictionary["two"] = word_info(4);
    BOOST_TEST(idictionary.size() == 2);
    BOOST_TEST(idictionary.find("two") != idictionary.end() &&
            idictionary.find("TWO")->first == "two" &&
            idictionary.find("Two")->second.tag == 4);

    return boost::report_errors();
}
