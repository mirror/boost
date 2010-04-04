#ifndef BOOST_RANGE_COMBINE_HPP
#define BOOST_RANGE_COMBINE_HPP

#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/config.hpp>

namespace boost
{
    namespace detail
    {
        struct void_ { typedef void_ type; };
    }

    template<> struct range_iterator<detail::void_>
    {
       typedef tuples::null_type type;
    };

    namespace detail
    {
        inline tuples::null_type range_begin( void_& ) 
        { return tuples::null_type(); }

        inline tuples::null_type range_end( void_& ) 
        { return tuples::null_type(); }

        template< class T >
        struct tuple_iter
        {
            typedef typename mpl::eval_if_c< is_same<T,void_>::value,
                                             mpl::identity<tuples::null_type>,
                                             range_iterator<T> >::type
                type;
        };

        template< class Rng1, class Rng2 >
        struct tuple_range
        {
            typedef typename mpl::eval_if_c< is_same<Rng1,void_>::value,
                                             void_,
                                             mpl::identity<Rng1> >::type
                type; 
        };

        template
        <
            class R1,
            class R2,
            class R3,
            class R4,
            class R5,
            class R6 
        >
        struct generate_tuple
        {
            typedef boost::tuple< typename tuple_iter<R1>::type,
                                  typename tuple_iter<R2>::type,
                                  typename tuple_iter<R3>::type,
                                  typename tuple_iter<R4>::type,
                                  typename tuple_iter<R5>::type,
                                  typename tuple_iter<R6>::type >
                type;

            static type begin( R1& r1, R2& r2, R3& r3, R4& r4, R5& r5, R6& r6 )
            {
                return make_tuple( boost::begin(r1),
                                   boost::begin(r2),
                                   boost::begin(r3),
                                   boost::begin(r4),
                                   boost::begin(r5),
                                   boost::begin(r6) );
            }

            static type end( R1& r1, R2& r2, R3& r3, R4& r4, R5& r5, R6& r6 )
            {
                return make_tuple( boost::end(r1),
                                   boost::end(r2),
                                   boost::end(r3),
                                   boost::end(r4),
                                   boost::end(r5),
                                   boost::end(r6) );
            }
        };

        template
        <
            class R1,
            class R2 = void_,
            class R3 = void_,
            class R4 = void_,
            class R5 = void_,
            class R6 = void_
        >
        struct zip_rng
            : iterator_range<
                zip_iterator< typename generate_tuple<R1,R2,R3,R4,R5,R6>::type >
                            >
        {
        private:
            typedef generate_tuple<R1,R2,R3,R4,R5,R6>
                generator;
            typedef typename generator::type
                tuple;
            typedef zip_iterator<tuple>
                zip_iter;
            typedef iterator_range<zip_iter>
                base;

        public:
            zip_rng( R1& r1, R2& r2, R3& r3, R4& r4, R5& r5, R6& r6 )
            : base( zip_iter( generator::begin(r1,r2,r3,r4,r5,r6) ),
                    zip_iter( generator::end(r1,r2,r3,r4,r5,r6) ) )
            {
		BOOST_ASSERT(boost::distance(r1) <= boost::distance(r2));
		BOOST_ASSERT(boost::distance(r1) <= boost::distance(r3));
		BOOST_ASSERT(boost::distance(r1) <= boost::distance(r4));
		BOOST_ASSERT(boost::distance(r1) <= boost::distance(r5));
		BOOST_ASSERT(boost::distance(r1) <= boost::distance(r6));
            }

            template< class Zip, class Rng >
            zip_rng( Zip& z, Rng& r )
            : base( zip_iter( generator::begin( z, r ) ),
                    zip_iter( generator::end( z, r ) ) )
            {

                // @todo: tuple::begin( should be overloaded for this situation
            }

            struct tuple_length : tuples::length<tuple>
            { };

            template< unsigned N >
            struct get
            {
                template< class Z, class R >
                static typename tuples::element<N,tuple>::type begin( Z& z, R& )
                {
                    return get<N>( z.begin().get_iterator_tuple() );
                }

                template< class Z, class R >
                static typename tuples::element<N,tuple>::type end( Z& z, R& r )
                {
                    return get<N>( z.end().get_iterator_tuple() );
                }
            };

        };

