//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "OuterOrthogonal.hpp"

#include <boost/fsm/state_machine.hpp>

#include <boost/test/test_tools.hpp>

#include <typeinfo>
#include <iostream>



namespace fsm = boost::fsm;



struct S1;
struct TranistionTest : fsm::state_machine< TranistionTest, S1 >
{
  void Entry( const std::type_info & id )
  {
    std::cout << "Entry: " << id.name() << "\n";
  }
  void Exit( const std::type_info & id )
  {
    std::cout << "Exit: " << id.name() << "\n";
  }
};

struct S11;
struct S1 : Orthogonal0< S1, TranistionTest, fsm::no_reactions, S11 >
{
  S1( my_context ctx ) : my_base( ctx ) {}
};

struct S111;
struct S11 : Orthogonal1< S11, S1, fsm::no_reactions, S111 >
{
  S11( my_context ctx ) : my_base( ctx ) {}
};

struct S111 : InnermostDefault< S111, S11::orthogonal< 1 > >
{
  S111( my_context ctx ) : my_base( ctx ) {}
};



int test_main(int, char* [])
{
  TranistionTest machine;
  machine.initiate();
  machine.terminate();
  return 0;
}
