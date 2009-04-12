int global_integer;
static int global_static_integer;
const int global_const_integer;
static const int global_static_const_integer;
enum global_enum { enumerator };

namespace example
{
    int namespace_integer;
    static int namespace_static_integer;
    const int namespace_const_integer;
    static const int namespace_static_const_integer;
    enum namespace_enum { enumerator };

    class example
    {
    public:
        int integer;
        static int static_integer;
        mutable int mutable_integer;
        const int const_integer;
        static mutable int static_mutable_integer;
        static const int static_const_integer;

        enum class_enum { enumerator };
    protected:
        int protected_integer;
        static int protected_static_integer;
        mutable int protected_mutable_integer;
        const int protected_const_integer;
        static mutable int protected_static_mutable_integer;
        static const int protected_static_const_integer;

        enum protected_class_enum { enumerator };
    private:
        int private_integer;
        static int private_static_integer;
        mutable int private_mutable_integer;
        const int private_const_integer;
        static mutable int private_static_mutable_integer;
        static const int private_static_const_integer;

        enum private_class_enum { enumerator };
    };
    
    template <typename TypeParameter, int NonTypeParameter,
        typename TypeParameterWithDefault = int>
    struct example_template {};
}