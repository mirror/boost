
#include <boost/serialization/export.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

#include "test_polymorphic2.hpp"

void A::serialize(
    boost::archive::polymorphic_oarchive &ar, 
    const unsigned int /*version*/
){
    ar & BOOST_SERIALIZATION_NVP(i);
}
void A::serialize(
    boost::archive::polymorphic_iarchive &ar, 
    const unsigned int /*version*/
){
    ar & BOOST_SERIALIZATION_NVP(i);
}
// note: only the most derived classes need be exported
// BOOST_CLASS_EXPORT(A)

void B::serialize(
    boost::archive::polymorphic_oarchive &ar, 
    const unsigned int /*version*/
){
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
}
void B::serialize(
    boost::archive::polymorphic_iarchive &ar, 
    const unsigned int /*version*/
){
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
}
BOOST_CLASS_EXPORT(B)
