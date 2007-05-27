/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/fusion/functional/adapter/unfused_typed.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <boost/blank.hpp>
#include <boost/noncopyable.hpp>

#include <boost/utility/result_of.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/utility/result_of.hpp>

#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

namespace fusion = boost::fusion;
namespace mpl = boost::mpl;
using mpl::placeholders::_;

using boost::noncopyable;

typedef fusion::vector<long &,int,char> types;

typedef mpl::always< mpl::true_ > unconstrained;

typedef  mpl::equal_to< fusion::result_of::size<_>,
    fusion::result_of::size<types> > non_variadic; 

template <class Base = boost::blank, class Validation = unconstrained>
struct test_func
    : Base
{
    template <class Seq> struct result
        : mpl::if_< typename mpl::apply<Validation, Seq>::type,
            mpl::identity<long>, boost::blank >::type
    { };

    template <typename Seq>
    long operator()(Seq const & seq) const
    {
        long state = 0;
        return fusion::fold(seq, state, fold_op());
    }

    template < typename Seq >
    long operator()(Seq const & seq) 
    {
        long state = 100;
        return fusion::fold(seq, state, fold_op());
    }

  private:

    struct fold_op
    {
        template <typename T>
        long operator()(T const & elem, long value) const
        {
          return value + sizeof(T) * elem;
        }

        template <typename T>
        long operator()(T & elem, long value) const
        {
          elem += sizeof(T);
          return value;
        }

        template <typename T0, typename T1> struct result
            : mpl::identity<long>
        { };
    };
};

void result_type_tests()
{
    using boost::is_same;
    using boost::fusion::detail::has_type;

    typedef fusion::unfused_typed< test_func<noncopyable, non_variadic>, types > test_func_3;
    typedef fusion::unfused_typed< test_func<noncopyable>, types > test_func_0;

    BOOST_TEST(( has_type< test_func_0::result<> >::value ));
    BOOST_TEST(( has_type< test_func_3::result<long &, int, char> >::value ));
    BOOST_TEST(( ! has_type< test_func_3::result<> >::value ));
    BOOST_TEST(( is_same< boost::result_of< test_func_0() >::type, long >::value ));
    BOOST_TEST(( is_same< boost::result_of< test_func_3(long &, int, char) >::type, long >::value ));
}

#if defined(BOOST_MSVC) && BOOST_MSVC < 1400
#   define BOOST_TEST_NO_VC71(cond) (void)((cond)?0:1)
#else
#   define BOOST_TEST_NO_VC71(cond) BOOST_TEST(cond)
#endif

int main()
{
    result_type_tests();

    test_func<noncopyable> f;
    fusion::unfused_typed< test_func<>, types > unfused_func;
    fusion::unfused_typed< test_func<noncopyable> &, types > unfused_func_ref(f);
    fusion::unfused_typed< test_func<> const, types > unfused_func_c;
    fusion::unfused_typed< test_func<>, types > const unfused_func_c2;
    fusion::unfused_typed< test_func<noncopyable> const &, types > unfused_func_c_ref(f);

    BOOST_TEST(unfused_func() == 100);
    BOOST_TEST(unfused_func_ref() == 100);
    BOOST_TEST(unfused_func_c() == 0);
    BOOST_TEST(unfused_func_c2() == 0);
    BOOST_TEST(unfused_func_c_ref() == 0);

    long lvalue = 1;
    BOOST_TEST_NO_VC71(unfused_func(lvalue) == 100);
    BOOST_TEST(lvalue == 1 + 1*sizeof(lvalue));
    BOOST_TEST(unfused_func_ref(lvalue) == 100);
    BOOST_TEST(lvalue == 1 + 2*sizeof(lvalue));
    BOOST_TEST(unfused_func_c(lvalue) == 0);
    BOOST_TEST(lvalue == 1 + 3*sizeof(lvalue));
    BOOST_TEST(unfused_func_c2(lvalue) == 0);
    BOOST_TEST(lvalue == 1 + 4*sizeof(lvalue));
    BOOST_TEST(unfused_func_c_ref(lvalue) == 0);
    BOOST_TEST(lvalue == 1 + 5*sizeof(lvalue));

    static const long expected = 2*sizeof(int) + 7*sizeof(char);
    BOOST_TEST_NO_VC71(unfused_func(lvalue,2,'\007') == 100 + expected);
    BOOST_TEST(lvalue == 1 + 6*sizeof(lvalue));
    BOOST_TEST(unfused_func_ref(lvalue,2,'\007') == 100 + expected);
    BOOST_TEST(lvalue == 1 + 7*sizeof(lvalue));
    BOOST_TEST(unfused_func_c(lvalue,2,'\007') == 0 + expected);
    BOOST_TEST(lvalue == 1 + 8*sizeof(lvalue));
    BOOST_TEST(unfused_func_c2(lvalue,2,'\007') == 0 + expected);
    BOOST_TEST(lvalue == 1 + 9*sizeof(lvalue));
    BOOST_TEST(unfused_func_c_ref(lvalue,2,'\007') == 0 + expected);
    BOOST_TEST(lvalue == 1 + 10*sizeof(lvalue));

    return boost::report_errors();
}

