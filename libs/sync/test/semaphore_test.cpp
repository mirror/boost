// Copyright (C) 2013 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>

#include <boost/thread.hpp>
#include <boost/sync/semaphore.hpp>

#include <boost/typeof/typeof.hpp>

BOOST_AUTO_TEST_CASE(test_semaphore_post_wait)
{
    boost::sync::semaphore sem(0);

    sem.post();
    sem.wait();
}


BOOST_AUTO_TEST_CASE(test_semaphore_try_wait)
{
    boost::sync::semaphore sem(0);

    BOOST_REQUIRE(!sem.try_wait());
    sem.post();
    BOOST_REQUIRE(sem.try_wait());
}


struct semaphore_wait_and_post_test
{
    void run()
    {
        boost::thread post_thread(boost::bind(&semaphore_wait_and_post_test::wait_and_post, this));
        sem_.wait();
    }

    void wait_and_post()
    {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        sem_.post();
    }

    boost::sync::semaphore sem_;
    boost::thread thread_;
};

BOOST_AUTO_TEST_CASE(semaphore_wait_and_post)
{
    semaphore_wait_and_post_test test;
    test.run();
}

#ifdef BOOST_SYNC_USES_CHRONO

BOOST_AUTO_TEST_CASE(test_semaphore_wait_for)
{
    using namespace boost;

    sync::semaphore sem(0);

    BOOST_AUTO(start, chrono::system_clock::now());

    BOOST_REQUIRE(!sem.try_wait_for(chrono::milliseconds(500)));

    BOOST_AUTO(end, chrono::system_clock::now());
    BOOST_AUTO(wait_time, end - start);

    // guessing!
    BOOST_REQUIRE( wait_time > chrono::milliseconds(450) );
    BOOST_REQUIRE( wait_time < chrono::milliseconds(1000) );

    sem.post();

    BOOST_REQUIRE(sem.try_wait_for(chrono::milliseconds(500)));
}

BOOST_AUTO_TEST_CASE(test_semaphore_wait_until)
{
    using namespace boost;

    sync::semaphore sem(0);
    {
        BOOST_AUTO(now, chrono::system_clock::now());
        BOOST_AUTO(timeout, now + chrono::milliseconds(500));

        BOOST_REQUIRE(!sem.try_wait_until(timeout));

        BOOST_AUTO(end, chrono::system_clock::now());
        BOOST_AUTO(timeout_delta, end - timeout);

        // guessing!
        BOOST_REQUIRE( timeout_delta > chrono::milliseconds(-400) );
        BOOST_REQUIRE( timeout_delta < chrono::milliseconds(400) );
    }

    sem.post();

    {
        BOOST_AUTO(start,   chrono::system_clock::now());
        BOOST_AUTO(timeout, start + chrono::milliseconds(500));

        BOOST_REQUIRE(sem.try_wait_until(timeout));

        BOOST_AUTO(end, chrono::system_clock::now());

        // guessing!
        BOOST_REQUIRE( (end - start) < chrono::milliseconds(100) );
    }
}
#endif
