// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor

/** @file request.cpp
 *
 *  This file reflects the Boost.MPI @c request class into
 *  Python.
 */
#include <boost/python.hpp>
#include <boost/mpi.hpp>

using namespace boost::python;
using namespace boost::mpi;

namespace boost { namespace mpi { namespace python {

extern const char* request_docstring;
extern const char* request_wait_docstring;
extern const char* request_test_docstring;
extern const char* request_cancel_docstring;

object request_wait(object req_obj)
{
  request& req = extract<request&>(req_obj)();
  status stat = req.wait();
  if (PyObject_HasAttrString(req_obj.ptr(), "value"))
    return boost::python::make_tuple(stat, req_obj.attr("value"));
  else
    return object(stat);  
}

object request_test(object req_obj)
{
  request& req = extract<request&>(req_obj)();

  if (optional<status> stat = req.test())
    {
      if (PyObject_HasAttrString(req_obj.ptr(), "value"))
        return boost::python::make_tuple(stat, req_obj.attr("value"));
      else
        return object(stat);
    }
  else
    return object();
}

void export_request()
{
  using boost::python::arg;
  using boost::python::object;
  
  class_<request>("request", request_docstring, no_init)
    .def("wait", &request_wait, request_wait_docstring)
    .def("test", &request_test, request_test_docstring)
    .def("cancel", &request::cancel, request_cancel_docstring)
    ;
}

} } } // end namespace boost::mpi::python
