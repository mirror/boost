
template<typename ID>
struct msvc_extract_type
{
    struct id2type;
};

template<typename T, typename ID>
struct msvc_register_type : msvc_extract_type<ID>
{
    typedef msvc_extract_type<ID> base_type;
    struct base_type::id2type // This uses nice VC6.5 and VC7.1 bugfeature
    {
        typedef T type;
    };
};

int main() {
    sizeof(msvc_register_type<double,int>);
    typedef msvc_extract_type<int>::id2type::type deduced_type;
    deduced_type f=5.0;
    return 0;
}