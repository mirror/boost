
    
#include <boost/function.hpp>
#include <iostream>


void do_sum_avg(int values[], int n, int& sum, float& avg)
{
  sum = 0;
  for (int i = 0; i < n; i++)
    sum += values[i];
  avg = (float)sum / n;
}

int main()
{
    
boost::function4<void, int[], int, int&, float> sum_avg;

    
sum_avg = &do_sum_avg;

}
