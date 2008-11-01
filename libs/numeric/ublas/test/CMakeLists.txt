# Define features to test:
#  Value types: USE_FLOAT USE_DOUBLE USE_STD_COMPLEX
#  Proxies: USE_RANGE USE_SLICE
#  Storage types: USE_BOUNDED_ARRAY USE_UNBOUNDED_ARRAY
#  Vector types: USE_STD_VECTOR USE_BOUNDED_VECTOR
#  Matrix types: USE_MATRIX USE_BOUNDED_MATRIX USE_VECTOR_OF_VECTOR
#  Adaptors: USE_ADAPTOR

set(UBLAS_TESTSET_DEFINES
  "-DUSE_DOUBLE -DUSE_STD_COMPLEX -DUSE_RANGE -DUSE_SLICE -DUSE_UNBOUNDED_ARRAY -DUSE_STD_VECTOR -DUSE_BOUNDED_VECTOR -DUSE_MATRIX")

#  Sparse storage: USE_MAP_ARRAY USE_STD_MAP
#  Sparse vectors: USE_MAPPED_VECTOR USE_COMPRESSED_VECTOR USE_COORDINATE_VECTOR
#  Sparse matrices: USE_MAPPED_MATRIX USE_COMPRESSED_MATRIX USE_COORDINATE_MATRIX USE_MAPPED_VECTOR_OF_MAPPED_VECTOR USE_GENERALIZED_VECTOR_OF_VECTOR

set(UBLAS_TESTSET_SPARSE_DEFINES
  "-DUSE_DOUBLE -DUSE_STD_COMPLEX -DUSE_UNBOUNDED_ARRAY -DUSE_MAP_ARRAY -DUSE_STD_MAP -DUSE_MAPPED_VECTOR -DUSE_COMPRESSED_VECTOR -DUSE_COORDINATE_VECTOR -DUSE_MAPPED_MATRIX -DUSE_COMPRESSED_MATRIX -DUSE_COORDINATE_MATRIX")

# Definitions for uBLAS tests
add_definitions(-DBOOST_UBLAS_NO_EXCEPTIONS)
# TODO: <toolset>vacpp:<define>"BOOST_UBLAS_NO_ELEMENT_PROXIES"

#-------------------------------------------------------------------------
#-- Needed include directories for the tests
boost_test_add_dependent_includes("utility;detail;config;test;mpl;serialization;type_traits;static_assert;preprocessor;array;iterator;exception;concept_check;concept")
#-------------------------------------------------------------------------


boost_test_run(ublas_test1
  test1.cpp test11.cpp test12.cpp test13.cpp
  COMPILE_FLAGS "${UBLAS_TESTSET_DEFINES}")

boost_test_run(ublas_test2
  test2.cpp test21.cpp test22.cpp test23.cpp
  COMPILE_FLAGS "${UBLAS_TESTSET_DEFINES}")

boost_test_run(ublas_test3
  test3.cpp test31.cpp test32.cpp test33.cpp
  COMPILE_FLAGS "${UBLAS_TESTSET_SPARSE_DEFINES}")

boost_test_run(ublas_test4
  test4.cpp test42.cpp test43.cpp
  COMPILE_FLAGS "${UBLAS_TESTSET_DEFINES}")

boost_test_run(ublas_test5
  test5.cpp test52.cpp test53.cpp
  COMPILE_FLAGS "${UBLAS_TESTSET_DEFINES}")

boost_test_run(ublas_test6
  test6.cpp test62.cpp test63.cpp
  COMPILE_FLAGS "${UBLAS_TESTSET_DEFINES}")

# Test commented out, just like in V1 and V2 Jamfiles
# boost_test_run(test7
#   test7.cpp test71.cpp test72.cpp test73.cpp
#   COMPILE_FLAGS "-DBOOST_UBLAS_USE_INTERVAL ${UBLAS_TESTSET_DEFINES}")

boost_test_run(placement_new)

#TODO:
#            <toolset>intel-linux:<cxxflags>"-Xc"
#			<toolset>darwin:<cxxflags>"-fabi-version=0"

boost_test_compile(concepts COMPILE_FLAGS "-DEXTERNAL")
