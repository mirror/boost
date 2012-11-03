//
//  sp_array_cv_test.cpp
//
//  Copyright (c) 2012 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/shared_ptr.hpp>

struct X
{
};

int main()
{
    boost::shared_ptr< X[] > px;

    boost::shared_ptr< X const[] > pcx( px );
    boost::shared_ptr< X volatile[] > pvx( px );

    boost::shared_ptr< X const volatile[] > pcvx( px );
    boost::shared_ptr< X const volatile[] > pcvx2( pcx );
    boost::shared_ptr< X const volatile[] > pcvx3( pvx );

    boost::shared_ptr< void > pv( px );

    boost::shared_ptr< void const > pcv( px );
    boost::shared_ptr< void const > pcv2( pcx );

    boost::shared_ptr< void volatile > pvv( px );
    boost::shared_ptr< void volatile > pvv2( pvx );

    boost::shared_ptr< void const volatile > pcvv( px );
    boost::shared_ptr< void const volatile > pcvv2( pcx );
    boost::shared_ptr< void const volatile > pcvv3( pvx );
    boost::shared_ptr< void const volatile > pcvv4( pcvx );

    return 0;
}
