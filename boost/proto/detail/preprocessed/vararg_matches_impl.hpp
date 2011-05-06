    ///////////////////////////////////////////////////////////////////////////////
    /// \file vararg_matches_impl.hpp
    /// Specializations of the vararg_matches_impl template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 2, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child1>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child1>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 2 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 2, 2>
      : matches_<
            typename detail::expr_traits<typename Args::child1>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child1>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 3, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child2>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child2>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 3 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 3, 3>
      : matches_<
            typename detail::expr_traits<typename Args::child2>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child2>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 4, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child3>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child3>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 4 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 4, 4>
      : matches_<
            typename detail::expr_traits<typename Args::child3>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child3>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 5, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child4>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child4>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 5 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 5, 5>
      : matches_<
            typename detail::expr_traits<typename Args::child4>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child4>::value_type::proto_grammar
          , Back
        >
    {};
