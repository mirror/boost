
struct msvc_extract_type_default_param {};

template<typename ID, typename T = msvc_extract_type_default_param>
struct msvc_extract_type;

template<typename ID>
struct msvc_extract_type<ID, msvc_extract_type_default_param> {
    template<bool>
    struct id2type_impl;

    typedef id2type_impl<true> id2type;
};

template<typename ID, typename T>
struct msvc_extract_type : msvc_extract_type<ID,msvc_extract_type_default_param>
{
    template<>
    struct id2type_impl<true>  //VC8.0 specific bugfeature
    {
        typedef T type;
    };
    template<bool>
    struct id2type_impl;

    typedef id2type_impl<true> id2type;
};

template<typename T, typename ID>
struct msvc_register_type : msvc_extract_type<ID, T>
{
};

int main() {
    sizeof(msvc_register_type<double,int>);
    typedef msvc_extract_type<int>::id2type::type deduced_type;
    deduced_type f=5.0;
    return 0;
}