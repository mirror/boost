/*=============================================================================
    Wave: A Standard compliant C++ preprocessor library

    http://spirit.sourceforge.net/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(CPP_EXPRESSION_VALUE_HPP_452FE66D_8754_4107_AF1E_E42255A0C18A_INCLUDED)
#define CPP_EXPRESSION_VALUE_HPP_452FE66D_8754_4107_AF1E_E42255A0C18A_INCLUDED

#if defined (BOOST_SPIRIT_DEBUG)
#include <iostream>
#endif // defined(BOOST_SPIRIT_DEBUG)

#include <boost/variant.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {
namespace grammars {
namespace closures {

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of the variant visitors needed for type correct value access
//
///////////////////////////////////////////////////////////////////////////////
struct long_visitor : public boost::static_visitor<long>
{
    template <typename T>
    long operator() (T val)
    {
        return T(val);
    }
};

struct ulong_visitor : public boost::static_visitor<unsigned long>
{
    template <typename T>
    unsigned long operator() (T val)
    {
        return T(val);
    }
};

struct bool_visitor : public boost::static_visitor<bool>
{
    template <typename T>
    bool operator() (T val)
    {
        return T(val);
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of the variant visitors needed for unary and binary operations
//  on the expression values.
//
///////////////////////////////////////////////////////////////////////////////
struct plus_visitor : public boost::static_visitor<>
{
    template <typename T1, typename T2>
    void operator()(unsigned long &lhs, T2 rhs) const
    {
        return lhs + rhs;
    }
};

struct minus_visitor : public boost::static_visitor<long>
{
    template <typename T1, typename T2>
    long operator()(T1 lhs, T2 rhs) const
    {
        return lhs - rhs;
    }
};

struct multiply_visitor : public boost::static_visitor<long>
{
    template <typename T1, typename T2>
    long operator()(T1 &lhs, T2 rhs) const
    {
        lhs *= rhs;
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  The closure_value class represents the closure type, which is used for the 
//  expression grammar. 
//
//      This class was introduced to allow the expression grammar to respect 
//      the numeric type of a numeric literal or expression result.
//
///////////////////////////////////////////////////////////////////////////////
class closure_value 
{
public:

    closure_value() 
    : value(0L), valid(true) 
    {}
    explicit closure_value(long i, bool valid_ = true) 
    : value(i), valid(valid_) 
    {}
    explicit closure_value(unsigned long ui, bool valid_ = true) 
    : value(ui), valid(valid_) 
    {}
    explicit closure_value(bool b, bool valid_ = true) 
    : value(b), valid(valid_) 
    {}

    bool is_valid() const { return valid; }
    
// implicit conversion
    operator long() const 
    {
        return as_long();
    }
    operator unsigned long() const 
    {
        return as_ulong();
    }
    operator bool() const 
    {
        return as_bool();
    }

// assignment    
    closure_value &operator= (long rhs)
    {
        value = rhs;
        valid = true;
        return *this;
    }
    closure_value &operator= (unsigned long rhs)
    {
        value = rhs;
        valid = true;
        return *this;
    }
    closure_value &operator= (bool rhs)
    {
        value = rhs;
        valid = true;
        return *this;
    }

// arithmetics
    closure_value &operator+= (closure_value const &rhs)
    {
        if (valid = valid && rhs.valid)
            value = boost::apply_visitor(plus_visitor(), value, rhs.value);
        return *this;
    }
    closure_value &operator-= (closure_value const &rhs)
    {
        if (valid = valid && rhs.valid)
            value = boost::apply_visitor(minus_visitor(), value, rhs.value);
        return *this;
    }
    closure_value &operator*= (closure_value const &rhs)
    {
        if (valid = valid && rhs.valid)
            value = boost::apply_visitor(multiply_visitor(), value, rhs.value);
        return *this;
    }
        switch (type) {
        case is_int:    
            switch(rhs.type) {
            case is_bool:   value.i *= long(rhs); break;
            case is_int:    value.i *= rhs.value.i; break;
            case is_uint:   value.ui *= rhs.value.ui; type = is_uint; break;
            }
            break;
            
        case is_uint:   value.ui *= unsigned long(rhs); break;
        case is_bool:
            switch (rhs.type) {
            case is_int:
                value.i = (value.b ? 1 : 0) * rhs.value.i; 
                type = is_int; 
                break;
                
            case is_uint:
                value.ui = (value.b ? 1 : 0) * rhs.value.ui; 
                type = is_uint; 
                break;
                
            case is_bool:
                value.b = 0 != ((value.b ? 1 : 0) * (rhs.value.b ? 1 : 0));
                break;
            }
        }
        valid = valid && rhs.valid;
        return *this;
    }
    closure_value &operator/= (closure_value const &rhs)
    {
        switch (type) {
        case is_int:    
            switch(rhs.type) {
            case is_bool:   
            case is_int:
                if (valid && long(rhs) != 0)
                    value.i /= long(rhs); 
                else
                    valid = false;      // division by zero
                break;
                
            case is_uint:
                if (valid && rhs.value.ui != 0) {
                    value.ui /= rhs.value.ui; 
                    type = is_uint; 
                }
                else {
                    valid = false;      // division by zero
                }
                break;
            }
            break;
            
        case is_uint: 
            if (valid && unsigned long(rhs) != 0) 
                value.ui /= unsigned long(rhs); 
            else
                valid = false;      // division by zero
            break;

        case is_bool:  
            if (valid && bool(rhs)) {
                switch(rhs.type) {
                case is_int:
                    value.i = (value.b ? 1 : 0) / rhs.value.i;
                    type = is_int;
                    break;
                    
                case is_uint:
                    value.i = (value.b ? 1 : 0) / rhs.value.ui;
                    type = is_int;
                    break;
                    
                case is_bool:
                    break;
                }                    
            }
            else {
                valid = false;      // division by zero
            }
        }
        return *this;
    }

    friend closure_value 
    operator- (closure_value const &rhs)
    {
        switch (rhs.type) {
        case is_int:    return closure_value(-long(rhs), rhs.valid);
        case is_bool:   return closure_value(!bool(rhs), rhs.valid); 
        case is_uint:   break;
        }
        return closure_value(-(int)unsigned long(rhs), rhs.valid);
    }
    friend closure_value 
    operator! (closure_value const &rhs)
    {
        switch (rhs.type) {
        case is_int:    return closure_value(!long(rhs), rhs.valid);
        case is_bool:   return closure_value(!bool(rhs), rhs.valid); 
        case is_uint:   break;
        }
        return closure_value(!unsigned long(rhs), rhs.valid);
    }
    
// comparison
    friend closure_value 
    operator== (closure_value const &lhs, closure_value const &rhs)
    {
        bool cmp = false;
        switch (lhs.type) {
        case is_int:
            switch(rhs.type) {
            case is_bool:   cmp = bool(lhs) == rhs.value.b; break;
            case is_int:    cmp = lhs.value.i == rhs.value.i; break;
            case is_uint:   cmp = lhs.value.ui == rhs.value.ui; break;
            }
            break;
            
        case is_uint:   cmp = lhs.value.ui == unsigned long(rhs); break;
        case is_bool:   cmp = lhs.value.b == bool(rhs); break;
        }
        return closure_value(cmp, lhs.valid && rhs.valid);
    }
    friend closure_value 
    operator!= (closure_value const &lhs, closure_value const &rhs)
    {
        return closure_value(!bool(lhs == rhs), lhs.valid && rhs.valid);
    }
    friend closure_value 
    operator> (closure_value const &lhs, closure_value const &rhs)
    {
        bool cmp = false;
        switch (lhs.type) {
        case is_int:
            switch(rhs.type) {
            case is_bool:   cmp = lhs.value.i > long(rhs); break;
            case is_int:    cmp = lhs.value.i > rhs.value.i; break;
            case is_uint:   cmp = lhs.value.ui > rhs.value.ui; break;
            }
            break;
            
        case is_uint:   cmp = lhs.value.ui > unsigned long(rhs); break;
        case is_bool:   cmp = lhs.value.b > bool(rhs); break;
        }
        return closure_value(cmp, lhs.valid && rhs.valid);
    }
    friend closure_value 
    operator< (closure_value const &lhs, closure_value const &rhs)
    {
        bool cmp = false;
        switch (lhs.type) {
        case is_int:    cmp = long(lhs) < long(rhs); break;
            switch(rhs.type) {
            case is_bool:   cmp = lhs.value.i < long(rhs); break;
            case is_int:    cmp = lhs.value.i < rhs.value.i; break;
            case is_uint:   cmp = lhs.value.ui < rhs.value.ui; break;
            }
            break;
            
        case is_uint:   cmp = lhs.value.ui < unsigned long(rhs); break;
        case is_bool:   cmp = bool(lhs) < bool(rhs); break;
        }
        return closure_value(cmp, lhs.valid && rhs.valid);
    }
    friend closure_value 
    operator<= (closure_value const &lhs, closure_value const &rhs)
    {
        return closure_value(!bool(lhs > rhs), lhs.valid && rhs.valid);
    }
    friend closure_value 
    operator>= (closure_value const &lhs, closure_value const &rhs)
    {
        return closure_value(!bool(lhs < rhs), lhs.valid && rhs.valid);
    }

    closure_value &
    operator<<= (closure_value const &rhs)
    {
        switch (type) {
        case is_bool:
        case is_int:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                long shift_by = long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.i <<= shift_by; 
                }
                break;
                
            case is_uint:
                {
                unsigned long shift_by = unsigned long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui <<= shift_by; 
                
                // Note: The usual arithmetic conversions are not performed on 
                //       bit shift operations.
                }
                break;
            }
            break;

        case is_uint:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                long shift_by = long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.ui <<= shift_by; 
                }
                break;
                
            case is_uint:
                {
                unsigned long shift_by = unsigned long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui <<= shift_by; 
                }
                break;
            }
        }
        valid = valid && rhs.valid;
        return *this;
    }

    closure_value &
    operator>>= (closure_value const &rhs)
    {
        switch (type) {
        case is_bool:
        case is_int:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                long shift_by = long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.i >>= shift_by; 
                }
                break;
                
            case is_uint:
                {
                unsigned long shift_by = unsigned long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui >>= shift_by; 
                
                // Note: The usual arithmetic conversions are not performed on 
                //       bit shift operations.
                }
                break;
            }
            break;
            
        case is_uint:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                long shift_by = long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.ui >>= shift_by; 
                }
                break;
                
            case is_uint:
                {
                unsigned long shift_by = unsigned long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui >>= shift_by; 
                }
                break;
            }
            break;
        }
        valid = valid && rhs.valid;
        return *this;
    }

    friend closure_value 
    operator|| (closure_value const &lhs, closure_value const &rhs)
    {
        bool result = bool(lhs) || bool(rhs);
        return closure_value(result, lhs.valid && rhs.valid);
    }
    
    friend closure_value 
    operator&& (closure_value const &lhs, closure_value const &rhs)
    {
        bool result = bool(lhs) && bool(rhs);
        return closure_value(result, lhs.valid && rhs.valid);
    }

    // handle the ?: operator
    closure_value &
    handle_questionmark(closure_value const &cond, closure_value const &val2)
    {
        switch (type) {
        case is_int:
            switch (val2.type) {
            case is_bool: value.b = bool(cond) ? value.b : bool(val2); break;
            case is_int:  value.i = bool(cond) ? value.i : long(val2); break;
            case is_uint: 
                value.ui = bool(cond) ? value.ui : unsigned long(val2); 
                type = is_uint;   // changing type!
                break;
            }
            break;
            
        case is_uint:   value.ui = bool(cond) ? value.ui : unsigned long(val2); break;
        case is_bool:   value.b = bool(cond) ? value.b : bool(val2); break;
        }
        valid = bool(cond) ? valid : val2.valid;
        return *this;
    }
    
#if defined (BOOST_SPIRIT_DEBUG)
    friend std::ostream&
    operator<< (std::ostream &o, closure_value const &val)
    {
        switch (val.type) {
        case is_int:    o << "int(" << long(val) << ")"; break;
        case is_uint:   o << "unsigned int(" << unsigned long(val) << ")"; break;
        case is_bool:   o << "bool(" << bool(val) << ")"; break;
        }
        return o;
    }
#endif // defined(BOOST_SPIRIT_DEBUG)

protected:
    long as_long() const
    {
        return boost::apply_visitor(long_visitor(), value);
    }
    unsigned long as_ulong() const
    {
        return boost::apply_visitor(ulong_visitor(), value);
    }
    bool as_bool() const
    {
        return boost::apply_visitor(bool_visitor(), value);
    }

private:
    boost::variant<long, unsigned long, bool> value;
    bool valid;
};

///////////////////////////////////////////////////////////////////////////////
}   // namespace closures
}   // namespace grammars
}   // namespace wave
}   // namespace boost

#endif // !defined(CPP_EXPRESSION_VALUE_HPP_452FE66D_8754_4107_AF1E_E42255A0C18A_INCLUDED)
