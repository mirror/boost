boost_module(serialization DEPENDS spirit preprocessor io smart_ptr bind array)

# bind is in there because we have a dependency on boost/mem_fn.hpp
