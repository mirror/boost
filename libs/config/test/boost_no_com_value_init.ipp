//  (C) Copyright Niels Dekker 2010. 
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for most recent version.

//  MACRO:         BOOST_NO_COMPLETE_VALUE_INITIALIZATION
//  TITLE:         No complete value-initialization
//  DESCRIPTION:   The C++ compiler does not to have implemented value-initialization completely.
//  See also boost/libs/utility/value_init.htm#compiler_issues

#include <cstdlib>
#include <iostream>

namespace boost_no_complete_value_initialization
{
  enum enum_type { negative_number = -1, magic_number = 42 };

  // A POD struct.
  struct pod_struct
  {
    enum_type e;
    char c;  
    unsigned char uc;  
    short s;
    int i;
    unsigned u;
    long l;
    float f;  
    double d;  
    void* p;
  };

  bool is_zero_initialized(const pod_struct& arg)
  {
    return
      arg.e == 0 &&
      arg.c == 0 &&
      arg.uc == 0 &&
      arg.s == 0 &&
      arg.i == 0 &&
      arg.u == 0 &&
      arg.l == 0 &&
      arg.f == 0 &&
      arg.d == 0 &&
      arg.p == 0;
  }

  struct derived_pod_struct: pod_struct
  {
    int derived_data;
  };

  bool is_zero_initialized(const derived_pod_struct& arg)
  {
    const pod_struct& base_subobject = arg; 
    return arg.derived_data == 0 && is_zero_initialized(base_subobject);
  }

  struct empty_struct
  {
  };

  struct derived_struct: empty_struct
  {
    int data;
  };

  bool is_zero_initialized(const derived_struct& arg)
  {
    return arg.data == 0;
  }

  struct int_struct
  {
    int data;
  };

  struct derived_int_struct: int_struct
  {
  };

  bool is_zero_initialized(const int_struct& arg)
  {
    return arg.data == 0;
  }

  union pod_struct_and_int_union
  {
    pod_struct first;
    int second;
  };

  bool is_zero_initialized(const pod_struct_and_int_union& arg)
  {
    // When a union is zero-initialized, its first non-static 
    // named data member is zero-initialized ([dcl.init]).
    return is_zero_initialized(arg.first);
  }


  union int_and_pod_struct_union
  {
    int first;
    pod_struct second;
  };

  bool is_zero_initialized(const int_and_pod_struct_union& arg)
  {
    return arg.first == 0;
  }


  // A class that holds a "magic" enum value.
  // Note: This is not a POD class, because it has a user-defined
  // default constructor.
  class enum_holder
  {
    enum_type m_enum;
  public:

    enum_holder()
    :
    m_enum(magic_number)
    {
    }

    bool is_default() const
    {
      return m_enum == magic_number;
    }
  };


  // An aggregate struct of a non-POD class and an int.
  struct enum_holder_and_int
  {
    enum_holder e;
    int i;
  };

  bool is_value_initialized(const enum_holder_and_int& arg)
  {
    return arg.e.is_default() && arg.i == 0;
  }


  // An class that has a private and a protected int data member.
  class private_and_protected_int
  {
  private:
    int private_int;
  protected:
    int protected_int;
  public:
    bool is_value_initialized() const
    {
      return private_int == 0 && protected_int == 0;
    }
  };


  class user_defined_destructor_holder
  {
  public:
    int i;
    ~user_defined_destructor_holder()
    {
    }
  };

  bool is_value_initialized(const user_defined_destructor_holder& arg)
  {
    return arg.i == 0;
  }


  class virtual_destructor_holder
  {
  public:
    int i;
    virtual ~virtual_destructor_holder()
    {
    }
  };

  bool is_value_initialized(const virtual_destructor_holder& arg)
  {
    return arg.i == 0;
  }


  // A class that is not a POD type.
  class non_pod_class
  {
  private:
    enum_holder m_enum_holder;

  public:
    int i;

    virtual bool is_value_initialized() const
    {
      return m_enum_holder.is_default() && i == 0;
    }

    virtual ~non_pod_class() {}
  };


