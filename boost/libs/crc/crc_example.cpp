//  Boost CRC example program file  ------------------------------------------//

//  (C) Copyright Daryle Walker 2003.  Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice
//  appears in all copies.  This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

//  Revision History
//  17 Jun 2003  Initial version (Daryle Walker)

#include <boost/crc.hpp>  // for boost::crc_32_type

#include <cstdlib>    // for EXIT_SUCCESS, EXIT_FAILURE
#include <exception>  // for std::exception
#include <fstream>    // for std::ifstream
#include <ios>        // for std::ios_base, etc.
#include <iostream>   // for std::cerr, std::cout
#include <ostream>    // for std::endl


// Redefine this to change to processing buffer size
#ifndef PRIVATE_BUFFER_SIZE
#define PRIVATE_BUFFER_SIZE  1024
#endif

// Global objects
std::streamsize const  buffer_size = PRIVATE_BUFFER_SIZE;


// Main program
int
main
(
    int           argc,
    char const *  argv[]
)
try
{
    boost::crc_32_type  result;

    for ( int i = 1 ; i < argc ; ++i )
    {
        std::ifstream  ifs( argv[i], std::ios_base::binary );

        if ( ifs )
        {
            do
            {
                char  buffer[ buffer_size ];

                ifs.read( buffer, buffer_size );
                result.process_bytes( buffer, ifs.gcount() );
            } while ( ifs );
        }
        else
        {
            std::cerr << "Failed to open file '" << argv[i] << "'."
             << std::endl;
        }
    }

    std::cout << std::hex << std::uppercase << result.checksum() << std::endl;
    return EXIT_SUCCESS;
}
catch ( std::exception &e )
{
    std::cerr << "Found an exception with '" << e.what() << "'." << std::endl;
    return EXIT_FAILURE;
}
catch ( ... )
{
    std::cerr << "Found an unknown exception." << std::endl;
    return EXIT_FAILURE;
}
