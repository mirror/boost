#include "boost/format.hpp"

#define BOOST_INCLUDE_MAIN 
#include <boost/test/test_tools.hpp>


int test_main(int, char* [])
{

  using boost::format;
  using boost::io::str;

  if(str( format("  %%  ") ) != "  %  ")
      BOOST_ERROR("Basic parsing without arguments Failed");
  if(str( format("nothing") ) != "nothing")
      BOOST_ERROR("Basic parsing without arguments Failed");
  if(str( format("%%  ") ) != "%  ")
      BOOST_ERROR("Basic parsing without arguments Failed");
  if(str( format("  %%") ) != "  %")
      BOOST_ERROR("Basic parsing without arguments Failed");
  if(str( format("  %n  ") ) != "    ")
      BOOST_ERROR("Basic parsing without arguments Failed");
  if(str( format("%n  ") ) != "  ")
      BOOST_ERROR("Basic parsing without arguments Failed");
  if(str( format("  %n") ) != "  ")
      BOOST_ERROR("Basic parsing without arguments Failed");

  if(str( format("%%##%%##%%1 %1%00") % "Escaped OK" ) != "%##%##%1 Escaped OK00")
      BOOST_ERROR("Basic parsing Failed");
  if(str( format("%%##%#x ##%%1 %s00") % 20 % "Escaped OK" ) != "%##0x14 ##%1 Escaped OK00")
      BOOST_ERROR("Basic p-parsing Failed") ;

#if !defined(BOOST_NO_STD_WSTRING) && !defined(BOOST_NO_STD_WSTREAM)
  using boost::wformat;
  if(str( wformat(L"%%##%%##%%1 %1%00") % L"Escaped OK" ) != L"%##%##%1 Escaped OK00")
      BOOST_ERROR("Basic w-parsing Failed");
  if(str( wformat(L"%%##%#x ##%%1 %s00") % 20 % L"Escaped OK" ) != L"%##0x14 ##%1 Escaped OK00")
      BOOST_ERROR("Basic wp-parsing Failed") ;
#endif // wformat tests

  return 0;
}
