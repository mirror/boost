# Add a library target to the build system
boost_library_project(
  graph_parallel
  SRCDIRS  src
  TESTDIRS  test
  HEADERS graph graph/parallel
  # DOCDIRS doc
  DESCRIPTION  "Parallel support using MPI for Boost.Graph."
  AUTHORS  "Douglas Gregor <doug.gregor -at- gmail.com>"
           "Nicholas Edmonds <ngedmond -at- osl.iu.edu>"
           "Jeremiah Willcock <jewillco -at- osl.iu.edu>"
           "Andrew Lumsdaine"
  #  MAINTAINERS 
)


