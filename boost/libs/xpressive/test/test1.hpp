///////////////////////////////////////////////////////////////////////////////
// test1.h
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
        test_case // test1
        (
            L("foobarboo")
          , L("foo")
          , regex_type(as_xpr(L("foo")))
          , L("")
          , backrefs(L("foo"), nil)
        )
      , test_case // test2
        (
            L("foobarboo")
          , L("bar")
          , regex_type(as_xpr(L("bar")))
          , L("")
          , backrefs(L("bar"), nil)
        )
      , test_case // test3
        (
            L("foobarboo")
          , L("bat")
          , regex_type(as_xpr(L("bat")))
          , L("")
          , no_match
        )
      , test_case // test4
        (
            L("foobarboo")
          , L("b.*ar")
          , regex_type(L('b') >> *_ >> L("ar"))
          , L("")
          , backrefs(L("bar"), nil)
        )
      , test_case // test5
        (
            L("foobarboo")
          , L("b.*r")
          , regex_type(L('b') >> *_ >> L('r'))
          , L("")
          , backrefs(L("bar"), nil)
        )
      , test_case // test6
        (
            L("foobarboo")
          , L("b.*b")
          , regex_type(L('b') >> *_ >> L('b'))
          , L("")
          , backrefs(L("barb"), nil)
        )
      , test_case // test7
        (
            L("foobarboo")
          , L("b.*o")
          , regex_type(L('b') >> *_ >> L('o'))
          , L("")
          , backrefs(L("barboo"), nil)
        )
      , test_case // test8
        (
            L("foobarboo")
          , L("b.*oo")
          , regex_type(L('b') >> *_ >> L("oo"))
          , L("")
          , backrefs(L("barboo"), nil)
        )
      , test_case // test9
        (
            L("foobarboo")
          , L("b.+ar")
          , regex_type(L('b') >> +_ >> L("ar"))
          , L("")
          , no_match
        )
      , test_case // test10
        (
            L("foobarboo")
          , L("b.+r")
          , regex_type(L('b') >> +_ >> L('r'))
          , L("")
          , backrefs(L("bar"), nil)
        )
      , test_case // test11
        (
            L("foobarboo")
          , L("b.+b")
          , regex_type(L('b') >> +_ >> L('b'))
          , L("")
          , backrefs(L("barb"), nil)
        )
      , test_case // test12
        (
            L("foobarboo")
          , L("b.+o")
          , regex_type(L('b') >> +_ >> L('o'))
          , L("")
          , backrefs(L("barboo"), nil)
        )
      , test_case // test13
        (
            L("foobarboo")
          , L("b.+oo")
          , regex_type(L('b') >> +_ >> L("oo"))
          , L("")
          , backrefs(L("barboo"), nil)
        )
      , test_case // test14
        (
            L("foobarboo")
          , L("^foo")
          , regex_type(bos >> L("foo"))
          , L("")
          , backrefs(L("foo"), nil)
        )
      , test_case // test15
        (
            L("foobarboo")
          , L("^b.*ar")
          , regex_type(bos >> L('b') >> *_ >> L("ar"))
          , L("")
          , no_match
        )
      , test_case // test16
        (
            L("foobarboo")
          , L("b.+ar$")
          , regex_type(L('b') >> +_ >> L("ar") >> eos)
          , L("")
          , no_match
        )
      , test_case // test17
        (
            L("foobarboo")
          , L("b.+o$")
          , regex_type(L('b') >> +_ >> L('o') >> eos)
          , L("")
          , backrefs(L("barboo"), nil)
        )
      , test_case // test18
        (
            L("foobarboo")
          , L("b.+oo$")
          , regex_type(L('b') >> +_ >> L("oo") >> eos)
          , L("")
          , backrefs(L("barboo"), nil)
        )
      , test_case // test19
        (
            L("+1234.56789F")
          , L("^([-+]?[0-9]+(\\.[0-9]*)?)([CF])$")
          , regex_type(bos >> (s1= !(set=L('-'),L('+')) >> +range(L('0'),L('9'))
                           >> !(s2= L('.') >> *range(L('0'),L('9'))))
                           >> (s3= (set=L('C'),L('F'))) >> eos)
          , L("")
          , backrefs(L("+1234.56789F"), L("+1234.56789"), L(".56789"), L("F"), nil)
        )
      , test_case // test20
        (
            L("+1234.56789")
          , L("(\\+|-)?([0-9]+\\.?[0-9]*|\\.[0-9]+)([eE](\\+|-)?[0-9]+)?")
          , regex_type( !(s1= as_xpr(L('+'))|L('-')) >> (s2= +range(L('0'),L('9')) >> !as_xpr(L('.')) >> *range(L('0'),L('9')) |
                        L('.') >> +range(L('0'),L('9'))) >> !(s3= (set=L('e'),L('E')) >> !(s4= as_xpr(L('+'))|L('-')) >> +range(L('0'),L('9'))))
          , L("")
          , backrefs(L("+1234.56789"), L("+"), L("1234.56789"), L(""), L(""), nil)
        )
    };

    return boost::make_iterator_range(test_cases);
}

