//File: class_a.h

#ifndef _CLASSA_H_INC_
#define _CLASSA_H_INC_


#include <iosfwd>

struct class_a 
{
   ~class_a();
   class_a(int n = 5511);
   class_a(const class_a& other);

   class_a& operator=(const class_a& rhs);
   void swap(class_a& other);

   int get() const;

private:
   int n_;
   class_a* self_p_;

}; //Class_a

std::ostream& operator<<(std::ostream& strm, const class_a& a);

 

#endif //_CLASSA_H_INC_
