add_executable(breadth_first_search breadth_first_search.cpp)
target_link_libraries(breadth_first_search
  boost_graph_mpi ${MPI_LIBRARIES})

set_target_properties(
  breadth_first_search
  PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}"
             COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")

if (BUILD_TESTING)
  add_test(breadth_first_search
    ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS}
    "${EXECUTABLE_OUTPUT_PATH}/\${CTEST_CONFIGURATION_TYPE}/breadth_first_search"
    ${MPIEXEC_POSTFLAGS} 
    "${CMAKE_CURRENT_SOURCE_DIR}/weighted_graph.gr"
    "${CMAKE_BINARY_DIR}/test/weighted_graph-bfs.gr")
endif (BUILD_TESTING)

add_executable(dijkstra_shortest_paths dijkstra_shortest_paths.cpp)
target_link_libraries(dijkstra_shortest_paths
  boost_graph_mpi ${MPI_LIBRARIES})

set_target_properties(
  dijkstra_shortest_paths
  PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}"
             COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")

if (BUILD_TESTING)
  add_test(dijkstra_shortest_paths
    ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS}
    "${EXECUTABLE_OUTPUT_PATH}/\${CTEST_CONFIGURATION_TYPE}/dijkstra_shortest_paths"
    ${MPIEXEC_POSTFLAGS} 
    "${CMAKE_CURRENT_SOURCE_DIR}/weighted_graph.gr"
    "${CMAKE_BINARY_DIR}/test/weighted_graph-dijkstra.gr")
endif (BUILD_TESTING)