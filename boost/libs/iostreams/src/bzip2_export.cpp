// (C) Copyright Jonathan Turkanis 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Specifies the symbols to be exported.

#include <boost/config.hpp>  // BOOST_MSVC.

#if defined(BOOST_MSVC) || \
    (defined(__ICL) && defined(_MSC_EXTENSIONS) && (_MSC_VER >= 1200)) \
    /**/
# pragma comment(linker, "/export:BZ2_bzCompress")
# pragma comment(linker, "/export:BZ2_bzCompressEnd")
# pragma comment(linker, "/export:BZ2_bzCompressInit")
# pragma comment(linker, "/export:BZ2_bzDecompress")
# pragma comment(linker, "/export:BZ2_bzDecompressEnd")
# pragma comment(linker, "/export:BZ2_bzDecompressInit")
# pragma comment(linker, "/export:BZ_CONFIG_ERROR")
# pragma comment(linker, "/export:BZ_DATA_ERROR")
# pragma comment(linker, "/export:BZ_DATA_ERROR_MAGIC")
# pragma comment(linker, "/export:BZ_FINISH_OK")
# pragma comment(linker, "/export:BZ_FLUSH_OK")
# pragma comment(linker, "/export:BZ_IO_ERROR")
# pragma comment(linker, "/export:BZ_MEM_ERROR")
# pragma comment(linker, "/export:BZ_OK")
# pragma comment(linker, "/export:BZ_OUTBUFF_FULL")
# pragma comment(linker, "/export:BZ_PARAM_ERROR")
# pragma comment(linker, "/export:BZ_RUN_OK")
# pragma comment(linker, "/export:BZ_SEQUENCE_ERROR")
# pragma comment(linker, "/export:BZ_STREAM_END")
# pragma comment(linker, "/export:BZ_UNEXPECTED_EOF")
#endif // MSVC and Intel
#if defined(__MWERKS__)
# pragma export list BZ2_bzCompress
# pragma export list BZ2_bzCompressEnd
# pragma export list BZ2_bzCompressInit
# pragma export list BZ2_bzDecompress
# pragma export list BZ2_bzDecompressEnd
# pragma export list BZ2_bzDecompressInit
# pragma export list BZ_CONFIG_ERROR
# pragma export list BZ_DATA_ERROR
# pragma export list BZ_DATA_ERROR_MAGIC
# pragma export list BZ_FINISH_OK
# pragma export list BZ_FLUSH_OK
# pragma export list BZ_IO_ERROR
# pragma export list BZ_MEM_ERROR
# pragma export list BZ_OK
# pragma export list BZ_OUTBUFF_FULL
# pragma export list BZ_PARAM_ERROR
# pragma export list BZ_RUN_OK
# pragma export list BZ_SEQUENCE_ERROR
# pragma export list BZ_STREAM_END
# pragma export list BZ_UNEXPECTED_EOF
#endif // Metrowerks
