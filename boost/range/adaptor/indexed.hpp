// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_INDEXED_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_INDEXED_IMPL_HPP

#include <boost/config.hpp>
#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable : 4355 )
#endif

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_adaptor.hpp>



namespace boost
{
	
	namespace range_detail
	{
		template< class Iter >
		class indexed_iterator
			: public boost::iterator_adaptor< indexed_iterator<Iter>, Iter >
		{
		private:
			typedef boost::iterator_adaptor< indexed_iterator<Iter>, Iter > 
				  base;   

			typedef BOOST_DEDUCED_TYPENAME base::difference_type index_type;

			index_type index_;
			
		public:
			explicit indexed_iterator( Iter i, index_type index )
			: base(i), index_(index) 
			{
				BOOST_ASSERT( index_ >= 0 && "Indexed Iterator out of bounds" );
			}

			index_type index() const
			{
				return index_;
			}
            
		 private:
			friend class boost::iterator_core_access;
			
			void increment() 
			{ 
                ++index_;
                ++(this->base_reference());
			}


			void decrement()
            {
                BOOST_ASSERT( index_ > 0 && "Indexed Iterator out of bounds" );
                --index_;
                --(this->base_reference());
            }

			void advance( index_type n )
            {
                index_ += n;
                BOOST_ASSERT( index_ >= 0 && "Indexed Iterator out of bounds" );
                this->base_reference() += n;
            }
		};

        template< class Rng >
        struct indexed_range : 
            iterator_range< indexed_iterator<BOOST_DEDUCED_TYPENAME range_iterator<Rng>::type> >
        {
        private:
            typedef indexed_iterator<BOOST_DEDUCED_TYPENAME range_iterator<Rng>::type>
                iter_type;
            typedef iterator_range<iter_type>
                base;
        public:
            template< class Index >
            indexed_range( Index i, Rng& r ) 
              : base( iter_type(boost::begin(r), i), iter_type(boost::end(r),i) )
            { }
        };


        template< class T >
        struct index_holder : holder<T>
        {
            index_holder( T r ) : holder<T>(r)
            { }
        };

        struct index_forwarder
        {
            template< class T >
            index_holder<T> operator()( T r ) const
            {
                return r;
            }
            
            index_holder<int> operator()( int r = 0 ) const
            {
                return r;
            }
        };
        
		template< class SinglePassRange >
		inline indexed_range<SinglePassRange> 
		operator|( SinglePassRange& r, 
				   const index_holder<typename range_difference<SinglePassRange>::type>& f )
		{
			return indexed_range<SinglePassRange>( f.val, r ); 
		}
	
		template< class SinglePassRange >
		inline indexed_range<const SinglePassRange> 
		operator|( const SinglePassRange& r, 
				   const index_holder<typename range_difference<SinglePassRange>::type>& f )
		{
			return indexed_range<const SinglePassRange>( f.val, r );   
		}
		
	} // 'range_detail'

	// Make this available to users of this library. It will sometimes be
	// required since it is the return type of operator '|' and
	// make_indexed_range().
	using range_detail::indexed_range;

	namespace adaptors
	{ 
		namespace
		{
			const range_detail::forwarder<range_detail::index_holder> 
				   indexed = 
				       range_detail::forwarder<range_detail::index_holder>();
		}
		
		template<class SinglePassRange, class Index>
		inline indexed_range<SinglePassRange>
		index(SinglePassRange& rng, Index index)
		{
		    return indexed_range<SinglePassRange>(index, rng);
	    }
	    
	    template<class SinglePassRange, class Index>
	    inline indexed_range<const SinglePassRange>
	    index(const SinglePassRange& rng, Index index)
	    {
	        return indexed_range<const SinglePassRange>(index, rng);
        }
	} // 'adaptors'
	
}

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#endif
