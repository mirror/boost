// Copyright Frank Mori Hess 2009
//
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_DETAIL_VARIADIC_ARG_TYPE_HPP
#define BOOST_SIGNALS2_DETAIL_VARIADIC_ARG_TYPE_HPP

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      template<unsigned, typename ... Args> class variadic_arg_type;

      template<typename T, typename ... Args> class variadic_arg_type<0, T, Args...>
      {
      public:
        typedef T type;
      };

      template<unsigned n, typename T, typename ... Args> class variadic_arg_type<n, T, Args...>
      {
      public:
        typedef typename variadic_arg_type<n - 1, Args...>::type type;
      };
    } // namespace detail
  } // namespace signals2
} // namespace boost


#endif // BOOST_SIGNALS2_DETAIL_VARIADIC_ARG_TYPE_HPP
