#include <sstream>
#include <iostream>
#include <fstream>

#include "boost/gdtl/gregorian/greg_month.hpp"
#include "boost/gdtl/gregorian/greg_facet.hpp"
#include "boost/gdtl/date_format_simple.hpp"
#include "boost/gdtl/gregorian/gregorian.hpp"
#include "boost/gdtl/testfrmwk.hpp"


    const char* const de_short_month_names[]={"Jan","Feb","Mar","Apr","Mai","Jun","Jul","Aug","Sep","Okt","Nov","Dez", "NAM"};

    const char* const de_long_month_names[]={"Januar","Februar","Marz","April","Mai","Juni","Juli","August","September","Oktober","November","Dezember","NichtDerMonat"};
    const char* const de_special_value_names[]={"NichtDatumzeit","-unbegrenztheit", "+unbegrenztheit"};

//    const char* const de_short_weekday_names[]={"Son", "Mon", "Diens"};

    const char* const de_long_weekday_names[]={"Sonntag", "Montag", "Dienstag","Mittwoch", "Donnerstag", "Freitag", "Samstag"};

    const char* const es_short_month_names[]={"Ene","Feb","Mar","Abr","Pue","Jun","Jul","Ago","Sep","Oct","Nov","Dic", "NAM"};

    const char* const es_long_month_names[]={"Enero","Febrero","Marcha","Abril","Pueda","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre","NoAMes"};
    const char* const es_special_value_names[]={"NoUnRatoDeLaFacha","-infinito", "+infinito"};

int
main()
{
//   std::locale native("");
//   std::cout << "native: " << native.name() << std::endl;
#ifndef BOOST_NO_STD_LOCALE

  using namespace boost::gregorian;

  typedef greg_facet_config facet_config;
  typedef boost::gdtl::all_date_names_put<facet_config> date_facet;
  typedef boost::gdtl::date_names_put<facet_config> date_facet_base;
  typedef boost::gdtl::ostream_month_formatter<date_facet_base> month_formatter;

  date_facet gdnp(de_short_month_names, de_long_month_names, 
		  de_special_value_names, de_long_weekday_names,
		  de_long_weekday_names);

  std::stringstream ss;
  std::ostreambuf_iterator<char> coi(ss);
  gdnp.put_month_short(coi, Oct);
  check("check german short month: " + ss.str(), 
 	ss.str() == std::string("Okt"));

  ss.str(""); //reset string stream 
  greg_month m(Oct);
  month_formatter::format_month(m, ss, gdnp, boost::gdtl::month_as_short_string);
  check("check german short month: " + ss.str(), 
 	ss.str() == std::string("Okt"));
  ss.str(""); //reset string stream 
  month_formatter::format_month(m, ss, gdnp, boost::gdtl::month_as_long_string);
  check("check german long month: " + ss.str(), 
 	ss.str() == std::string("Oktober"));


  greg_year_month_day ymd(2002,Oct,1);
  typedef boost::gdtl::ostream_ymd_formatter<greg_year_month_day, date_facet_base> ymd_formatter;
  ss.str(""); //reset string stream 
  ymd_formatter::ymd_put(ymd, ss, gdnp);
  check("check ymd: " + ss.str(), 
  	ss.str() == std::string("2002-Okt-01"));


  typedef boost::gdtl::ostream_date_formatter<date, date_facet_base> datef;

  std::stringstream os;
  date d1(2002, Oct, 1);
  datef::date_put(d1, os, gdnp);
  check("ostream low level check string:"+os.str(), 
 	os.str() == std::string("2002-Okt-01"));

//   //Locale tests
  std::locale global;
  std::cout << "global: " << global.name() << std::endl;

  // put a facet into a locale
  //check for a facet p319
  check("no registered facet here",
	!std::has_facet<date_facet>(global));

  std::locale global2(global, 
		      new date_facet(de_short_month_names, 
				     de_long_month_names,
				     de_special_value_names,
				     de_long_weekday_names,
				     de_long_weekday_names));

  check("facet registered here",
	std::has_facet<boost::gdtl::date_names_put<facet_config> >(global2));

  std::stringstream os2;
  os2.imbue(global2); 
  datef::date_put(d1, os2);
  check("check string imbued ostream: "+os2.str(), 
	os2.str() == std::string("2002-Okt-01"));

  date infin(pos_infin);
  os2.str(""); //clear stream
  datef::date_put(infin, os2);
  check("check string imbued ostream: "+os2.str(), 
 	os2.str() == std::string("+unbegrenztheit"));

  os2.str(""); //clear stream
  os2 << infin;
  check("check string imbued ostream: "+os2.str(), 
 	os2.str() == std::string("+unbegrenztheit"));


  date nadt(not_a_date_time);
  os2.str(""); //clear stream
  datef::date_put(nadt, os2);
  check("check string imbued ostream: "+os2.str(), 
 	os2.str() == std::string("NichtDatumzeit"));
  

  std::stringstream os3;
  os3 << d1;
  check("check any old ostream: "+os3.str(), 
 	os3.str() == std::string("2002-Oct-01"));

  std::ofstream f("test_facet_file.out");
  f << d1 << std::endl;
  
//   // date formatter that takes locale and gets facet from locale


#else
  check("All pass, no tests executed - Locales not supported", true);

#endif //BOOST_NO_STD_LOCALE

  printTestStats();


  return 0;
}
