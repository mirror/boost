/*=============================================================================
    Copyright (c) 2005-2011 Joel de Guzman
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_THIS_HPP
#define BOOST_PHOENIX_SCOPE_THIS_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/type_traits/remove_pointer.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(this_function)
  , (meta_grammar)(meta_grammar)
  , BOOST_PHOENIX_LIMIT
)

namespace boost { namespace phoenix {

    template <typename Expr>
    struct this_actor;

    namespace detail
    {
        template <typename Dummy>
        struct this_placeholder {};
        
        struct infinite_recursion_detected {};

        struct last_non_this_actor
            : proto::or_<
                proto::when<
                    proto::nary_expr<
                        proto::_
                      , proto::_
                      , proto::_
                    >
                  , proto::_child_c<1>
                >
              , proto::when<
                    proto::nary_expr<
                        proto::_
                      , proto::_
                      , proto::_
                      , proto::_
                    >
                  , proto::_child_c<2>
                >
            >
        {};
    }
    
    struct this_function_eval
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <typename This, typename T, typename T0, typename Context>
        struct result<This(T, T0, Context)>
            : result<This(T const &, T0 const &, Context const &)>
        {};

        template <typename This, typename T, typename T0, typename Context>
        struct result<This(T &, T0 &, Context &)>
        {
            typedef
                typename evaluator::impl<T &, Context &, int>::result_type
                this_type;

            typedef
                typename evaluator::impl<T0 &, Context &, int>::result_type
                arg0_type;

            typedef typename detail::last_non_this_actor::impl<this_type, int, int>::result_type checker;

            typedef
                typename proto::detail::uncvref<
                    typename boost::result_of<typename proto::detail::uncvref<checker>::type(arg0_type)>::type
                >::type
                type;
        };

        template <typename This, typename T, typename T0, typename T1, typename Context>
        struct result<This(T, T0, T1, Context)>
            : result<This(T const &, T0 const &, T1 const &, Context const &)>
        {};

        template <typename This, typename T, typename T0, typename T1, typename Context>
        struct result<This(T &, T0 &, T1 &, Context &)>
        {
            typedef
                typename evaluator::impl<T &, Context &, int>::result_type
                this_type;

            typedef
                typename evaluator::impl<T0 &, Context &, int>::result_type
                arg0_type;

            typedef
                typename evaluator::impl<T0 &, Context &, int>::result_type
                arg1_type;

            typedef typename detail::last_non_this_actor::impl<this_type, int, int>::result_type checker;

            typedef
                typename proto::detail::uncvref<
                    typename boost::result_of<typename proto::detail::uncvref<checker>::type(arg0_type, arg1_type)>::type
                >::type
                type;
        };


        template <typename This, typename T0, typename Context>
        typename result<this_function_eval(This const&, T0 const&, Context &)>::type
        operator()(This const& _this, T0 const & t0, Context & ctx) const
        {
            typedef typename evaluator::impl<This const&, Context &, int>::result_type this_type;
            typedef typename detail::last_non_this_actor::impl<this_type, int, int>::result_type checker;

            //std::cout << typeid(checker).name() << "\n";
            //std::cout << typeid(checker).name() << "\n";

            return boost::phoenix::eval(_this, ctx)(boost::phoenix::eval(t0, ctx));
        }

        template <typename This, typename T0, typename T1, typename Context>
        typename result<this_function_eval(This const&, T0 const&, T1 const&, Context)>::type
        operator()(This const& _this, T0 const & t0, T1 const & t1, Context & ctx) const
        {
            typedef typename evaluator::impl<This const&, Context &, int>::result_type this_type;
            typedef typename detail::last_non_this_actor::impl<this_type, int, int>::result_type checker;

            //std::cout << typeid(checker).name() << "\n";

            return boost::phoenix::eval(_this, ctx)(boost::phoenix::eval(t0, ctx), boost::phoenix::eval(t1, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::this_function, Dummy>
        : proto::or_<
            proto::when<
                expression::this_function<proto::_, proto::_>
              , this_function_eval(proto::_child_c<0>, proto::_child_c<1>, _context)
            >
          , proto::when<
                expression::this_function<proto::_, proto::_>
              , this_function_eval(proto::_child_c<0>, proto::_child_c<1>, proto::_child_c<2>, _context)
            >
        >
    {};

    template <typename Expr>
    struct this_actor
        : actor<Expr>
    {
        typedef actor< Expr > base_type;
        
        this_actor(base_type const & base = base_type())
            : base_type( base )
        {}
        
        template <typename T>
        typename expression::this_function<this_actor, T>::type const
        operator()(T const & t) const
        {
            return expression::this_function<this_actor, T>::make(*this, t);
        }
        
        template <typename T0, typename T1>
        typename expression::this_function<this_actor, T0, T1>::type const
        operator()(T0 const & t0, T1 const & t1) const
        {
            return expression::this_function<this_actor, T0, T1>::make(*this, t0, t1);
        }
    };
    
    
    template <typename D>
    struct is_custom_terminal<detail::this_placeholder<D> >
        : mpl::true_
    {};
    
    // Special handling for this_placeholder
    template<typename D>
    struct custom_terminal<detail::this_placeholder<D> >
    {
        template <typename Sig>
        struct result;
        
        template <typename This, typename P, typename Context>
        struct result<This(P, Context)>
        {
            typedef
                typename add_reference<
                    typename remove_pointer<
                        typename remove_reference<
                            typename fusion::result_of::at_c<
                                typename boost::remove_reference<
                                    typename result_of::env<Context>::type
                                >::type
                              , 0
                            >::type
                        >::type
                    >::type
                >::type
            type;
        };
       
        template <typename Context>
        typename result<custom_terminal(detail::this_placeholder<D>, Context)>::type const
        operator()(detail::this_placeholder<D>, Context &ctx) const
        {
            return *fusion::at_c<0>(env(ctx));
        }
    };
    
    namespace expression
    {
        struct _this
            : proto::terminal<detail::this_placeholder<void> >
        {
            typedef proto::terminal<detail::this_placeholder<void> >::type base_type;
            typedef this_actor<base_type> type;
            
            static const type make()
            {
                actor<base_type> const e = {{{}}};
                return e;
            }
        };
    }

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
    expression::_this::type const _this = expression::_this::make();
#endif
    
}}

#endif
