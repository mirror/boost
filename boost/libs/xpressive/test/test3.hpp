///////////////////////////////////////////////////////////////////////////////
// test3.hpp
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
        test_case // test41
        (
            L("foobarFOObarfoo")
          , L("((?i)FOO)(.*?)\\1")
          , regex_type((s1= icase(L("FOO"))) >> (s2= -*_) >> s1)
          , L("")
          , backrefs(L("foobarFOObarfoo"), L("foo"), L("barFOObar"), nilbr)
        )
      , test_case // test42
        (
            L("foobarFOObarfoo")
          , L("((?i)FOO)(.*?)(?i:\\1)")
          , regex_type((s1= icase(L("FOO"))) >> (s2= -*_) >> icase(s1))
          , L("")
          , backrefs(L("foobarFOO"), L("foo"), L("bar"), nilbr)
        )
      , test_case // test42.1
        (
            L("fooFOOOFOOOOObar")
          , L("(foo|(?i:\\1O))+")
          , regex_type(+(s1= L("foo") | icase(s1 >> L('O'))))
          , L("")
          , backrefs(L("fooFOOOFOOOO"), L("FOOOO"), nilbr)
        )
      , test_case // test43
        (
            L("zoo")
          , L("^[A-Za-m]")
          , regex_type(bos >> set[range(L('A'),L('Z')) | range(L('a'),L('m'))])
          , L("")
          , no_match
        )
      , test_case // test44
        (
            L("Here is a URL: http://www.cnn.com. OK?")
          , L("(https?:/|www\\.)[\\w\\./,?@#%!_=~&-]+\\w")
          , regex_type((s1= L("http") >> !as_xpr(L('s')) >> L(":/") | L("www."))
                        >> +set[_w | (set=L('.'),L('/'),L(','),L('?'),L('@'),L('#'),L('%'),L('!'),L('_'),L('='),L('~'),L('&'),L('-'))]
                        >> _w)
          , L("")
          , backrefs(L("http://www.cnn.com"), L("http:/"), nilbr)
        )
      , test_case // test45
        (
            L("fooooooooo")
          , L("fo{2,5}")
          , regex_type(L('f') >> repeat<2,5>(L('o')))
          , L("")
          , backrefs(L("fooooo"), nilbr)
        )
      , test_case // test46
        (
            L("fooooooooo")
          , L("fo{2,5}?")
          , regex_type(L('f') >> -repeat<2,5>(L('o')))
          , L("")
          , backrefs(L("foo"), nilbr)
        )
      , test_case // test45.1
        (
            L("fooooooooo")
          , L("fo{2,5}o")
          , regex_type(L('f') >> repeat<2,5>(L('o')) >> L('o'))
          , L("")
          , backrefs(L("foooooo"), nilbr)
        )
      , test_case // test46.1
        (
            L("fooooooooo")
          , L("fo{2,5}?o")
          , regex_type(L('f') >> -repeat<2,5>(L('o')) >> L('o'))
          , L("")
          , backrefs(L("fooo"), nilbr)
        )
      , test_case // test47
        (
            L("{match this}")
          , L("^{.*}$")
          , regex_type(bos >> L('{') >> *_ >> L('}') >> eos)
          , L("")
          , backrefs(L("{match this}"), nilbr)
        )
      , test_case // test48
        (
            L("+-+-")
          , L("[+-]+")
          , regex_type(+(set=L('+'),L('-')))
          , L("")
          , backrefs(L("+-+-"), nilbr)
        )
      , test_case // test49
        (
            L("+-+-")
          , L("[-+]+")
          , regex_type(+(set=L('-'),L('+')))
          , L("")
          , backrefs(L("+-+-"), nilbr)
        )
      , test_case // test50
        (
            L("\\05g-9e")
          , L("[\\d-g]+")
          , regex_type(+set[_d | L('-') | L('g')])
          , L("")
          , backrefs(L("05g-9"), nilbr)
        )
      , test_case // test51
        (
            L("\\05g-9e")
          , L("[\\d-\\g]+")
          , regex_type(+set[_d | L('-') | L('g')])
          , L("")
          , backrefs(L("05g-9"), nilbr)
        )
      , test_case // test52
        (
            L("\\05g-9e")
          , L("[g-\\d]+")
          , regex_type(+set[L('g') | as_xpr(L('-')) | _d])
          , L("")
          , backrefs(L("05g-9"), nilbr)
        )
      , test_case // test53
        (
            L("\\05g-9e")
          , L("[\\g-\\d]+")
          , regex_type(+set[L('g') | as_xpr(L('-')) | _d])
          , L("")
          , backrefs(L("05g-9"), nilbr)
        )
      , test_case // test54
        (
            L("aBcdefg\\")
          , L("[a-\\g]+")
          , regex_type(icase(+range(L('a'),L('g'))))
          , L("i")
          , backrefs(L("aBcdefg"), nilbr)
        )
      , test_case // test55
        (
            L("ab/.-ba")
          , L("[--/]+")
          , regex_type(+range(L('-'),L('/')))
          , L("")
          , backrefs(L("/.-"), nilbr)
        )
      , test_case // test56
        (
            L("ab+,-ba")
          , L("[+--]+")
          , regex_type(+range(L('+'),L('-')))
          , L("")
          , backrefs(L("+,-"), nilbr)
        )
      , test_case // test56.1
        (
            L("aaabbbb----")
          , L("[b-b]+")
          , regex_type(+range(L('b'),L('b')))
          , L("")
          , backrefs(L("bbbb"), nilbr)
        )
      , test_case // test57
        (
            L("foobarFOO5")
          , L("(foo).*\\15")
          , regex_type(icase((s1= L("foo")) >> *_ >> L('\15')))
          , L("i")
          , no_match
        )
      , test_case // test58
        (
            L("Her number is 804-867-5309.")
          , L("(?:\\d{3}-){2}\\d{4}")
          , regex_type(repeat<2>(repeat<3>(_d) >> L('-')) >> repeat<4>(_d))
          , L("")
          , backrefs(L("804-867-5309"), nilbr)
        )
      , test_case // test59
        (
            L("foo")
          , L("fo+")
          , regex_type(L('f') >> +as_xpr(L('o')))
          , L("")
          , backrefs(L("foo"), nilbr)
        )
      , test_case // test60
        (
            L("fooFOObar")
          , L("(foo)+foobar")
          , regex_type(icase(+(s1= L("foo")) >> L("foobar")))
          , L("i")
          , backrefs(L("fooFOObar"), L("foo"), nilbr)
        )
    };

    return boost::make_iterator_range(test_cases);
}
