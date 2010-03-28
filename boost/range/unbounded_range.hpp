#ifndef BOOST_RANGE_UNBOUNDED_RANGE_HPP
#define BOOST_RANGE_UNBOUNDED_RANGE_HPP

#include <boost/range/iterator_range.hpp>
#include <boost/config.hpp>

namespace boost
{
    template< class Iter >
    struct unbounded_iterator_range : iterator_range<Iter>
    {
        explicit unbounded_iterator_range( Iter r ) 
          : iterator_range<Iter>( r, r ) 
        {
            //
            // Remark: by storing the same iterator
            // twice, we can still allow
            // comparison to execute without leading to
            // operations on singular iterators 
            //
        }
        
    private:

        bool empty() const
        {
            return false;
        }
        //
        // Hide members that are illegal to use.
        //
        /*
        void end() const;
        void size() const;
        void empty() const;
        void equal() const;
        operator bool() const;
        bool operator==( unbounded_iterator_range );
        bool operator!=( unbounded_iterator_range );
        template< class S >
        void operator[]( S s ) const;
        template< class D >
        void advance_end( D d ) const;
        void back() const;
        */
    };

    template< class Iter >
    inline unbounded_iterator_range<Iter> unbounded_range( Iter r )
    {
        return unbounded_iterator_range<Iter>(r);
    }

    namespace detail
    {
        char is_unbounded_range( ... );
        template< class Iter >
        long is_unbounded_range( const unbounded_iterator_range<Iter>* );
    }

    template< class T >
    struct is_unbounded_range
    {
    private:
        static T* ptr_;
        
    public:
        BOOST_STATIC_CONSTANT( bool, 
              value = sizeof(long) == sizeof(detail::is_unbounded_range(ptr_) ) ); 
    };
}

#endif
