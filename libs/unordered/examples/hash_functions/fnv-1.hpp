// See: http://www.isthe.com/chongo/tech/comp/fnv/

#include <string>

namespace hash
{
    template <std::size_t FnvPrime, std::size_t OffsetBias>
    struct basic_fnv_1
    {
        std::size_t operator()(std::string const& text) const
        {
            std::size_t hash = OffsetBias;
            for(std::string::const_iterator it = text.begin(), end = text.end();
                    it != end; ++it)
            {
                hash *= FnvPrime;
                hash ^= *it;
            }

            return hash;
        }
    };

    template <std::size_t FnvPrime, std::size_t OffsetBias>
    struct basic_fnv_1a
    {
        std::size_t operator()(std::string const& text) const
        {
            std::size_t hash = OffsetBias;
            for(std::string::const_iterator it = text.begin(), end = text.end();
                    it != end; ++it)
            {
                hash ^= *it;
                hash *= FnvPrime;
            }

            return hash;
        }
    };

    // TODO: Select Bias & Prime base on the size of std::size_t.
    //
    // 32 bit FNV_prime = 16777619
    // 64 bit FNV_prime = 1099511628211
    // 128 bit FNV_prime = 309485009821345068724781401
    // 256 bit FNV_prime = 374144419156711147060143317175368453031918731002211
    //
    // 32 bit offset_basis = 2166136261
    // 64 bit offset_basis = 14695981039346656037
    // 128 bit offset_basis = 275519064689413815358837431229664493455
    // 256 bit offset_basis = 100029257958052580907070968620625704837092796014241193945225284501741471925557

    const std::size_t fnv_prime = 16777619;
    // 64 bit FNV_prime = 1099511628211
    // 128 bit FNV_prime = 309485009821345068724781401
    // 256 bit FNV_prime = 374144419156711147060143317175368453031918731002211

    const std::size_t fnv_offset_bias = 2166136261;
    // 64 bit offset_basis = 14695981039346656037
    // 128 bit offset_basis = 275519064689413815358837431229664493455
    // 256 bit offset_basis = 100029257958052580907070968620625704837092796014241193945225284501741471925557

    typedef basic_fnv_1<fnv_prime, fnv_offset_bias> fnv_1;
    typedef basic_fnv_1a<fnv_prime, fnv_offset_bias> fnv_1a;

}
