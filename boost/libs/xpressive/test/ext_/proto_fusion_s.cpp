///////////////////////////////////////////////////////////////////////////////
// proto_fusion.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/fusion.hpp>
#include <boost/xpressive/proto/ext_/fusion_s.hpp>
#include <boost/fusion/algorithm/iteration/ext_/for_each_s.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>

boost::proto::unary_op<char, boost::proto::noop_tag> a_('a');
boost::proto::unary_op<char, boost::proto::noop_tag> b_('b');
boost::proto::unary_op<char, boost::proto::noop_tag> c_('c');
boost::proto::unary_op<char, boost::proto::noop_tag> d_('d');
boost::proto::unary_op<char, boost::proto::noop_tag> e_('e');
boost::proto::unary_op<char, boost::proto::noop_tag> f_('f');
boost::proto::unary_op<char, boost::proto::noop_tag> g_('g');
boost::proto::unary_op<char, boost::proto::noop_tag> h_('h');
boost::proto::unary_op<char, boost::proto::noop_tag> i_('i');

std::ostream &operator <<(std::ostream &sout, boost::proto::noop_tag)
{
    return sout;
}

std::ostream &operator <<(std::ostream &sout, boost::proto::right_shift_tag)
{
    return sout << ">>";
}

std::ostream &operator <<(std::ostream &sout, boost::proto::bitor_tag)
{
    return sout << "|";
}

template<typename A, typename Tag>
std::ostream &operator <<(std::ostream &sout, boost::proto::unary_op<A,Tag> const &op)
{
    return sout << Tag() << boost::proto::arg(op);
}

template<typename A, typename B, typename Tag>
std::ostream &operator <<(std::ostream &sout, boost::proto::binary_op<A,B,Tag> const &op)
{
    return sout << boost::proto::left(op) << Tag() << boost::proto::right(op);
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
