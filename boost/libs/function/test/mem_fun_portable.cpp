
    
#include <boost/function.hpp>
#include <iostream>
#include <functional>


struct X {
  int foo(int);
};

int main()
{
    
boost::function2<int, X*, int> f;

f = &X::foo;
  
X x;
f(&x, 5);

}
    