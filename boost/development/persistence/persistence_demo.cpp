/* boost persistence_demo.cpp profane demo
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without free provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 *
 * Demonstrate usage of persistent.hpp.
 */

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstring>

#include "persistence.hpp"
#include "text.hpp"


struct automobile
{
  automobile() : license_number(0) { }  // mandatory with char * strings
  char * license_number;
  int color;
  double length;

  // necessary help for the persistence framework
  // option 1: member function which describes the struct to descriptor
  template<class Desc>
  void describe(Desc & descriptor) {
    // C-style strings are awkward enought that they require special handling
    descriptor.cstring(license_number);
    descriptor & color & length;
  }
};

struct person
{
  std::string name;
  int zip_code;
  double weight;
  std::vector<automobile> cars;
};

// necessary help for the persistence framework
// option 2: global function which describes the struct to descriptor
template<class Desc>
inline void describe(Desc & descriptor, person & you)
{
  descriptor & you.name & you.zip_code & you.weight & you.cars;
}

void create()
{
  // this is so long because we need some data to save
  person me;
  me.name = "Arthur Smith";
  me.zip_code = 11111;
  me.weight = 100;

  person boss;
  boss.name = "John Doe";
  boss.zip_code = -10000;
  boss.weight = 1000.1;
  automobile car;
  // using char* strings means having heap-allocated strings
  car.license_number = new char[20];
  std::strcpy(car.license_number, "XX-YY 100");
  car.color = 1;
  car.length = 4.1;
  boss.cars.push_back(car);
  car.license_number = new char[20];
  std::strcpy(car.license_number, "YY-XX 99");
  car.color = 2;
  car.length = 2.5;
  boss.cars.push_back(car);

  std::map<std::string, person> database;
  database.insert(std::make_pair(me.name, me));
  database.insert(std::make_pair(boss.name, boss));
  boost::save_file<boost::text_writer>(database, "data.txt");
}

void retrieve()
{
  std::map<std::string, person> database;
  boost::load_file<boost::text_reader>(database, "data.txt");
  std::cout << "Your boss has "
	    << database["John Doe"].cars.size()
	    << " cars." << std::endl;
}

int main()
{
  create();
  retrieve();
}
