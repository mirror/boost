//[foo_cpp
struct Foo{

  Foo()//=;
//<-
      : x( 10 )
  {}
//->

//<-
  int x;
//->
};
//]