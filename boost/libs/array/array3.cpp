/* example for using class array<>
 */
#include <string>
#include <iostream>
#include <boost/array.hpp>

template <class T>
void print_elements (const T& x);

int main()
{
    // create array of four seasons
    boost::array<std::string,4> seasons = {
        { "spring", "summer", "autumn", "winter" }
    };

    // copy and change order
    boost::array<std::string,4> seasons_orig = seasons;
    for (unsigned i=seasons.size()-1; i>0; --i) {
        swap(seasons.at(i),seasons.at((i+1)%seasons.size()));
    }

    std::cout << "one way:   ";
    print_elements(seasons);

    // try swap()
    std::cout << "other way: ";
    swap(seasons,seasons_orig);
    print_elements(seasons);

    // try reverse iterators
    std::cout << "reverse:   ";
    for (boost::array<std::string,4>::reverse_iterator pos
           =seasons.rbegin(); pos<seasons.rend(); ++pos) {
        std::cout << " " << *pos;
    }
    std::cout << std::endl;
}

template <class T>
void print_elements (const T& x)
{
    for (unsigned i=0; i<x.size(); ++i) {
        std::cout << " " << x[i];
    }
    std::cout << std::endl;
}

