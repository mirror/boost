#include <iostream>


struct Fun
{
    Fun()
    {
        std::cout << "fun" << std::endl;
    }
    
    template< class T >
    void operator()( T t )
    {
    }

    template< class T >
    Fun& operator,( T r ) 
    {
        return *this;
    }
};

template< class T >
Fun foo( T t )
{
    return Fun();
}



struct one
{
    one()
    {
        std::cout <<"one" << std::endl;
    }
};

struct two
{
    two()
    {
        std::cout <<"two" << std::endl;
    }
};

int main()
{
    foo( one() )( two() );

    Fun(),one(),two(),one();
}
