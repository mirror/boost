/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename A0>
        let_actor_gen<
            typename detail::make_locals<A0>::type
        > const
        operator()(A0 const& a0) const
        {
            return detail::make_locals<A0>::make(a0);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1>
        let_actor_gen<
            typename detail::make_locals<A0 , A1>::type
        > const
        operator()(A0 const& a0 , A1 const& a1) const
        {
            return detail::make_locals<A0 , A1>::make(a0 , a1);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2) const
        {
            return detail::make_locals<A0 , A1 , A2>::make(a0 , a1 , a2);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3>::make(a0 , a1 , a2 , a3);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3 , A4>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3 , A4>::make(a0 , a1 , a2 , a3 , a4);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5>::make(a0 , a1 , a2 , a3 , a4 , a5);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6>::make(a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    
    
    
    
    
    
    
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        let_actor_gen<
            typename detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type
        > const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
        {
            return detail::make_locals<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
        }
