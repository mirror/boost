../../../../dist/bin/wave\
    -S ../../../..\
    -S "C:\\Program Files\\Microsoft Visual Studio .NET 2003\\vc7\\include"\
    -D _WIN32\
    -D BOOST_PROTO_DOXYGEN_INVOKED\
    -p 1\
    `cygpath -d $1`
