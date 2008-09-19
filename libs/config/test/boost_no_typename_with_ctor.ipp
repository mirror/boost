//  MACRO:         BOOST_NO_TYPENAME_WITH_CTOR
//  TITLE:         Use of typename keyword with constructors
//  DESCRIPTION:   If the compiler rejects the typename keyword when calling
//                 the constructor of a dependent type

namespace boost_no_typename_with_ctor {

struct A {};

template <typename T>
struct B {
  typedef T type;
};

template <typename T>
typename T::type f() {
  return typename T::type();
}

int test() {
  A a = f<B<A> >();
  return 0;
}

}

