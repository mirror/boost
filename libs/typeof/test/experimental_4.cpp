#include <typeinfo>

template<const std::type_info& info>
struct msvc_register_type {
};

int main() {
    msvc_register_type<typeid(double)>;
}