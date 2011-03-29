/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::casual unit test

#include <libs/icl/test/disable_test_warnings.hpp>

#include <string>
#include <vector>
#include <boost/mpl/list.hpp>
#include "../unit_test_unwarned.hpp"
#include <boost/test/test_case_template.hpp>


// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"

#include <boost/rational.hpp>
#include <boost/icl/chrono.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/icl/gregorian.hpp>
#include <boost/icl/ptime.hpp>

#define BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>



using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;

namespace boost{ namespace scalars 
{
/*
template<class Origin = constant<0>, class Factor = ratio<1,1>, class Rep>
class scalar
{
public:
private:

}
*/
}} //namespace boost scalars

class MyInt
{
public:
    MyInt():_rep() { cout << "default constructed\n"; }
    int value()const { return _rep; }
private:
    int _rep;
};

BOOST_AUTO_TEST_CASE(chrono_duration_ctor)
{
    using namespace boost::chrono;

    chrono::duration<int> cd_default0 = chrono::duration<int>();
    cout << "chrono::duration<int>() = " << cd_default0 << endl;

    chrono::duration<double> cd_default1 = chrono::duration<double>();
    cout << "chrono::duration<double>() = " << cd_default1 << endl;

    chrono::duration<rational<int> > cd_default2 = chrono::duration<rational<int> >();
    cout << "chrono::duration<rational<int> >() = " << cd_default2 << endl;

    chrono::duration<complex<float> > cd_default3 = chrono::duration<complex<float> >();
    cout << "chrono::duration<complex<float> >() = " << cd_default3 << endl;

/*
    chrono::duration<MyInt> cd_default = chrono::duration<MyInt>();
    cout << "chrono::duration<MyInt>() = " << cd_default.count().value() << endl;
    cout << "===============================\n";

    duration<int, ratio<60> > min1(1);
    duration<int, ratio<1,100> > centi1(1);
    duration<int, ratio<1,100> > centi2 = min1 + centi1;
    cout << "centi2 = " << centi2 << " centi2.count() = " << centi2.count() << endl;

    centi2 += centi1;
    cout << "++centi2=" << centi2 << " centi2.count() = " << centi2.count() << endl;
*/
}

BOOST_AUTO_TEST_CASE(test_difference_types)
{
    BOOST_CHECK(( boost::is_same< int,            difference_type_of<int>::type >::value ));
    BOOST_CHECK(( boost::is_same< double,         difference_type_of<double>::type >::value ));
    BOOST_CHECK(( boost::is_same< std::ptrdiff_t, difference_type_of<int*>::type >::value ));

    BOOST_CHECK(( has_difference_type<std::string>::value ));
    BOOST_CHECK(( boost::is_same< std::string::difference_type, difference_type_of<std::string>::type >::value ));
    BOOST_CHECK(( boost::is_same< std::ptrdiff_t, difference_type_of<std::string>::type >::value ));

    BOOST_CHECK((  boost::is_same<                    chrono::duration<int>
                                 , difference_type_of<chrono::duration<int> >::type >::value ));
    BOOST_CHECK((  boost::is_same<                    chrono::duration<double>
                                 , difference_type_of<chrono::duration<double> >::type >::value ));

    BOOST_CHECK((  boost::is_same<                    Now::time_point::duration
                                 , difference_type_of<Now::time_point>::type >::value ));

    typedef boost::chrono::time_point<Now, boost::chrono::duration<double> > contin_timeT;
    BOOST_CHECK((  boost::is_same<                    contin_timeT::duration
                                 , difference_type_of<contin_timeT>::type >::value ));

    typedef boost::chrono::time_point<Now, boost::chrono::duration<int> > discr_timeT;
    BOOST_CHECK((  boost::is_same<                    chrono::duration<int>
                                 , difference_type_of<discr_timeT>::type >::value ));
}

