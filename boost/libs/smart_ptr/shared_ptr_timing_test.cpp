#include <boost/shared_ptr.hpp>
#include <iostream>
#include <vector>
#include <ctime>

int const n = 8 * 1024 * 1024;

int main()
{
    std::vector< boost::shared_ptr<int> > v;
    boost::shared_ptr<int> pi(new int);

    std::clock_t t = std::clock();

    for(int i = 0; i < n; ++i)
    {
        v.push_back(pi);
    }

    t = std::clock() - t;

    std::cout << static_cast<double>(t) / CLOCKS_PER_SEC << '\n';
}
