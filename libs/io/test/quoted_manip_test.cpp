//  libs/io/test/quote_manip_test.cpp  -----------------------------------------------  //

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/io

//  ----------------------------------------------------------------------------------  //

#include <boost/io/detail/quoted_manip.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <sstream>

using boost::io::quoted;
using std::string;
using std::wstring;

int main()
{

  std::stringstream ss;
  std::wstringstream wss;

  const string s1("foo\\bar, \" *");
  string r; // test results

  ss << quoted(s1);
  ss >> r;
  BOOST_TEST_EQ(r, "\"foo\\\\bar, \\\" *\"");

  ss << quoted(s1.c_str());
  ss >> r;
  BOOST_TEST_EQ(r, "\"foo\\\\bar, \\\" *\"");

  ss << quoted(s1);
  ss >> quoted(r);
  BOOST_TEST_EQ(r, s1);

  ss << quoted(s1.c_str());
  ss >> quoted(r);
  BOOST_TEST_EQ(r, s1);

  string s2("'Jack & Jill'");                                 

  ss << quoted(s2, '&', '\'');
  ss >> r;
  BOOST_TEST_EQ(r, "'&'Jack && Jill&''");

  ss << quoted(s2, '&', '\'');
  ss >> quoted(r, '&', '\'');
  BOOST_TEST_EQ(r, s2);

  wstring ws1(L"foo$bar, \" *");
  wstring wr; // test results

  wss << quoted(ws1, L'$');
  wss >> wr;
  BOOST_TEST(wr == wstring(L"\"foo$$bar, $\" *\""));

  wss << quoted(ws1, L'$');
  wss >> quoted(wr,  L'$');
  BOOST_TEST(wr == ws1);

  const string s3("const string");
  ss << quoted(s3);
  ss >> quoted(r);
  BOOST_TEST_EQ(r, s3);

  //  missing end delimiter test
  ss << "\"abc";      // load ss with faulty quoting
  ss >> quoted(r);    // this loops if istream error/eof not detected
  BOOST_TEST_EQ(r, "abc");

  //  no initial delmiter test
  ss << "abc";
  ss >> quoted(r);
  BOOST_TEST_EQ(r, "abc");

  //  no initial delmiter, space in ss
  ss << "abc def";
  ss >> quoted(r);
  BOOST_TEST_EQ(r, "abc");

  // these should fail to compile because the arguments are const:
  //   ss >> quoted(s1);
  //   ss >> quoted("foo");

  return 0;
}
