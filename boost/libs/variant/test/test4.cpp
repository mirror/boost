// File: test4.cpp

#include "boost/test/minimal.hpp"
#include "boost/variant.hpp"
#include "boost/incomplete.hpp"

#include "jobs.h"

#include <string>

struct class_a;

using boost::incomplete;
using boost::variant;

typedef variant<std::string, incomplete<class_a>, float> var_type_1;
typedef variant<std::string, incomplete<class_a>, short> var_type_2;

#include "class_a.h"

int test_main(int , char* [])
{
   using namespace boost;


   var_type_1 v1;
   var_type_2 v2;

   v1 = class_a();
   verify(v1, spec<class_a>(), "[V] class_a(5511)");

   verify(v2, spec<std::string>(), "[V] ");

   v2 = "abcde";
   verify(v2, spec<std::string>(), "[V] abcde");

   v2 = v1;
   verify(v2, spec<class_a>(), "[V] class_a(5511)");

   v2 = 5;
   v1 = v2;

   return 0;
}

