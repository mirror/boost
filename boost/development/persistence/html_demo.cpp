//  html_demo.cpp: demonstrate use of html.hpp  ------------------------------//

#include <string>
#include <map>
#include <boost/persistence.hpp>
#include <boost/html.hpp>

// There are some apparently unnecessary uses of std::string conversions from
// char *'s.  Done as a workaround for Borland 5.5.1 problems.

int main()
{
    std::map<int,std::string> my_map;
    my_map.insert(std::make_pair(2,std::string("This value is two")));
    my_map.insert(std::make_pair(1000,std::string("This value is one thousand")));

    boost::save_file<boost::text_writer>( my_map, std::string("my_map.txt") );
    boost::save_file<boost::html_writer>( my_map, std::string("my_map.html") );

    return 0;
}
