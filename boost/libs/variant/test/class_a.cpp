//File: class_a.cpp


#include <sstream>
#include <iostream>
#include <assert.h>

#include "class_a.h"


using namespace std;

class_a::~class_a()
{
   assert(self_p_ == this);
}

class_a::class_a(int n)
{
   n_ = n;
   self_p_ = this;
}

class_a::class_a(const class_a& other)
{
   n_ = other.n_;
   self_p_ = this;
}


class_a& class_a::operator=(const class_a& rhs)
{
   class_a temp(rhs);
   swap(temp);

   return *this;
}

void class_a::swap(class_a& other)
{
   std::swap(n_, other.n_);
}

int class_a::get() const
{
   return n_;
}




std::ostream& operator<<(std::ostream& strm, const class_a& a)
{
   return strm << "class_a(" << a.get() << ")";
}
