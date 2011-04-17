/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::casual unit test

#define BOOST_ICL_TEST_CHRONO

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

BOOST_AUTO_TEST_CASE(invariance_wrt_compare_ordering_ticket_5482)
{
    typedef int T;
    typedef int U;
    typedef interval_map<T,U, partial_absorber> IntervalMapT;
    typedef interval_map<T,U, partial_absorber,std::less> IntervalLtMapT;
    typedef interval_map<T,U, partial_absorber,std::greater> IntervalGtMapT;
    typedef interval_set<T>                     IntervalSetT;
    typedef IntervalMapT::interval_type         IntervalT;
    typedef IntervalLtMapT::interval_type       IntervalLtT;
    typedef IntervalGtMapT::interval_type       IntervalGtT;

    IntervalLtMapT lt_map;
    IntervalGtMapT gt_map;

    BOOST_CHECK( IntervalLtMapT::domain_compare()(0,1));
    BOOST_CHECK(!IntervalLtMapT::domain_compare()(1,0));
    BOOST_CHECK( IntervalGtMapT::domain_compare()(1,0));
    BOOST_CHECK(!IntervalGtMapT::domain_compare()(0,1));

    IntervalGtT(5);

    lt_map.insert(make_pair(IntervalLtT(1),1));
    lt_map.insert(make_pair(IntervalLtT(2),1));

    gt_map.insert(make_pair(IntervalGtT(2,1),1));
    gt_map.insert(make_pair(IntervalGtT(3,2),1));
    gt_map.insert(make_pair(IntervalGtT(5,4),1));
    gt_map.add(make_pair(IntervalGtT(8,2),1));

    cout << "-----------------------------\n";
    cout << "lt_map.iterative_size() = " << lt_map.iterative_size() << endl;
    cout << "gt_map.iterative_size() = " << gt_map.iterative_size() << endl;
    cout << "gt_map : " << gt_map << endl;
    

    BOOST_CHECK_EQUAL(true, true);
}


BOOST_AUTO_TEST_CASE(ticket_5482)
{
    typedef interval_map<int,int,partial_absorber,std::less>    m1_t;
    typedef interval_map<int,int,partial_absorber,std::greater> m2_t;
    m1_t m1;
    m2_t m2;
    m1.insert(make_pair(m1_t::interval_type(1), 20));
    m1.insert(make_pair(m1_t::interval_type(2), 20));
    m1.insert(make_pair(m1_t::interval_type(3), 20));

    m2.insert(make_pair(m2_t::interval_type(1), 20));
    m2.insert(make_pair(m2_t::interval_type(2), 20));
    m2.insert(make_pair(m2_t::interval_type(3), 20));
    BOOST_CHECK_EQUAL(m1.iterative_size(), m2.iterative_size());
}

BOOST_AUTO_TEST_CASE(casual)
{
    typedef int T;
    typedef int U;
    typedef interval_map<T,U, partial_absorber> IntervalMapT;
    typedef interval_set<T>                     IntervalSetT;
    typedef IntervalMapT::interval_type         IntervalT;

    BOOST_CHECK_EQUAL(true, true);
}


