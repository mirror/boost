
    
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
    
boost::function<void (int values[], int n, int& sum, float& avg)> sum_avg;

    
sum_avg = &do_sum_avg;


    return 0;
}
