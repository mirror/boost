                                                                                                                                                                                                                                                               
// Copyright (C) 2005 Igor Chesnokov, mailto:ichesnokov@gmail.com
// Copyright (C) 2005 Peder Holt

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_MSVC_TYPEOF_IMPL_HPP_INCLUDED
# define BOOST_TYPEOF_MSVC_TYPEOF_IMPL_HPP_INCLUDED

# include <boost/config.hpp>
# include <boost/detail/workaround.hpp>

namespace boost
{
    namespace type_of
    {

        //Compile time constant code
# if BOOST_WORKAROUND(BOOST_MSVC,>=1300) && defined(_MSC_EXTENSIONS)
        template<int N> struct the_counter;
        
        template<typename T,int N = 5/*for similarity*/>
        struct encode_counter
        {
            __if_exists(the_counter<N + 256>)
            {
                BOOST_STATIC_CONSTANT(unsigned,count=(encode_counter<T,N + 257>::count));
            }
            __if_not_exists(the_counter<N + 256>)
            {
                __if_exists(the_counter<N + 64>)
                {
                    BOOST_STATIC_CONSTANT(unsigned,count=(encode_counter<T,N + 65>::count));
                }
                __if_not_exists(the_counter<N + 64>)
                {
                    __if_exists(the_counter<N + 16>)
                    { 
                        BOOST_STATIC_CONSTANT(unsigned,count=(encode_counter<T,N + 17>::count));
                    }
                    __if_not_exists(the_counter<N + 16>)
                    {
                        __if_exists(the_counter<N + 4>)
                        {
                            BOOST_STATIC_CONSTANT(unsigned,count=(encode_counter<T,N + 5>::count));
                        }
                        __if_not_exists(the_counter<N + 4>)
                        {
                            __if_exists(the_counter<N>)
                            {
                                BOOST_STATIC_CONSTANT(unsigned,count=(encode_counter<T,N + 1>::count));
                            }
                            __if_not_exists(the_counter<N>)
                            {
                                BOOST_STATIC_CONSTANT(unsigned,count=N);
                                typedef the_counter<N> type;
                            }
                        }
                    }
                }
            }
        };

# define BOOST_TYPEOF_INDEX(T) (encode_counter<T>::count)
# define BOOST_TYPEOF_NEXT_INDEX(next)
# else
        template<int N> struct encode_counter : encode_counter<N - 1> {};
        template<> struct encode_counter<0> {};
        
        //Need to default to a larger value than 4, as due to MSVC's ETI errors. (sizeof(int)==4)
        char (*encode_index(...))[5];

# define BOOST_TYPEOF_INDEX(T) (sizeof(*boost::type_of::encode_index((boost::type_of::encode_counter<1005>*)0)))
# define BOOST_TYPEOF_NEXT_INDEX(next) friend char (*encode_index(encode_counter<next>*))[next];
# endif

        //Typeof code

# if BOOST_WORKAROUND(BOOST_MSVC,==1300)
        template<int ID>
        struct msvc_typeof_base
        {
            template<bool>
            struct id2type_impl;

            typedef id2type_impl<true> id2type;
        };

        template<typename T, int ID>
        struct msvc_typeof : msvc_typeof_base<ID>
        {
            template<>
            struct id2type_impl<true> 
            {
                typedef T type;
            };
        };
# else 
        template<int ID>
        struct msvc_typeof_base
        {

            struct id2type;
        };

        template<typename T, int ID>
        struct msvc_typeof : msvc_typeof_base<ID>
        {
            struct msvc_typeof_base<ID>::id2type // This uses nice VC6-VC7 bugfeature
            {
                typedef T type;
            };
        };
# endif
        template<int ID>
        struct msvc_typeid_wrapper {
            typedef typename msvc_typeof_base<ID>::id2type id2type;
            typedef typename id2type::type type;
        };
        //Workaround for ETI-bug for VC6 and VC7
        template<>
        struct msvc_typeid_wrapper<1> {
            typedef msvc_typeid_wrapper<1> type;
        };
        //Workaround for ETI-bug for VC7.1
        template<>
        struct msvc_typeid_wrapper<4> {
            typedef msvc_typeid_wrapper<4> type;
        };

        //Tie it all together
        template<typename T>
        struct encode_type
        {
            //Get the next available compile time constants index
            BOOST_STATIC_CONSTANT(unsigned,value=BOOST_TYPEOF_INDEX(T));
            //Instantiate the template
            typedef typename msvc_typeof<T,value>::id2type type;
            //Set the next compile time constants index
            BOOST_STATIC_CONSTANT(unsigned,next=value+1);
            //Increment the compile time constant (only needed when extensions are not active
            BOOST_TYPEOF_NEXT_INDEX(next);     
        };

        template<typename T>
        char (*encode_start(T const&))[encode_type<T>::value];
    }
}

# define BOOST_TYPEOF(expr) \
    boost::type_of::msvc_typeid_wrapper<sizeof(*boost::type_of::encode_start(expr))>::type

# define BOOST_TYPEOF_TPL(expr) typename BOOST_TYPEOF(expr)

#endif//BOOST_TYPEOF_MSVC_TYPEOF_IMPL_HPP_INCLUDED
