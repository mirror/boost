template< class Iter, int Level >
struct iterator
{
    typedef Iter type;
    typedef iterator<Iter,Level-1> next;
    
    next::type& next;
    mutable Iter iter_;

    
    Iter& base() const
    {
        return iter_;
    }
};

template< class Iter, class Boxed >
Iter unbox( const Boxed& b )
{
    
}

#include <vector>

int main()
{
    std::vector<int> v;
    typedef std::vector<int>::iterator iter;

    iterator<iter> i;
    iter ii = i;

    iterator< iterator<iter> > iii;
    iter iiii = iii;
}

