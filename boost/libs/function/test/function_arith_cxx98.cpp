
    
#include <boost/function.hpp>
#include <iostream>



  float mul_ints(int x, int y) { return ((float)x) * y; }


struct int_div { 
  float operator()(int x, int y) const { return ((float)x)/y; }; 
};


int main()
{
    
boost::function<float (int x, int y)> f;

    
f = int_div();

    
std::cout << f(5, 3) << std::endl;

    
if (f)
  std::cout << f(5, 3) << std::endl;
else
  std::cout << "f has no target, so it is unsafe to call" << std::endl;

    
f = 0;

    
  f = &mul_ints;

  
    return 0;
}
