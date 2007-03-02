/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_APPLY_TRANSFORM_RESULT_02092006_1936)
#define FUSION_APPLY_TRANSFORM_RESULT_02092006_1936

namespace boost { namespace fusion
{
    struct void_;
    
    namespace detail
    {
        template <typename F>
        struct apply_transform_result
        {
            template <typename T0, typename T1 = void_>
            struct apply
            {
                typedef typename F::template result<T0, T1>::type type;
            };

            template <typename T0>
            struct apply<T0, void_>
            {
                typedef typename F::template result<T0>::type type;
            };
        };
    }
}}

#endif


