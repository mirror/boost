
#include <cassert>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include <boost/call_traits.hpp>

//
// struct contained models a type that contains a type (for example std::pair)
// arrays are contained by value, and have to be treated as a special case:
//
template <class T>
struct contained
{
   // define our typedefs first, arrays are stored by value
   // so value_type is not the same as result_type:
   typedef typename boost::call_traits<T>::param_type       param_type;
   typedef typename boost::call_traits<T>::reference        reference;
   typedef typename boost::call_traits<T>::const_reference  const_reference;
   typedef T                                                value_type;
   typedef typename boost::call_traits<T>::value_type       result_type;

   // stored value:
   value_type v_;
   
   // constructors:
   contained() {}
   contained(param_type p) : v_(p){}
   // return byval:
   result_type value() { return v_; }
   // return by_ref:
   reference get() { return v_; }
   const_reference const_get()const { return v_; }
   // pass value:
   void call(param_type p){}

};

template <class T, std::size_t N>
struct contained<T[N]>
{
   typedef typename boost::call_traits<T[N]>::param_type       param_type;
   typedef typename boost::call_traits<T[N]>::reference        reference;
   typedef typename boost::call_traits<T[N]>::const_reference  const_reference;
   typedef T                                                   value_type[N];
   typedef typename boost::call_traits<T[N]>::value_type       result_type;

   value_type v_;

   contained(param_type p)
   {
      std::copy(p, p+N, v_);
   }
   // return byval:
   result_type value() { return v_; }
   // return by_ref:
   reference get() { return v_; }
   const_reference const_get()const { return v_; }
   void call(param_type p){}
};

template <class T>
contained<typename boost::call_traits<T>::value_type> wrap(const T& t)
{
   return contained<typename boost::call_traits<T>::value_type>(t);
}

template <class T1, class T2>
std::pair<
   typename boost::call_traits<T1>::value_type, 
   typename boost::call_traits<T2>::value_type> 
      make_pair(const T1& t1, const T2& t2)
{
   return std::pair<
      typename boost::call_traits<T1>::value_type, 
      typename boost::call_traits<T2>::value_type>(t1, t2);
}

using namespace std;

//
// struct checker:
// verifies behaviour of contained example:
//
template <class T>
struct checker
{
   typedef typename boost::call_traits<T>::param_type param_type;
   void operator()(param_type);
};

template <class T>
void checker<T>::operator()(param_type p)
{
   T t(p);
   contained<T> c(t);
   cout << "checking contained<" << typeid(T).name() << ">..." << endl;
   assert(t == c.value());
   assert(t == c.get());
   assert(t == c.const_get());

   cout << "typeof contained<" << typeid(T).name() << ">::v_ is:           " << typeid(&contained<T>::v_).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::value() is:      " << typeid(&contained<T>::value).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::get() is:        " << typeid(&contained<T>::get).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::const_get() is:  " << typeid(&contained<T>::const_get).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::call() is:       " << typeid(&contained<T>::call).name() << endl;
   cout << endl;
}

template <class T, std::size_t N>
struct checker<T[N]>
{
   typedef typename boost::call_traits<T[N]>::param_type param_type;
   void operator()(param_type);
};

template <class T, std::size_t N>
void checker<T[N]>::operator()(param_type t)
{
   contained<T[N]> c(t);
   cout << "checking contained<" << typeid(T[N]).name() << ">..." << endl;
   unsigned int i = 0;
   for(i = 0; i < N; ++i)
      assert(t[i] == c.value()[i]);
   for(i = 0; i < N; ++i)
      assert(t[i] == c.get()[i]);
   for(i = 0; i < N; ++i)
      assert(t[i] == c.const_get()[i]);

   cout << "typeof contained<" << typeid(T[N]).name() << ">::v_ is:         " << typeid(&contained<T[N]>::v_).name() << endl;
   cout << "typeof contained<" << typeid(T[N]).name() << ">::value is:      " << typeid(&contained<T[N]>::value).name() << endl;
   cout << "typeof contained<" << typeid(T[N]).name() << ">::get is:        " << typeid(&contained<T[N]>::get).name() << endl;
   cout << "typeof contained<" << typeid(T[N]).name() << ">::const_get is:  " << typeid(&contained<T[N]>::const_get).name() << endl;
   cout << "typeof contained<" << typeid(T[N]).name() << ">::call is:        " << typeid(&contained<T[N]>::call).name() << endl;
   cout << endl;
}

//
// check_wrap:
// verifies behaviour of "wrap":
//
template <class T, class U, class V>
void check_wrap(T c, U u, const V& v)
{
   cout << "checking contained<" << typeid(T::value_type).name() << ">..." << endl;
   assert(c.get() == u);
   cout << "typeof deduced argument was:                    " << typeid(V).name() << endl;
   cout << "typeof deduced parameter after adjustment was:  " << typeid(v).name() << endl;
   cout << "typeof contained<" << typeid(T::value_type).name() << ">::v_ is:         " << typeid(&T::v_).name() << endl;
   cout << "typeof contained<" << typeid(T::value_type).name() << ">::value is:      " << typeid(&T::value).name() << endl;
   cout << "typeof contained<" << typeid(T::value_type).name() << ">::get is:        " << typeid(&T::get).name() << endl;
   cout << "typeof contained<" << typeid(T::value_type).name() << ">::const_get is:  " << typeid(&T::const_get).name() << endl;
   cout << "typeof contained<" << typeid(T::value_type).name() << ">::call is:       " << typeid(&T::call).name() << endl;
   cout << endl;
}

//
// check_make_pair:
// verifies behaviour of "make_pair":
//
template <class T, class U, class V>
void check_make_pair(T c, U u, V v)
{
   cout << "checking std::pair<" << typeid(c.first).name() << ", " << typeid(c.second).name() << ">..." << endl;
   assert(c.first == u);
   assert(c.second == v);
   cout << endl;
}


struct UDT
{
   int i_;
   UDT() : i_(2){}
   bool operator == (const UDT& v){ return v.i_ == i_; }
};


int main()
{
   checker<UDT> c1;
   UDT u;
   c1(u);
   checker<int> c2;
   int i = 2;
   c2(i);
   int* pi = &i;
   checker<int*> c3;
   c3(pi);
   checker<int&> c4;
   c4(i);
   checker<const int&> c5;
   c5(i);

   int a[2] = {1,2};
   checker<int[2]> c6;
   c6(a);

   check_wrap(wrap(2), 2, 2);
   const char ca[4] = "abc";
   // compiler can't deduce this for some reason:
   //check_wrap(wrap(ca), ca, ca);
   check_wrap(wrap(a), a, a);
   check_make_pair(::make_pair(a, a), a, a);

   return 0;
}
