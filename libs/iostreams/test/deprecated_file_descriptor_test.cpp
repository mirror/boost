#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"
#include "detail/file_handle.hpp"

// Test file_descriptor with the depreacted constructors.

namespace boost_ios = boost::iostreams;
namespace ios_test = boost::iostreams::test;

void deprecated_file_descriptor_test()
{
    typedef boost_ios::stream<boost_ios::file_descriptor_source> fdistream;
    typedef boost_ios::stream<boost_ios::file_descriptor_sink>   fdostream;
    typedef boost_ios::stream<boost_ios::file_descriptor>        fdstream;

    ios_test::test_file  test1;       
    ios_test::test_file  test2;       
                    
    //--------------Deprecated file descriptor constructor--------------------//

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        {
            boost_ios::file_descriptor_source source1(handle);
            BOOST_CHECK(source1.handle() == handle);
        }
        BOOST_CHECK_HANDLE_OPEN(handle);
        ios_test::close_file_handle(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        {
            boost_ios::file_descriptor_source source1(handle, false);
            BOOST_CHECK(source1.handle() == handle);
        }
        BOOST_CHECK_HANDLE_OPEN(handle);
        ios_test::close_file_handle(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        {
            boost_ios::file_descriptor_source source1(handle, true);
            BOOST_CHECK(source1.handle() == handle);
        }
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        boost_ios::file_descriptor_source source1(handle);
        BOOST_CHECK(source1.handle() == handle);
        source1.close();
        BOOST_CHECK(!source1.is_open());
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        boost_ios::file_descriptor_source source1(handle, false);
        BOOST_CHECK(source1.handle() == handle);
        source1.close();
        BOOST_CHECK(!source1.is_open());
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        boost_ios::file_descriptor_source source1(handle, true);
        BOOST_CHECK(source1.handle() == handle);
        source1.close();
        BOOST_CHECK(!source1.is_open());
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    //--------------Deprecated file descriptor open---------------------------//

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        {
            boost_ios::file_descriptor_source source1;
            source1.open(handle);
            BOOST_CHECK(source1.handle() == handle);
        }
        BOOST_CHECK_HANDLE_OPEN(handle);
        ios_test::close_file_handle(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        {
            boost_ios::file_descriptor_source source1;
            source1.open(handle, false);
            BOOST_CHECK(source1.handle() == handle);
        }
        BOOST_CHECK_HANDLE_OPEN(handle);
        ios_test::close_file_handle(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        {
            boost_ios::file_descriptor_source source1;
            source1.open(handle, true);
            BOOST_CHECK(source1.handle() == handle);
        }
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        boost_ios::file_descriptor_source source1;
        source1.open(handle);
        BOOST_CHECK(source1.handle() == handle);
        source1.close();
        BOOST_CHECK(!source1.is_open());
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        boost_ios::file_descriptor_source source1;
        source1.open(handle, false);
        BOOST_CHECK(source1.handle() == handle);
        source1.close();
        BOOST_CHECK(!source1.is_open());
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    {
        boost_ios::detail::file_handle handle = ios_test::open_file_handle(test1.name());
        boost_ios::file_descriptor_source source1;
        source1.open(handle, true);
        BOOST_CHECK(source1.handle() == handle);
        source1.close();
        BOOST_CHECK(!source1.is_open());
        BOOST_CHECK_HANDLE_CLOSED(handle);
    }

    //--------------Deprecated open with existing descriptor------------------//

    {
        boost_ios::detail::file_handle handle1 = ios_test::open_file_handle(test1.name());
        boost_ios::detail::file_handle handle2 = ios_test::open_file_handle(test1.name());

        {
            boost_ios::file_descriptor_source source1(handle1);
            BOOST_CHECK(source1.handle() == handle1);
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
            source1.open(handle2);
            BOOST_CHECK(source1.handle() == handle2);
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
            source1.close();
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_CLOSED(handle2);
        }
        BOOST_CHECK_HANDLE_OPEN(handle1);
        BOOST_CHECK_HANDLE_CLOSED(handle2);

        ios_test::close_file_handle(handle1);
    }

    {
        boost_ios::detail::file_handle handle1 = ios_test::open_file_handle(test1.name());
        boost_ios::detail::file_handle handle2 = ios_test::open_file_handle(test1.name());

        {
            boost_ios::file_descriptor_source source1(handle1, true);
            BOOST_CHECK(source1.handle() == handle1);
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
            source1.open(handle2);
            BOOST_CHECK(source1.handle() == handle2);
            BOOST_CHECK_HANDLE_CLOSED(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
            source1.close();
            BOOST_CHECK_HANDLE_CLOSED(handle1);
            BOOST_CHECK_HANDLE_CLOSED(handle2);
        }
        BOOST_CHECK_HANDLE_CLOSED(handle1);
        BOOST_CHECK_HANDLE_CLOSED(handle2);
    }

    {
        boost_ios::detail::file_handle handle1 = ios_test::open_file_handle(test1.name());
        boost_ios::detail::file_handle handle2 = ios_test::open_file_handle(test1.name());

        {
            boost_ios::file_descriptor_source source1(handle1, false);
            BOOST_CHECK(source1.handle() == handle1);
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
            source1.open(handle2, false);
            BOOST_CHECK(source1.handle() == handle2);
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
        }
        BOOST_CHECK_HANDLE_OPEN(handle1);
        BOOST_CHECK_HANDLE_OPEN(handle2);

        ios_test::close_file_handle(handle1);
        ios_test::close_file_handle(handle2);
    }

    {
        boost_ios::detail::file_handle handle1 = ios_test::open_file_handle(test1.name());
        boost_ios::detail::file_handle handle2 = ios_test::open_file_handle(test1.name());

        {
            boost_ios::file_descriptor_source source1(handle1, true);
            BOOST_CHECK(source1.handle() == handle1);
            BOOST_CHECK_HANDLE_OPEN(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
            source1.open(handle2, true);
            BOOST_CHECK(source1.handle() == handle2);
            BOOST_CHECK_HANDLE_CLOSED(handle1);
            BOOST_CHECK_HANDLE_OPEN(handle2);
        }
        BOOST_CHECK_HANDLE_CLOSED(handle1);
        BOOST_CHECK_HANDLE_CLOSED(handle2);
    }
}

boost::unit_test::test_suite* init_unit_test_suite(int, char* []) 
{
    boost::unit_test::test_suite* test = BOOST_TEST_SUITE("deprecated file_descriptor test");
    test->add(BOOST_TEST_CASE(&deprecated_file_descriptor_test));
    return test;
}
