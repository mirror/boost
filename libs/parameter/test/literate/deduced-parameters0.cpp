
#line 1029 "../../../../libs/parameter/doc/index.rst"
#include <boost/parameter.hpp>

BOOST_PARAMETER_NAME(name)
BOOST_PARAMETER_NAME(func)
BOOST_PARAMETER_NAME(docstring)
BOOST_PARAMETER_NAME(keywords)
BOOST_PARAMETER_NAME(policies)

struct default_call_policies
{};

struct no_keywords
{};

struct keywords
{};

template <class T>
struct is_keyword_expression
  : boost::mpl::false_
{};

template <>
struct is_keyword_expression<keywords>
  : boost::mpl::true_
{};

default_call_policies some_policies;

void f()
{}
#line 996 "../../../../libs/parameter/doc/index.rst"
namespace mpl = boost::mpl;

BOOST_PARAMETER_FUNCTION(
    (void), def, tag,

    (required (name,(char const*)) (func,*) )   // nondeduced

    (deduced
      (optional
        (docstring, (char const*), "")

        (keywords
           , *(is_keyword_expression<mpl::_>) // see 5
           , no_keywords())

        (policies
           , *(mpl::not_<
                 mpl::or_<
                     boost::is_convertible<mpl::_, char const*>
                   , is_keyword_expression<mpl::_> // see 5
                 >
             >)
           , default_call_policies()
         )
       )
     )
 )
 {
    
 }


#line 1078 "../../../../libs/parameter/doc/index.rst"
int main()
{
#line 1075 "../../../../libs/parameter/doc/index.rst"
def("f", &f, some_policies, "Documentation for f");
def("f", &f, "Documentation for f", some_policies);

#line 1088 "../../../../libs/parameter/doc/index.rst"
def(
    "f", &f
   , _policies = some_policies, "Documentation for f");
#line 1091 "../../../../libs/parameter/doc/index.rst"
}

