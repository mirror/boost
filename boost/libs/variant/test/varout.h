//File: varout.h
#ifndef _VAROUTH_INC_
#define _VAROUTH_INC_

#include <sstream>
#include <string>
#include <iostream>

template<typename T0, typename T1, typename T2, typename T3>
inline std::ostream& operator<<(
      std::ostream& out
    , const boost::variant<T0, T1, T2, T3>& a
    );

struct to_text : boost::static_visitor<std::string>
{
   template<class Value>
   std::string operator()(const Value& value) const
   {
      std::ostringstream ost;      
      ost << "[V] " << value;
      
      return ost.str();
   }
};


template<typename T0, typename T1, typename T2, typename T3>
inline std::ostream& operator<<(
      std::ostream& out
    , const boost::variant<T0, T1, T2, T3>& a
    )
{
   out << boost::apply_visitor(to_text(), a);
   return out;
}

#endif //_VAROUTH_INC_
