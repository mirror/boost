
# Add a library target to the build system
boost_library_project(
  signals2
  TESTDIRS test
  HEADERS  signals2.hpp signals2
  #  DOCDIRS 
  DESCRIPTION  "The Boost.Signals2 library is an implementation of a managed signals and slots system. Signals represent callbacks with multiple targets, and are also called publishers or events in similar systems. Signals are connected to some set of slots, which are callback receivers (also called event targets or subscribers), which are called when the signal is \"emitted.\""
  MODULARIZED
  AUTHORS  "Frank Mori Hess <fixme -at- fixme.com>"
)


