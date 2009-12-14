namespace boost {
namespace archive {
    class polymorphic_oarchive;
    class polymorphic_iarchive;
}
}

struct A {
public:
    A() {}
    virtual ~A() {}

    void serialize(
        boost::archive::polymorphic_oarchive &ar, 
        const unsigned int /*version*/
    );
    void serialize(
        boost::archive::polymorphic_iarchive &ar, 
        const unsigned int /*version*/
    );

    int i;
};

struct B : A {
    void serialize(
        boost::archive::polymorphic_oarchive &ar, 
        const unsigned int /*version*/
    );
    void serialize(
        boost::archive::polymorphic_iarchive &ar, 
        const unsigned int /*version*/
    );
};
