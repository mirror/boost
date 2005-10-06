///////////////////////////////////////////////////////////////////////////////
// test7.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./test.hpp"

///////////////////////////////////////////////////////////////////////////////
// get_test_cases
//
template<typename BidiIterT>
boost::iterator_range<test_case<BidiIterT> const *> get_test_cases()
{
    typedef typename boost::iterator_value<BidiIterT>::type char_type;
    typedef test_case<BidiIterT> test_case;
    typedef basic_regex<BidiIterT> regex_type;

    static char_type const *nil = 0;
    static test_case const test_cases[] =
    {
        test_case // test127
        (
            L("foobar")
          , L("foo(?#This is a comment[)bar")
          , regex_type(as_xpr(L("foo")) >> /*This is a comment[*/ L("bar"))
          , L("")
          , backrefs(L("foobar"), nil)
        )
      , test_case // test128
        (
            L("foobar")
          , L("^ f oo b ar $")
          , regex_type(bos >> L("foobar") >> eos)
          , L("x")
          , backrefs(L("foobar"), nil)
        )
      , test_case // test129
        (
            L("foobar")
          , L("^ f o *")
          , regex_type(bos >> L('f') >> *as_xpr(L('o')))
          , L("x")
          , backrefs(L("foo"), nil)
        )
      , test_case // test129a
        (
            L("foobar")
          , L("^ f \\157 *")
          , regex_type(bos >> L('f') >> *as_xpr(L('\157')))
          , L("x")
          , backrefs(L("foo"), nil)
        )
      , test_case // test130
        (
            L("foo bar")
          , L("^ f oo\\  b ar $")
          , regex_type(bos >> L("foo bar") >> eos)
          , L("x")
          , backrefs(L("foo bar"), nil)
        )
      , test_case // test131
        (
            L("foo bar")
          , L("^ f oo [ ] b ar $")
          , regex_type(bos >> L("foo") >> set[L(' ')] >> L("bar") >> eos)
          , L("x")
          , backrefs(L("foo bar"), nil)
        )
      , test_case // test132
        (
            L("foo bar")
          , L("^ ( ? : f oo [ ] b ar ) $ # This is a comment")
          , regex_type(bos >> (L("foo") >> set[L(' ')] >> L("bar")) >> eos /*This is a comment*/)
          , L("x")
          , backrefs(L("foo bar"), nil)
        )
      , test_case // test133
        (
            L("foo bar")
          , L("^ f oo [ ] b ar # This is a comment")
          , regex_type(bos >> L("foo") >> set[L(' ')] >> L("bar") /*This is a comment*/)
          , L("x")
          , backrefs(L("foo bar"), nil)
        )
      , test_case // test134
        (
            L("foo bar#Thisisnotacomment")
          , L("^ f oo [ ] b ar \\# This is not a comment")
          , regex_type(bos >> L("foo") >> set[L(' ')] >> L("bar#Thisisnotacomment"))
          , L("x")
          , backrefs(L("foo bar#Thisisnotacomment"), nil)
        )
      , test_case // test135
        (
            L("f oo b ar")
          , L("^f o(?x)     o     (?-x) b ar")
          , regex_type(bos >> L("f oo b ar"))
          , L("")
          , backrefs(L("f oo b ar"), nil)
        )
      , test_case // test137
        (
            L("a--")
          , L("^(a?)*$")
          , regex_type(bos >> *(s1= optional(L('a'))) >> eos)
          , L("")
          , no_match
        )
      , test_case // test138
        (
            L("a--")
          , L("^(a?)*?$")
          , regex_type(bos >> -*(s1= optional(L('a'))) >> eos)
          , L("")
          , no_match
        )
      , test_case // test139
        (
            L("bc")
          , L("^(b?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bc"), L(""), nil)
        )
      , test_case // test140
        (
            L("bbc")
          , L("^(b?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L(""), nil)
        )
    };

    return boost::make_iterator_range(test_cases);
}
