///////////////////////////////////////////////////////////////////////////////
/// \file arg.hpp
/// Contains definition of the argN transforms.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_11_01_2007
#define BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_11_01_2007

#include <boost/proto/detail/prefix.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/detail/suffix.hpp>

namespace boost { namespace proto
{

    /// \brief A PrimitiveTransform that returns the current expression
    /// unmodified
    struct _expr : transform<_expr>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param expr An expression
            /// \return \c expr
            /// \throw nothrow
            typename impl::expr_param operator()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return expr;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns the current state
    /// unmodified
    struct _state : transform<_state>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef State result_type;

            /// \param state The current state.
            /// \return \c state
            /// \throw nothrow
            typename impl::state_param operator ()(
                typename impl::expr_param
              , typename impl::state_param state
              , typename impl::data_param
            ) const
            {
                return state;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns the current data
    /// unmodified
    struct _data : transform<_data>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Data result_type;

            /// \param state The current data.
            /// \return \c data
            /// \throw nothrow
            typename impl::data_param operator ()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                return data;
            }
        };
    };

    /// \brief A PrimitiveTransform that returns I-th child of the current
    /// expression.
    template<int I>
    struct _child_c : transform<_child_c<I> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef
                typename result_of::child_c<Expr, I>::type
            result_type;

            /// \param expr The current expression.
            /// \return <tt>proto::child_c\<I\>(expr)</tt>
            /// \throw nothrow
            typename result_of::child_c<typename impl::expr_param, I>::type
            operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return proto::child_c<I>(expr);
            }
        };
    };

    /// \brief A PrimitiveTransform that returns the value of the
    /// current terminal expression.
    struct _value : transform<_value>
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef
                typename result_of::value<Expr>::type
            result_type;

            /// \param expr The current expression.
            /// \return <tt>proto::value(expr)</tt>
            /// \throw nothrow
            typename result_of::value<typename impl::expr_param>::type
            operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return proto::value(expr);
            }
        };
    };

    /// \brief A unary CallableTransform that wraps its argument
    /// in a \c boost::reference_wrapper\<\>.
    struct _byref : callable
    {
        template<typename Sig>
        struct result;

        template<typename This, typename T>
        struct result<This(T)>
        {
            typedef boost::reference_wrapper<T const> const type;
        };

        template<typename This, typename T>
        struct result<This(T &)>
        {
            typedef boost::reference_wrapper<T> const type;
        };

        /// \param t The object to wrap
        /// \return <tt>boost::ref(t)</tt>
        /// \throw nothrow
        template<typename T>
        boost::reference_wrapper<T> const operator ()(T &t) const
        {
            return boost::reference_wrapper<T>(t);
        }

        /// \overload
        ///
        template<typename T>
        boost::reference_wrapper<T const> const operator ()(T const &t) const
        {
            return boost::reference_wrapper<T const>(t);
        }
    };

    /// \brief A unary CallableTransform that strips references
    /// from its argument.
    struct _byval : callable
    {
        template<typename Sig>
        struct result;

        template<typename This, typename T>
        struct result<This(T)>
        {
            typedef T type;
        };

        template<typename This, typename T>
        struct result<This(T &)>
          : result<This(T)>
        {};

        template<typename This, typename T>
        struct result<This(boost::reference_wrapper<T>)>
          : result<This(T)>
        {};

        /// \param t The object to unref
        /// \return <tt>t</tt>
        /// \throw nothrow
        template<typename T>
        T const &operator ()(T const &t) const
        {
            return t;
        }

        /// \overload
        ///
        template<typename T>
        T &operator ()(boost::reference_wrapper<T> const &t) const
        {
            return t;
        }
    };

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_expr>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_state>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_data>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<int I>
    struct is_callable<_child_c<I> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_value>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_byref>
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<>
    struct is_callable<_byval>
      : mpl::true_
    {};

}}

#endif
