#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/remove_pointer.hpp>

struct copy_clone_allocator
{
    template< class T >
    T allocate_clone( const T& r )
    {
        return r;
    }

    template< class T >
    void deallocate_clone( const T* )
    {
        // do nothing
    }
};


template< class T >
struct indirect_value
{
    typedef typename boost::iterator_value<T>::type type;
};


template
<
    class T,
    class CloneAllocator = copy_clone_allocator,
    class Allocator      = std::allocator<T> 
>
class indirect_vector
{
    typedef std::vector<T> vec;
    vec vec_;

public:

    typedef boost::indirect_iterator<typename vec::iterator> iterator;
    typedef T                                 value_type;
    typedef typename indirect_value<T>::type  indirect_value;
    typedef indirect_value&                   reference;

public:

    void push_back( const T& r )
    {
        vec_.push_back( r );
    }

    iterator begin()
    {
        return iterator( vec_.begin() );
    }

    iterator end()
    {
        return iterator( vec_.end() );
    }

    reference front()
    {
        return *begin();
    }

    reference back()
    {
        return *--end();
    }
};

template
<
    class T,               /* can be T, nullable<T> or viewable<T> 
    class CloneAllocator = /* link: see below */,
    class Allocator      = /* link: see below */ 
>
class indirect_vector<T*,CloneAllocator,Allocator>
{
    
};

indirect_vector< boost::viewable<T> >; + byt om på policies (?)
indirect_vector< booot::nullable<T> >;
indirect_vector< T >;

indirect_vector< viewable< share_ptr<T> > >;


#include <boost/shared_ptr.hpp>
#include <cassert>

int main()
{
    using namespace boost;
    typedef std::vector<int>::iterator iter_t;    
    indirect_vector<iter_t> vec;
    indirect_vector<int*> vec2;
    std::vector<int> source;
    source.push_back( 5 );
    vec.push_back( source.begin() );
    vec.front() = 5;
    assert( vec.front() == 5 );
    assert( *vec.begin() == 5 );
}