  // The first argument (is_value_initializated) tells whether value initialization
  // has succeeded.
  // The second argument tells what expression was evaluated.
  bool is_true(bool is_value_initializated, const char *const expression)
  {
    if ( ! is_value_initializated )
    {
      std::cout << "Note: " << expression << " evaluated to false." << std::endl;
    }
    return is_value_initializated;
  }

#define IS_TRUE(value) is_true(value, #value)
#define IS_ZERO(value) is_true(value == 0, #value " == 0")

  // value_initializer initializes each of its data members by means
  // of an empty set of parentheses, and allows checking whether
  // each of them is indeed value-initialized, as specified by 
  // the C++ Standard ([dcl.init]).
  class value_initializer
  {
  private:
    enum_holder m_enum_holder;
    enum_holder m_enum_holder_array[2];
    enum_type m_enum;
    enum_type m_enum_array[2];
    char m_char;
    char m_char_array[2];
    unsigned char m_unsigned_char;
    unsigned char m_unsigned_char_array[2];
    short m_short;
    short m_short_array[2];
    int m_int;
    int m_int_array[2];
    unsigned m_unsigned;
    unsigned m_unsigned_array[2];
    long m_long;
    long m_long_array[2];
    float m_float;
    float m_float_array[2];
    double m_double;
    double m_double_array[2];
    void* m_ptr;
    void* m_ptr_array[2];
    int_struct m_int_struct;
    int_struct m_int_struct_array[2];
    pod_struct m_pod_struct;
    pod_struct m_pod_struct_array[2];
    derived_pod_struct m_derived_pod;
    derived_pod_struct m_derived_pod_array[2];
    derived_struct m_derived_struct;
    derived_struct m_derived_struct_array[2];
    derived_int_struct m_derived_int_struct;
    derived_int_struct m_derived_int_struct_array[2];
    enum_holder_and_int m_enum_holder_and_int;
    enum_holder_and_int m_enum_holder_and_int_array[2];
    private_and_protected_int m_private_and_protected_int;
    private_and_protected_int m_private_and_protected_int_array[2];
    user_defined_destructor_holder m_user_defined_destructor_holder;
    user_defined_destructor_holder m_user_defined_destructor_holder_array[2];
    virtual_destructor_holder m_virtual_destructor_holder;
    virtual_destructor_holder m_virtual_destructor_holder_array[2];
    non_pod_class m_non_pod;
    non_pod_class m_non_pod_array[2];
    pod_struct_and_int_union m_pod_struct_and_int_union;
    pod_struct_and_int_union m_pod_struct_and_int_union_array[2];
    int_and_pod_struct_union m_int_and_pod_struct_union;
    int_and_pod_struct_union m_int_and_pod_struct_union_array[2];

  public:
    value_initializer()
    :
    m_enum_holder(),
    m_enum_holder_array(),
    m_enum(),
    m_enum_array(),
    m_char(),
    m_char_array(),
    m_unsigned_char(),
    m_unsigned_char_array(),
    m_short(),
    m_short_array(),
    m_int(),
    m_int_array(),
    m_unsigned(),
    m_unsigned_array(),
    m_long(),
    m_long_array(),
    m_float(),
    m_float_array(),
    m_double(),
    m_double_array(),
    m_ptr(),
    m_ptr_array(),
    m_int_struct(),
    m_int_struct_array(),
    m_pod_struct(),
    m_pod_struct_array(),
    m_derived_pod(),
    m_derived_pod_array(),
    m_derived_struct(),
    m_derived_struct_array(),
    m_derived_int_struct(),
    m_derived_int_struct_array(),
    m_enum_holder_and_int(),
    m_enum_holder_and_int_array(),
    m_private_and_protected_int(),
    m_private_and_protected_int_array(),
    m_user_defined_destructor_holder(),
    m_user_defined_destructor_holder_array(),
    m_virtual_destructor_holder(),
    m_virtual_destructor_holder_array(),
    m_non_pod(),
    m_non_pod_array(),
    m_pod_struct_and_int_union(),
    m_pod_struct_and_int_union_array(),
    m_int_and_pod_struct_union(),
    m_int_and_pod_struct_union_array()
    {
    }