        template< class Rng1, class Rng2 >
        struct zip_range 
            : iterator_range< 
                zip_iterator< 
                    tuple< typename range_iterator<Rng1>::type,
                           typename range_iterator<Rng2>::type >
                            > > 
        {
        private:
            typedef zip_iterator< 
                tuple< typename range_iterator<Rng1>::type,
                       typename range_iterator<Rng2>::type >
                        >
                zip_iter;
            typedef iterator_range<zip_iter>
                base;

        public:
            zip_range( Rng1& r1, Rng2& r2 )
            : base( zip_iter( make_tuple(boost::begin(r1), 
                                         boost::begin(r2)) ),
                    zip_iter( make_tuple(boost::end(r1), 
                                         boost::end(r2)) ) )
            {
		BOOST_ASSERT(boost::distance(r1) <= boost::distance(r2));
            }
        };

        template< class Rng1, class Rng2, class Rng3 >
        struct zip_range3 
            : iterator_range< 
                zip_iterator< 
                    tuple< typename range_iterator<Rng1>::type,
                           typename range_iterator<Rng2>::type,
                           typename range_iterator<Rng3>::type >
                            > > 
        {
        private:
            typedef zip_iterator< 
                tuple< typename range_iterator<Rng1>::type,
                       typename range_iterator<Rng2>::type, 
                       typename range_iterator<Rng3>::type >
                        >
                zip_iter;
            typedef iterator_range<zip_iter>
                base;

        public:
            zip_range3( Rng1& r1, Rng2& r2, Rng3& r3 )
            : base( zip_iter( make_tuple(boost::begin(r1), 
                                         boost::begin(r2),
                                         boost::begin(r3)) ),
                    zip_iter( make_tuple(boost::end(r1), 
                                         boost::end(r2),
                                         boost::end(r3)) )
                   )
            {
		BOOST_ASSERT(distance(r1) <= distance(r2));
		BOOST_ASSERT(distance(r1) <= distance(r3));
            }
        };


        struct combine_tag {};

        template< class Rng >
        inline zip_rng<Rng> 
        operator&( combine_tag, Rng& r )
        {
            return zip_rng<Rng>(r);
        }

        template< class Rng >
        inline iterator_range<const Rng> 
        operator&( combine_tag, const Rng& r )
        {
            return iterator_range<const Rng>(r);
        }

        template
        < 
            class R1, 
            class R2,
            class R3,
            class R4,
            class R5,
            class Rng
        >
        inline typename zip_rng<R1,R2,R3,R4,R5>::next 
        operator&( const zip_rng<R1,R2,R3,R4,R5>& zip, 
                   Rng& r )
        {
            return zip_rng<R1,R2,R3,R4,R5>::next( zip, r );
        }

        //
        // This one should be able to be made generic
        //
        // template
        // <
        //     class R1, 
        //     class R2 = void, 
        //     class R3 = void, 
        //     class R4 = void, 
        //     class R5 = void,
        //     class R6 = void
        // >
        // inline zip_range<R1,R2,R3,R4,R4,R5,R6>::type
        // x
        //
        //
        /*
        template< class Rng1, class Rng2, class Rng3 >
        inline zip_range3<Rng1,Rng2,Rng3>
        operator&( const zip_range<Rng1,Rng2>& r1, const Rng3& r3 )
        {
            return zip_range3<Rn1,Rng2,Rng3>(
        }*/

    } // namespace 'detail'

    template< class Rng1, class Rng2 >
    inline detail::zip_range<Rng1,Rng2> combine( Rng1& r1, Rng2& r2 )
    {
        return detail::zip_range<Rng1,Rng2>(r1,r2);
    }

    template< class Rng1, class Rng2 >
    inline detail::zip_range<const Rng1,Rng2> combine( const Rng1& r1, Rng2& r2 )
    {
        return detail::zip_range<const Rng1,Rng2>(r1,r2);
    }

    template< class Rng1, class Rng2 >
    inline detail::zip_range<Rng1,const Rng2> combine( Rng1& r1, const Rng2& r2 )
    {
        return detail::zip_range<Rng1,Rng2>(r1,r2);
    }

    template< class Rng1, class Rng2 >
    inline detail::zip_range<const Rng1,const Rng2> combine( const Rng1& r1, const Rng2& r2 )
    {
        return detail::zip_range<const Rng1,const Rng2>(r1,r2);
    }

    //
    // @todo: find a solution that scales better
    //        instead of adding 6 overloads!
    //
}

#endif
