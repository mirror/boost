/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_LOCAL_VARIABLE_HPP
#define BOOST_PHOENIX_SCOPE_LOCAL_VARIABLE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/container/generation/make_map.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>
#include <boost/phoenix/statement/sequence.hpp>

namespace boost { namespace phoenix
{

    namespace detail
    {
        template <typename Key>
        struct local
        {
            typedef Key type;
        };
    }
    
    namespace expression
    {
        template <typename Key>
        struct local_variable
            : expression::terminal<detail::local<Key> >
        {
            typedef typename expression::terminal<detail::local<Key> >::type type;

            static type make()
            {
                type const e = {};
                return e;
            }
        };
    }

    namespace rule
    {
        struct local_variable
            : expression::local_variable<proto::_>
        {};

        struct local_var_def
            : proto::assign<local_variable, meta_grammar>
        {};
    }

    namespace result_of
    {
        template <typename Key>
        struct is_nullary<custom_terminal<detail::local<Key> > >
            : mpl::false_
        {};
    }

    namespace detail
    {
        template <typename Map, typename Context>
        struct local_var_def_is_nullary;


        struct local_var_def_eval;
            
        #include <boost/phoenix/scope/detail/local_var_def.hpp>
        
        struct scope_is_nullary_actions
        {
            template <typename Rule, typename Dummy = void>
            struct when
                : boost::phoenix::is_nullary::when<Rule, Dummy>
            {};
        };

        template <typename Dummy>
        struct scope_is_nullary_actions::when<rule::custom_terminal, Dummy>
            : proto::or_<
                proto::when<rule::local_variable, mpl::true_()>
              , proto::otherwise<
                    boost::phoenix::result_of::is_nullary<
                        custom_terminal<proto::_value>
                    >()
                >
            >
        {};

        struct local_var_not_found
        {
        };
    }

    struct get_local
    {
        template <typename Sig>
        struct result;
        
        template <typename This, typename Env, typename OuterEnv, typename Locals, typename Key>
        struct result<This(scoped_environment<Env, OuterEnv, Locals> const&, Key)>
            : mpl::eval_if_c<
                fusion::result_of::has_key<Locals, Key>::type::value
              , fusion::result_of::at_key<Locals, Key>
              , result<This(OuterEnv&, Key)>
            >
        {};

        template <typename This, typename Env, typename OuterEnv, typename Locals, typename Key>
        struct result<This(scoped_environment<Env, OuterEnv, Locals>&, Key)>
            : mpl::eval_if_c<
                fusion::result_of::has_key<Locals, Key>::type::value
              , fusion::result_of::at_key<Locals, Key>
              , result<This(typename proto::detail::uncvref<OuterEnv>::type&, Key)>
            >
        {};

        template <typename This, typename Env, typename OuterEnv, typename Key>
        struct result<This(scoped_environment<Env, OuterEnv, mpl::void_> const&, Key)>
            : result<This(OuterEnv&, Key)>
        {};

        template <typename This, typename Env, typename OuterEnv, typename Key>
        struct result<This(scoped_environment<Env, OuterEnv, mpl::void_>&, Key)>
            : result<This(OuterEnv&, Key)>
        {};
        
        template <typename This, typename Env, typename Key>
        struct result<This(Env &, Key)>
        {
            typedef detail::local_var_not_found type;
        };

        template <typename Env, typename OuterEnv, typename Locals, typename Key>
        typename result<get_local(scoped_environment<Env, OuterEnv, Locals>&, Key)>::type
        operator()(scoped_environment<Env, OuterEnv, Locals>& env, Key k) const
        {
            return this->evaluate(env, k, typename fusion::result_of::has_key<Locals, Key>::type());
        }

        template <typename Env, typename OuterEnv, typename Locals, typename Key>
        typename result<get_local(scoped_environment<Env, OuterEnv, Locals>&, Key)>::type
        operator()(scoped_environment<Env, OuterEnv, Locals> const& env, Key k) const
        {
            return this->evaluate(env, k, typename fusion::result_of::has_key<Locals, Key>::type());
        }
        
        template <typename Env, typename OuterEnv, typename Key>
        typename result<get_local(scoped_environment<Env, OuterEnv, mpl::void_>&, Key)>::type
        operator()(scoped_environment<Env, OuterEnv, mpl::void_>& env, Key k) const
        {
            return (*this)(env.outer_env, k);
        }
        
        template <typename Env, typename OuterEnv, typename Key>
        typename result<get_local(scoped_environment<Env, OuterEnv, mpl::void_>&, Key)>::type
        operator()(scoped_environment<Env, OuterEnv, mpl::void_> const& env, Key k) const
        {
            return (*this)(env.outer_env, k);
        }

