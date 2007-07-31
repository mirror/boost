
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/is_callable_builtin.hpp>

namespace ft = boost::function_types;
namespace mpl = boost::mpl;

typedef ft::stdcall_cc cc;
typedef ft::default_cc dc;

class C; 

BOOST_MPL_ASSERT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C &>, cc>::type, cc >
));

BOOST_MPL_ASSERT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C const &>, cc>::type, cc >
));

BOOST_MPL_ASSERT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C volatile &>, cc>::type, cc >
));

BOOST_MPL_ASSERT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C const volatile &>, cc>::type, cc >
));

BOOST_MPL_ASSERT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C &> >::type, dc >
));

BOOST_MPL_ASSERT_NOT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C &>, cc>::type, dc >
));

BOOST_MPL_ASSERT_NOT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C const &>, cc>::type, dc >
));

BOOST_MPL_ASSERT_NOT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C volatile &>, cc>::type, dc >
));

BOOST_MPL_ASSERT_NOT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C const volatile &>, cc>::type, dc >
));

BOOST_MPL_ASSERT_NOT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C &> >::type, cc >
));

BOOST_MPL_ASSERT_NOT((
  ft::is_callable_builtin< ft::member_function_pointer<mpl::vector<int, C &>, cc>::type, dc >
));

