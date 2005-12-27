///////////////////////////////////////////////////////////////////////////////
// test10.hpp
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

    static char_type const *nilbr = 0;
    static test_case const test_cases[] =
    {
        test_case // test16
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
          , backrefs(L("barboo"), nilbr)
        )
      , test_case // test18
        (
            L("foobarboo")
          , L("b.+oo$")
          , regex_type(L('b') >> +_ >> L("oo") >> eos)
          , L("")
          , backrefs(L("barboo"), nilbr)
        )
      , test_case // test19
        (
            L("+1234.56789F")
          , L("^([-+]?[0-9]+(\\.[0-9]*)?)([CF])$")
          , regex_type(bos >> (s1= !(set=L('-'),L('+')) >> +range(L('0'),L('9'))
                           >> !(s2= L('.') >> *range(L('0'),L('9'))))
                           >> (s3= (set=L('C'),L('F'))) >> eos)
          , L("")
          , backrefs(L("+1234.56789F"), L("+1234.56789"), L(".56789"), L("F"), nilbr)
        )
      , test_case // test20
        (
            L("+1234.56789")
          , L("(\\+|-)?([0-9]+\\.?[0-9]*|\\.[0-9]+)([eE](\\+|-)?[0-9]+)?")
          , regex_type( !(s1= as_xpr(L('+'))|L('-')) >> (s2= +range(L('0'),L('9')) >> !as_xpr(L('.')) >> *range(L('0'),L('9')) |
                        L('.') >> +range(L('0'),L('9'))) >> !(s3= (set=L('e'),L('E')) >> !(s4= as_xpr(L('+'))|L('-')) >> +range(L('0'),L('9'))))
          , L("")
          , backrefs(L("+1234.56789"), L("+"), L("1234.56789"), L(""), L(""), nilbr)
        )
      , test_case // test166
        (
            L("G")
          , L("f|(?i)g")
          , regex_type(L('f') | icase(L('g')))
          , L("")
          , backrefs(L("G"), nilbr)
        )
      , test_case // test167
        (
            L("aBBa")
          , L("[[:lower:]]+")
          , regex_type(icase(+lower))
          , L("i")
          , backrefs(L("aBBa"), nilbr)
        )
      , test_case // test168
        (
            L("aA")
          , L("\\x61+")
          , regex_type(icase(+as_xpr(L('\x61'))))
          , L("i")
          , backrefs(L("aA"), nilbr)
        )
      , test_case // test169
        (
            L("aA")
          , L("[\\x61]+")
          , regex_type(icase(+set[L('\x61')]))
          , L("i")
          , backrefs(L("aA"), nilbr)
        )
      , test_case // test170
        (
            L("aA")
          , L("\\u0061+")
          , regex_type(icase(+as_xpr(L('\x0061'))))
          , L("i")
          , backrefs(L("aA"), nilbr)
        )
      , test_case // test171
        (
            L("aA")
          , L("[\\u0061]+")
          , regex_type(icase(+set[L('\x0061')]))
          , L("i")
          , backrefs(L("aA"), nilbr)
        )

    };

    return boost::make_iterator_range(test_cases);
}

