//  bll_and_function.cpp  --------------------------------

// test using BLL and boost::function

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"

#include "boost/lambda/lambda.hpp"

#include "boost/function.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>


using namespace boost::lambda;

using namespace std;

void test_function() {

  boost::function<int, int, int> f;
  f = _1 + _2;

 BOOST_TEST(f(1, 2)== 3);

 int i=1; int j=2;
 boost::function<int&, int&, int> g = _1 += _2;
 g(i, j);
 BOOST_TEST(i==3);



  int* sum = new int();
  *sum = 0;
  boost::function<int&, int> counter = *sum += _1;
  counter(5); // ok, sum* = 5;
  BOOST_TEST(*sum == 5);
  delete sum; 
  
  // The next statement would lead to a dangling reference
  // counter(3); // error, *sum does not exist anymore

}


int test_main(int, char *[]) {

  test_function();

  return 0;
}






