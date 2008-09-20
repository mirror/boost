//  MACRO:         BOOST_NO_NESTED_FRIENDSHIP
//  TITLE:         Access to private members from nested classes
//  DESCRIPTION:   If the compiler fails to support access to private members
//                 from nested classes

namespace boost_no_nested_friendship {

class A {
   static int b;
   class B {
      int f() { return b; }
   };
};

int test()
{
    return 0;
}

}

