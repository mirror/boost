// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_ADJACENT_FILTER_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_ADJACENT_FILTER_IMPL_HPP

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
#include <boost/next_prior.hpp>


namespace boost
{

	namespace range_detail
	{
		template< class Iter, class R >
		class skip_iterator
		  : public boost::iterator_adaptor< skip_iterator<Iter,R>, Iter >
		{
		private:
			typedef boost::iterator_adaptor< skip_iterator<Iter,R>, Iter >
				  base_t;

			R* range;

		public:
			typedef Iter wrapped_iter_t;

			//
			// The iterators are bound to the lifetime of the
			// range and may not exist on their own. Hence it makes no
			// sense to e.g. wrap them in reverse_iterators
			// (that can OTOH be done in advance).
			//
			typedef std::input_iterator_tag iterator_category;

			explicit skip_iterator( R* r, Iter i )
			  : base_t(i), range(r) {}

			template< class OtherIter, class R2>
			skip_iterator( const skip_iterator<OtherIter,R2>& other )
			: base_t( other.base() ) {}

			R* get_range() const { return range; }

		 private:
			friend class boost::iterator_core_access;

			void increment()
			{
				BOOST_ASSERT( range != 0 );
				range->increment_impl( this->base_reference() );
			}

			//
			// Not needed ... just apply a reverse_iterator
			//
			void decrement()
            {
                BOOST_ASSERT( false && "you can't decrement an adjacent_filter_iterator" );
            }

			template< class D >
			void advance( D n )
            {
                BOOST_ASSERT( false );
            }

		};

		template< class P, class R >
		struct adjacent_filter_range
			: iterator_range< skip_iterator<
			                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type,
			                    adjacent_filter_range<P,R>
			                                >
			                >
		{
		private:
			typedef skip_iterator<
			                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type,
			                    adjacent_filter_range<P,R>
			                     >
				skip_iter;
			typedef iterator_range<skip_iter>
				base_range;

			typedef BOOST_DEDUCED_TYPENAME range_iterator<R>::type raw_iterator;

			P m_bi_pred;

			// Get the first element in the half-open range that
			// passes the filter predicate.
			// The adjacent_filter_range must only contain values that pass
			// through the filter.
			static raw_iterator to_valid(raw_iterator it, raw_iterator last, const P& bi_pred, bool default_pass)
			{
				if (it != last)
				{
					if (default_pass)
					{
						raw_iterator nxt = next(it);
						while (nxt != last && !bi_pred(*it, *nxt))
						{
							++it;
							++nxt;
						}
					}
					else
					{
						raw_iterator nxt = next(it);
						for(; nxt != last; ++it, ++nxt)
						{
							if (bi_pred(*it, *nxt))
							{
								break;
							}
						}
						if (nxt == last)
						{
							it = last;
						}
					}
				}
				return it;
			}

		public:
			adjacent_filter_range( const P& p, R& r, bool default_pass )
			: base_range( skip_iter( this, to_valid(boost::begin(r), boost::end(r), p, default_pass)),
						  skip_iter( this, boost::end(r)   ) ),
			  m_bi_pred( p ),
			  m_default_pass(default_pass)
			{
			}

			void increment_impl( raw_iterator& current )
			{
				BOOST_ASSERT( current != this->end().base() );

				current = to_valid(next(current), this->end().base(), m_bi_pred, m_default_pass);
			}

		private:
			bool m_default_pass;
		};

		template< class T >
		struct adjacent_holder : holder<T>
		{
			adjacent_holder( T r ) : holder<T>(r)
			{ }
		};

		template< class T >
		struct adjacent_excl_holder : holder<T>
		{
			adjacent_excl_holder( T r ) : holder<T>(r)
			{ }
		};

		template< class ForwardRng, class BinPredicate >
		inline adjacent_filter_range<BinPredicate, ForwardRng>
		operator|( ForwardRng& r,
				   const adjacent_holder<BinPredicate>& f )
		{
			return adjacent_filter_range<BinPredicate, ForwardRng>( f.val, r, true );
		}

		template< class ForwardRng, class BinPredicate >
		inline adjacent_filter_range<BinPredicate, const ForwardRng>
		operator|( const ForwardRng& r,
				   const adjacent_holder<BinPredicate>& f )
		{
			return adjacent_filter_range<BinPredicate,
				                         const ForwardRng>( f.val, r, true );
		}

		template< class ForwardRng, class BinPredicate >
		inline adjacent_filter_range<BinPredicate, ForwardRng>
		operator|( ForwardRng& r,
				   const adjacent_excl_holder<BinPredicate>& f )
		{
			return adjacent_filter_range<BinPredicate, ForwardRng>( f.val, r, false );
		}

		template< class ForwardRng, class BinPredicate >
		inline adjacent_filter_range<BinPredicate, ForwardRng>
		operator|( const ForwardRng& r,
				   const adjacent_excl_holder<BinPredicate>& f )
		{
			return adjacent_filter_range<BinPredicate,
										 const ForwardRng>( f.val, r, false );
		}

	} // 'range_detail'

	// Bring adjacent_filter_range into the boost namespace so that users of
	// this library may specify the return type of the '|' operator and
	// adjacent_filter()
	using range_detail::adjacent_filter_range;

	namespace adaptors
	{
		namespace
		{
			const range_detail::forwarder<range_detail::adjacent_holder>
                adjacent_filtered =
                   range_detail::forwarder<range_detail::adjacent_holder>();

			const range_detail::forwarder<range_detail::adjacent_excl_holder>
				adjacent_filtered_excl =
					range_detail::forwarder<range_detail::adjacent_excl_holder>();
		}

	    template<class ForwardRng, class BinPredicate>
	    inline adjacent_filter_range<BinPredicate, ForwardRng>
	    adjacent_filter(ForwardRng& rng, BinPredicate filter_pred, bool default_pass = true)
	    {
	        return adjacent_filter_range<BinPredicate, ForwardRng>(filter_pred, rng, default_pass);
	    }

	    template<class ForwardRng, class BinPredicate>
	    inline adjacent_filter_range<BinPredicate, const ForwardRng>
	    adjacent_filter(const ForwardRng& rng, BinPredicate filter_pred, bool default_pass = true)
	    {
	        return adjacent_filter_range<BinPredicate, const ForwardRng>(filter_pred, rng, default_pass);
	    }

	} // 'adaptors'

}

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#endif
