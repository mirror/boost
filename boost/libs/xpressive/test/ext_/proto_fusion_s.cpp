///////////////////////////////////////////////////////////////////////////////
// proto_fusion.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/fusion.hpp>
#include <boost/fusion/algorithm/iteration/ext_/for_each_s.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>

boost::proto::meta::terminal<char>::type a_ = {'a'};
boost::proto::meta::terminal<char>::type b_ = {'b'};
boost::proto::meta::terminal<char>::type c_ = {'c'};
boost::proto::meta::terminal<char>::type d_ = {'d'};
boost::proto::meta::terminal<char>::type e_ = {'e'};
boost::proto::meta::terminal<char>::type f_ = {'f'};
boost::proto::meta::terminal<char>::type g_ = {'g'};
boost::proto::meta::terminal<char>::type h_ = {'h'};
boost::proto::meta::terminal<char>::type i_ = {'i'};

std::ostream &operator <<(std::ostream &sout, boost::proto::right_shift_tag)
{
    return sout << ">>";
}

std::ostream &operator <<(std::ostream &sout, boost::proto::bitor_tag)
{
    return sout << "|";
}

template<typename Args>
std::ostream &operator <<(std::ostream &sout, boost::proto::basic_expr<boost::proto::terminal_tag, Args, 1> const &op)
{
    return sout << boost::proto::arg(op);
}

template<typename Tag, typename Args>
std::ostream &operator <<(std::ostream &sout, boost::proto::basic_expr<Tag, Args, 1> const &op)
{
    return sout << Tag() << boost::proto::arg(op).cast();
}

template<typename Tag, typename Args>
std::ostream &operator <<(std::ostream &sout, boost::proto::basic_expr<Tag, Args, 2> const &op)
{
    return sout << boost::proto::left(op).cast() << Tag() << boost::proto::right(op).cast();
}

///////////////////////////////////////////////////////////////////////////////
// to_string
//
struct to_string
{
    to_string(std::ostream &sout)
      : sout_(sout)
    {}

    template<typename Op>
    void operator()(Op const &op) const
    {
        this->sout_ << '(' << op << ')';
    }
private:
    std::ostream &sout_;
};

void test1()
{
    std::stringstream sout;

    // Test for 1-way branching "tree"
    sout.str("");
    boost::fusion::for_each_s(!!!!(a_ >> b_), to_string(sout));
    BOOST_CHECK_EQUAL("(a>>b)", sout.str());

    // Tests for 2-way branching trees
    sout.str("");
    boost::fusion::for_each_s(a_ >> b_ >> c_, to_string(sout));
    BOOST_CHECK_EQUAL("(a)(b)(c)", sout.str());

    sout.str("");
    boost::fusion::for_each_s(a_ | b_ | c_, to_string(sout));
    BOOST_CHECK_EQUAL("(a)(b)(c)", sout.str());

    sout.str("");
    boost::fusion::for_each_s(a_ >> b_ | c_ >> d_, to_string(sout));
    BOOST_CHECK_EQUAL("(a>>b)(c>>d)", sout.str());

    sout.str("");
    boost::fusion::for_each_s(a_ | b_ >> c_ | d_, to_string(sout));
    BOOST_CHECK_EQUAL("(a)(b>>c)(d)", sout.str());

    sout.str("");
    boost::fusion::for_each_s(a_ >> b_ | c_ >> d_ | e_ >> f_ >> g_, to_string(sout));
    BOOST_CHECK_EQUAL("(a>>b)(c>>d)(e>>f>>g)", sout.str());

    sout.str("");
    boost::fusion::for_each_s(a_ >> b_ | c_ >> d_ | e_ >> (f_ | g_) >> h_, to_string(sout));
    BOOST_CHECK_EQUAL("(a>>b)(c>>d)(e>>f|g>>h)", sout.str());

    // Test for n-way branching tree
    sout.str("");
    boost::fusion::for_each_s(a_(b_(c_ >> d_, e_ | f_), g_ >> h_)(i_), to_string(sout));
    BOOST_CHECK_EQUAL("(a)(b)(c>>d)(e|f)(g>>h)(i)", sout.str());
}

using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test proto and segmented fusion integration");

    test->add(BOOST_TEST_CASE(&test1));

    return test;
}