    // Returns the number of failures.
    unsigned check() const
    {
      const unsigned num_failures = 
        (IS_TRUE( m_enum_holder.is_default() ) ? 0 : 1) +
        (IS_TRUE( m_enum_holder_array[0].is_default() ) ? 0 : 1) +
        (IS_TRUE( m_enum_holder_array[1].is_default() ) ? 0 : 1) +
        (IS_ZERO(m_enum) ? 0 : 1) + 
        (IS_ZERO(m_enum_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_enum_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_char) ? 0 : 1) + 
        (IS_ZERO(m_char_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_char_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_unsigned_char) ? 0 : 1) + 
        (IS_ZERO(m_unsigned_char_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_unsigned_char_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_short) ? 0 : 1) + 
        (IS_ZERO(m_short_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_short_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_int) ? 0 : 1) + 
        (IS_ZERO(m_int_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_int_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_unsigned) ? 0 : 1) + 
        (IS_ZERO(m_unsigned_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_unsigned_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_long) ? 0 : 1) + 
        (IS_ZERO(m_long_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_long_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_float) ? 0 : 1) + 
        (IS_ZERO(m_float_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_float_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_double) ? 0 : 1) + 
        (IS_ZERO(m_double_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_double_array[1]) ? 0 : 1) + 
        (IS_ZERO(m_ptr) ? 0 : 1) + 
        (IS_ZERO(m_ptr_array[0]) ? 0 : 1) + 
        (IS_ZERO(m_ptr_array[1]) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_int_struct) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_int_struct_array[0]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_int_struct_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_pod_struct) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_pod_struct_array[0]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_pod_struct_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_pod) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_pod_array[0]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_pod_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_struct) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_struct_array[0]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_struct_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_int_struct) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_int_struct_array[0]) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_derived_int_struct_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_enum_holder_and_int) ) ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_enum_holder_and_int_array[0]) )  ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_enum_holder_and_int_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( m_private_and_protected_int.is_value_initialized() ) ? 0 : 1) + 
        (IS_TRUE( m_private_and_protected_int_array[0].is_value_initialized() ) ? 0 : 1 ) +
        (IS_TRUE( m_private_and_protected_int_array[1].is_value_initialized() ) ? 0 : 1 );
        (IS_TRUE( is_value_initialized(m_user_defined_destructor_holder) ) ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_user_defined_destructor_holder_array[0]) )  ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_user_defined_destructor_holder_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_virtual_destructor_holder) ) ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_virtual_destructor_holder_array[0]) )  ? 0 : 1) + 
        (IS_TRUE( is_value_initialized(m_virtual_destructor_holder_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( m_non_pod.is_value_initialized() ) ? 0 : 1) + 
        (IS_TRUE( m_non_pod_array[0].is_value_initialized() ) ? 0 : 1 ) +
        (IS_TRUE( m_non_pod_array[1].is_value_initialized() ) ? 0 : 1 ) +
        (IS_TRUE( is_zero_initialized(m_pod_struct_and_int_union) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_pod_struct_and_int_union_array[0]) ) ? 0 : 1 ) +
        (IS_TRUE( is_zero_initialized(m_pod_struct_and_int_union_array[1]) ) ? 0 : 1 ) +
        (IS_TRUE( is_zero_initialized(m_int_and_pod_struct_union) ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_int_and_pod_struct_union_array[0]) ) ? 0 : 1 ) +
        (IS_TRUE( is_zero_initialized(m_int_and_pod_struct_union_array[1]) ) ? 0 : 1 );
      return num_failures;
    }
  };


  int test()
  {
    // Check both value-initialization on the stack and on the heap:
    const unsigned num_failures_on_stack = value_initializer().check();
    const value_initializer* const ptr = new value_initializer();
    const unsigned num_failures_on_heap = ptr->check();
    delete ptr;
    if ( num_failures_on_stack > 0 || num_failures_on_heap > 0 )
    {
      std::cout << "Number of initialization failures on the stack: " << num_failures_on_stack
        << "\nNumber of initialization failures on the heap: " << num_failures_on_heap
        << "\nDetected by boost_no_complete_value_initialization::test() revision 5."
        << std::endl;
    }
    return static_cast<int>(num_failures_on_stack + num_failures_on_heap);
  }

}  // End of namespace.