BOOST_AUTO_TEST_CASE(test_size_types)
{
    BOOST_CHECK(( boost::is_same< std::size_t,    size_type_of<int>::type >::value ));
    BOOST_CHECK(( boost::is_same< std::size_t,    size_type_of<double>::type >::value ));
    BOOST_CHECK(( boost::is_same< std::size_t,    size_type_of<int*>::type >::value ));
    BOOST_CHECK(( boost::is_same< std::size_t,    size_type_of<std::string>::type >::value ));
    BOOST_CHECK(( boost::is_same<              chrono::duration<int>
                                , size_type_of<chrono::duration<int> >::type >::value ));
    BOOST_CHECK(( boost::is_same<              chrono::duration<double>
                                , size_type_of<chrono::duration<double> >::type >::value ));

    typedef boost::chrono::time_point<Now, boost::chrono::duration<int> > discr_timeT;
    BOOST_CHECK((  boost::is_same< chrono::duration<int>
                                 , size_type_of<discr_timeT>::type >::value ));

    typedef boost::chrono::time_point<Now, boost::chrono::duration<double> > contin_timeT;
    BOOST_CHECK((  boost::is_same< contin_timeT::duration
                                 , size_type_of<contin_timeT>::type >::value ));
}

BOOST_AUTO_TEST_CASE(test_chrono_identity_elements)
{
    chrono::duration<int> idel_i = icl::identity_element<chrono::duration<int> >::value();
    cout << "dur<int>0 = " << idel_i << endl;
    chrono::duration<double> idel_d = icl::identity_element<chrono::duration<int> >::value();
    cout << "dur<dbl>0 = " << idel_d << endl;

    BOOST_CHECK(( boost::is_same<              chrono::duration<int>
                                , size_type_of<chrono::duration<int> >::type >::value ));
}



BOOST_AUTO_TEST_CASE(test_infinities)
{
    BOOST_CHECK(( has_std_infinity<double>::value));
    BOOST_CHECK((!has_std_infinity<int>::value));

    BOOST_CHECK(( has_max_infinity<int>::value ));
    BOOST_CHECK((!has_max_infinity<double>::value ));

    //--------------------------------------------------------------------------
    BOOST_CHECK_EQUAL( numeric_infinity<double>::value(),  (std::numeric_limits<double>::infinity)() );
    BOOST_CHECK_EQUAL( numeric_infinity<int>::value(),     (std::numeric_limits<int>::max)() );
    BOOST_CHECK_EQUAL( numeric_infinity<std::string>::value(), std::string() );

    //--------------------------------------------------------------------------
    BOOST_CHECK_EQUAL( infinity<double>::value(),  (std::numeric_limits<double>::infinity)() );
    BOOST_CHECK_EQUAL( infinity<int>::value(),     (std::numeric_limits<int>::max)() );
    BOOST_CHECK_EQUAL( infinity<std::string>::value(), identity_element<std::string>::value() );

    //--------------------------------------------------------------------------
    BOOST_CHECK_EQUAL( infinity<chrono::duration<double> >::value()
                     , chrono::duration<double>((std::numeric_limits<double>::infinity)()) );
    BOOST_CHECK_EQUAL( infinity<chrono::duration<int> >::value()
                     , chrono::duration<int>((std::numeric_limits<int>::max)()) );

}

BOOST_AUTO_TEST_CASE(casual)
{
    //typedef int T;
    //typedef int U;
    //typedef interval_map<T,U, total_absorber> IntervalMapT;
    //typedef interval_set<T>                   IntervalSetT;
    //typedef IntervalMapT::interval_type       IntervalT;

    BOOST_CHECK((has_std_infinity<double>::value));

    BOOST_CHECK((boost::detail::is_incrementable<chrono::duration<int> >::value));

    BOOST_CHECK((has_rep_type<chrono::duration<int> >::value));
    BOOST_CHECK((represents<int, chrono::duration<int> >::value));

    BOOST_CHECK((!is_discrete<chrono::duration<double> >::value));

    //BOOST_CHECK((!is_discrete<Now_time_rational>::value));
    BOOST_CHECK(( is_continuous<boost::rational<int> >::value));
    BOOST_CHECK(( !is_discrete<boost::rational<int> >::value));

    BOOST_CHECK(( has_rep_type<Now_time_rational>::value));
    BOOST_CHECK(( is_continuous<Now_time_rational>::value));
    BOOST_CHECK(( !is_discrete<Now_time_rational>::value));
    BOOST_CHECK(( is_continuous<typename rep_type_of<Now_time_rational>::type>::value));


    BOOST_CHECK_EQUAL(true, true);
}

