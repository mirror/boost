#include <boost/static_assert.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

struct vbase 
{
};

struct derived : public virtual vbase
{
};

// VC 7.1, borland 5.51 and Commeau trap here (no gcc !)
BOOST_STATIC_ASSERT(boost::is_polymorphic<derived>::value);

// everything including gcc trap here !
BOOST_STATIC_ASSERT(boost::is_polymorphic<vbase>::value);

int main(int argc, char *argv[])
{
}