        template <typename Env, typename Key>
        typename result<get_local(Env&, Key)>::type
        operator()(Env &, Key) const
        {
            return detail::local_var_not_found();
        }

        private:
            // is a scoped environment
            template <typename Env, typename Key>
            typename result<get_local(Env&, Key)>::type
            evaluate(Env & env, Key, mpl::true_) const
            {
                return fusion::at_key<Key>(env.locals);
            }
            
            // --> we need to look in the outer environment
            template <typename Env, typename Key>
            typename result<get_local(Env&, Key)>::type
            evaluate(Env & env, Key k, mpl::false_) const
            {
                return (*this)(env.outer_env, k);
            }

    };
    
    template<typename Key>
    struct is_custom_terminal<detail::local<Key> >
      : mpl::true_
    {};

    template <typename Key>
    struct custom_terminal<detail::local<Key> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Local, typename Context>
        struct result<This(Local, Context)>
            : result<This(Local const &, Context)>
        {};

        template <typename This, typename Local, typename Context>
        struct result<This(Local &, Context)>
        {
            typedef
                typename get_local::
                    template result<
                        get_local(
                            typename result_of::env<Context>::type
                          , Local
                        )
                    >::type
                type;
        };

        template <typename Local, typename Context>
        typename result<custom_terminal<detail::local<Key> >(Local const &, Context const&)>::type
        operator()(Local const& local, Context const & ctx)
        {
            return get_local()(env(ctx), local);
        }
    };

    namespace local_names
    {
        typedef expression::local_variable<struct _a_key>::type _a_type;
        typedef expression::local_variable<struct _b_key>::type _b_type;
        typedef expression::local_variable<struct _c_key>::type _c_type;
        typedef expression::local_variable<struct _d_key>::type _d_type;
        typedef expression::local_variable<struct _e_key>::type _e_type;
        typedef expression::local_variable<struct _f_key>::type _f_type;
        typedef expression::local_variable<struct _g_key>::type _g_type;
        typedef expression::local_variable<struct _h_key>::type _h_type;
        typedef expression::local_variable<struct _i_key>::type _i_type;
        typedef expression::local_variable<struct _j_key>::type _j_type;
        typedef expression::local_variable<struct _k_key>::type _k_type;
        typedef expression::local_variable<struct _l_key>::type _l_type;
        typedef expression::local_variable<struct _m_key>::type _m_type;
        typedef expression::local_variable<struct _n_key>::type _n_type;
        typedef expression::local_variable<struct _o_key>::type _o_type;
        typedef expression::local_variable<struct _p_key>::type _p_type;
        typedef expression::local_variable<struct _q_key>::type _q_type;
        typedef expression::local_variable<struct _r_key>::type _r_type;
        typedef expression::local_variable<struct _s_key>::type _s_type;
        typedef expression::local_variable<struct _t_key>::type _t_type;
        typedef expression::local_variable<struct _u_key>::type _u_type;
        typedef expression::local_variable<struct _v_key>::type _v_type;
        typedef expression::local_variable<struct _w_key>::type _w_type;
        typedef expression::local_variable<struct _x_key>::type _x_type;
        typedef expression::local_variable<struct _y_key>::type _y_type;
        typedef expression::local_variable<struct _z_key>::type _z_type;

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
        _a_type const _a = {{{}}};
        _b_type const _b = {{{}}};
        _c_type const _c = {{{}}};
        _d_type const _d = {{{}}};
        _e_type const _e = {{{}}};
        _f_type const _f = {{{}}};
        _g_type const _g = {{{}}};
        _h_type const _h = {{{}}};
        _i_type const _i = {{{}}};
        _j_type const _j = {{{}}};
        _k_type const _k = {{{}}};
        _l_type const _l = {{{}}};
        _m_type const _m = {{{}}};
        _n_type const _n = {{{}}};
        _o_type const _o = {{{}}};
        _p_type const _p = {{{}}};
        _q_type const _q = {{{}}};
        _r_type const _r = {{{}}};
        _s_type const _s = {{{}}};
        _t_type const _t = {{{}}};
        _u_type const _u = {{{}}};
        _v_type const _v = {{{}}};
        _w_type const _w = {{{}}};
        _x_type const _x = {{{}}};
        _y_type const _y = {{{}}};
        _z_type const _z = {{{}}};
#endif
    }
    
    namespace detail
    {
        template <
            BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_LOCAL_LIMIT)
          , typename Dummy = void
        >
        struct make_locals;
        
        #include <boost/phoenix/scope/detail/make_locals.hpp>
    }
}}

#endif
