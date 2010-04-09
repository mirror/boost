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

  // A class that holds a "magic" enum value.
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
      std::cout
        << "Information: " << expression << " evaluated to false.\n" 
        << std::endl;
    }
    return is_value_initializated;
  }

#define IS_TRUE(value) is_true(value, #value)
#define IS_ZERO(value) is_true(value == 0, #value " == 0")

  // The default constructor of this class initializes each of its 
  // data members by means of an empty set of parentheses, and checks
  // whether each of them is value-initialized.
  class value_initializer
  {
  private:
    enum_holder m_enum_holder;
    enum_type m_enum;
    char m_char;  
    unsigned char m_unsigned_char;  
    short m_short;
    int m_int;
    unsigned m_unsigned;
    long m_long;
    float m_float;  
    double m_double;  
    void* m_ptr;
    pod_struct m_pod;
    pod_struct m_pod_array[2];
    non_pod_class m_non_pod;
    non_pod_class m_non_pod_array[2];

  public:
    value_initializer()
    :
    m_enum_holder(),
    m_enum(),
    m_char(),
    m_unsigned_char(),
    m_short(),
    m_int(),
    m_unsigned(),
    m_long(),
    m_float(),
    m_double(),
    m_ptr(),
    m_pod(),  
    m_pod_array(),
    m_non_pod(),
    m_non_pod_array()
    {
    }

    // Returns the number of failures.
    unsigned check() const
    {
      return 
        (IS_TRUE( m_enum_holder.is_default() ) ? 0 : 1) +
        (IS_ZERO(m_enum) ? 0 : 1) + 
        (IS_ZERO(m_char) ? 0 : 1) + 
        (IS_ZERO(m_unsigned_char) ? 0 : 1) + 
        (IS_ZERO(m_short) ? 0 : 1) + 
        (IS_ZERO(m_int) ? 0 : 1) + 
        (IS_ZERO(m_unsigned) ? 0 : 1) + 
        (IS_ZERO(m_long) ? 0 : 1) + 
        (IS_ZERO(m_float) ? 0 : 1) + 
        (IS_ZERO(m_double) ? 0 : 1) + 
        (IS_ZERO(m_ptr) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_pod) ) ? 0 : 1) + 
        (IS_TRUE( m_non_pod.is_value_initialized() ) ? 0 : 1) + 
        (IS_TRUE( is_zero_initialized(m_pod_array[0]) 
        && is_zero_initialized(m_pod_array[1]) ) ? 0 : 1) + 
        (IS_TRUE( m_non_pod_array[0].is_value_initialized() 
        && m_non_pod_array[1].is_value_initialized() ) ? 0 : 1);

    }
  };

  int test()
  {
    // Check both value-initialization on the stack and on the heap:
    const unsigned num_failures_on_stack = value_initializer().check();
    const value_initializer* const ptr = new value_initializer();
    const unsigned num_failures_on_heap = ptr->check();
    delete ptr;
    return static_cast<int>(num_failures_on_stack + num_failures_on_heap);
  }

}  // End of namespace.

