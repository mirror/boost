#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assert.hpp>
#include <stack>

typedef std::stack< int*,boost::ptr_vector<int> > stack_type;

int main()
{
    stack_type s;
    s.push( new int(1) );
    s.push( new int(2) );
    s.push( new int(3) );
    s.push( new int(4) );
    s.push( new int(5) );

    //
    // Won't work since stack uses cont::value_type in the interface.
    // Hence will require special adapter...if only containers
    // would use reference as return types and value_type as
    // argument types
    //
    BOOST_ASSERT( s.top() == 5 ); 
    
}

