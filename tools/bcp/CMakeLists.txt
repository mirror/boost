boost_tool_project(bcp
DESCRIPTION "The bcp utility is a tool for extracting subsets of Boost."
AUTHORS "John Maddock")

option(BOOST_BUILD_BCP "Build the bcp tool" ON)
IF (BOOST_BUILD_BCP)

# add_definitions("-DBOOST_REGEX_NO_LIB=1")
boost_test_add_dependent_includes("filesystem;smart_ptr;config;detail;system;iterator;exception;type_traits;static_assert;utility;mpl;preprocessor;integer;regex;date_time;algorithm")

set (bcp_sources
  add_path.cpp 
  bcp_imp.cpp 
  copy_path.cpp 
  file_types.cpp
  fileview.cpp 
  main.cpp 
  path_operations.cpp 
  scan_cvs_path.cpp 
  licence_info.cpp 
  scan_licence.cpp 
  output_licence_info.cpp
)

boost_add_executable(
  bcp
  ${bcp_sources}
  DEPENDS boost_filesystem boost_prg_exec_monitor boost_regex
)

ENDIF (BOOST_BUILD_BCP)