//  Copyright (C) 2001
//  Housemarque, Inc.
//  http://www.housemarque.com
//  
//  Permission to copy, use, modify, sell and distribute this software is
//  granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

#include <boost/preprocessor.hpp>

// ***

struct Container
{
#define BOOST_PREPROCESSOR_DEF(CV)\
  CV int& operator[](int i) CV;

  BOOST_PREPROCESSOR_DEF(BOOST_PREPROCESSOR_EMPTY())
  BOOST_PREPROCESSOR_DEF(const)
  BOOST_PREPROCESSOR_DEF(volatile)
  BOOST_PREPROCESSOR_DEF(const volatile)

#undef BOOST_PREPROCESSOR_DEF
};

// ***

int test_logic_1[0+(BOOST_PREPROCESSOR_NOT(0) == 1)];
int test_logic_2[0+(BOOST_PREPROCESSOR_NOT(1) == 0)];

int test_logic_3[0+(BOOST_PREPROCESSOR_AND(0,0) == 0)];
int test_logic_4[0+(BOOST_PREPROCESSOR_AND(0,1) == 0)];
int test_logic_5[0+(BOOST_PREPROCESSOR_AND(1,0) == 0)];
int test_logic_6[0+(BOOST_PREPROCESSOR_AND(1,1) == 1)];

int test_logic_7[0+(BOOST_PREPROCESSOR_OR(0,0) == 0)];
int test_logic_8[0+(BOOST_PREPROCESSOR_OR(0,1) == 1)];
int test_logic_9[0+(BOOST_PREPROCESSOR_OR(1,0) == 1)];
int test_logic_a[0+(BOOST_PREPROCESSOR_OR(1,1) == 1)];

int test_logic_b[0+(BOOST_PREPROCESSOR_XOR(0,0) == 0)];
int test_logic_c[0+(BOOST_PREPROCESSOR_XOR(0,1) == 1)];
int test_logic_d[0+(BOOST_PREPROCESSOR_XOR(1,0) == 1)];
int test_logic_e[0+(BOOST_PREPROCESSOR_XOR(1,1) == 0)];

// ***

static int if_test[
  0+(BOOST_PREPROCESSOR_IF(BOOST_PREPROCESSOR_INC(0),true,false) &&
  BOOST_PREPROCESSOR_IF(BOOST_PREPROCESSOR_DEC(1),false,true))];

// ***

static int cat_test[
  0+(BOOST_PREPROCESSOR_CAT(BOOST_PREPROCESSOR_IF(1,tru,fals), e))];

// ***

static const char stringize_test[4] = BOOST_PREPROCESSOR_STRINGIZE(__LINE__);

// ***

//  RATIONALE:
//  - All forms of ENUM_PARAMS must be tested with 0 and n, where n is
//  sufficiently large to exceed imaginable usage like. 50 should be
//  suffient in this case. 

#ifndef ENUM_PARAMS_TEST_MAX
#define ENUM_PARAMS_TEST_MAX 50
#endif

#define CONSTANT(I,A) const A##I = I;
BOOST_PREPROCESSOR_REPEAT(ENUM_PARAMS_TEST_MAX, CONSTANT, int default_param_)
#undef CONSTANT

#define TEST_ENUM_PARAMS(N)\
  void BOOST_PREPROCESSOR_CAT(test_enum_params,N)(\
    BOOST_PREPROCESSOR_ENUM_PARAMS(N, double x));\
  void BOOST_PREPROCESSOR_CAT(test_enum_params_with_a_default,N)(\
    BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT(N, double x, 0));\
  void BOOST_PREPROCESSOR_CAT(test_enum_params_with_defaults,N)(\
    BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_DEFAULTS(N, double x, default_param_));

TEST_ENUM_PARAMS(0)
TEST_ENUM_PARAMS(ENUM_PARAMS_TEST_MAX)

#undef TEST_ENUM_PARAMS

// ***

#ifndef IS_FUNCTION_HELPER_TEST_MAX
#define IS_FUNCTION_HELPER_TEST_MAX 40
#endif

typedef char yes_type;

#define IS_FUNCTION_HELPER(I,A)\
  template\
  <BOOST_PREPROCESSOR_ENUM_PARAMS(BOOST_PREPROCESSOR_INC(I),class P)>\
  yes_type is_function_helper(\
    P0 (*)(BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS(BOOST_PREPROCESSOR_INC(I),P)));

BOOST_PREPROCESSOR_REPEAT_2ND(BOOST_PREPROCESSOR_INC(IS_FUNCTION_HELPER_TEST_MAX),IS_FUNCTION_HELPER,A)

#undef IS_FUNCTION_HELPER

// ***

int test_arithmetic_1[0+(BOOST_PREPROCESSOR_ADD(5,10)==15)];
int test_arithmetic_2[0+(BOOST_PREPROCESSOR_ADD(0,10)==10)];
int test_arithmetic_3[0+(BOOST_PREPROCESSOR_ADD(1,BOOST_PREPROCESSOR_LIMIT_MAG)==BOOST_PREPROCESSOR_LIMIT_MAG)];
int test_arithmetic_4[0+(BOOST_PREPROCESSOR_SUB(11,0)==11)];
int test_arithmetic_5[0+(BOOST_PREPROCESSOR_SUB(12,1)==11)];
int test_arithmetic_6[0+(BOOST_PREPROCESSOR_SUB(3,4)==0)];

int test_arithmetic_7[0+(BOOST_PREPROCESSOR_MUL(0,1)==0)];
int test_arithmetic_8[0+(BOOST_PREPROCESSOR_MUL(1,0)==0)];
int test_arithmetic_9[0+(BOOST_PREPROCESSOR_MUL(1,1)==1)];
int test_arithmetic_10[0+(BOOST_PREPROCESSOR_MUL(11,5)==55)];

int test_arithmetic_11[0+(BOOST_PREPROCESSOR_DIV(2,1)==2)];
int test_arithmetic_12[0+(BOOST_PREPROCESSOR_DIV(0,5)==0)];
int test_arithmetic_13[0+(BOOST_PREPROCESSOR_DIV(11,3)==3)];
int test_arithmetic_14[0+(BOOST_PREPROCESSOR_DIV(67,30)==2)];

int test_arithmetic_15[0+(BOOST_PREPROCESSOR_EQUAL(1,0)==0)];
int test_arithmetic_16[0+(BOOST_PREPROCESSOR_EQUAL(100,100)==1)];
int test_arithmetic_17[0+(BOOST_PREPROCESSOR_NOT_EQUAL(34,45)==1)];
int test_arithmetic_18[0+(BOOST_PREPROCESSOR_NOT_EQUAL(67,67)==0)];
int test_arithmetic_19[0+(BOOST_PREPROCESSOR_LESS_EQUAL(6,7)==1)];
int test_arithmetic_20[0+(BOOST_PREPROCESSOR_LESS_EQUAL(87,12)==0)];
int test_arithmetic_21[0+(BOOST_PREPROCESSOR_LESS_EQUAL(58,58)==1)];
int test_arithmetic_22[0+(BOOST_PREPROCESSOR_GREATER_EQUAL(6,7)==0)];
int test_arithmetic_23[0+(BOOST_PREPROCESSOR_GREATER_EQUAL(10,10)==1)];
int test_arithmetic_24[0+(BOOST_PREPROCESSOR_GREATER_EQUAL(87,12)==1)];
int test_arithmetic_25[0+(BOOST_PREPROCESSOR_LESS(2,1)==0)];
int test_arithmetic_26[0+(BOOST_PREPROCESSOR_LESS(1,1)==0)];
int test_arithmetic_27[0+(BOOST_PREPROCESSOR_LESS(1,2)==1)];
int test_arithmetic_28[0+(BOOST_PREPROCESSOR_GREATER(2,1)==1)];
int test_arithmetic_29[0+(BOOST_PREPROCESSOR_GREATER(1,1)==0)];
int test_arithmetic_30[0+(BOOST_PREPROCESSOR_GREATER(1,2)==0)];

int test_arithmetic_31[0+(BOOST_PREPROCESSOR_MIN(1,0)==0)];
int test_arithmetic_32[0+(BOOST_PREPROCESSOR_MIN(1,2)==1)];
int test_arithmetic_33[0+(BOOST_PREPROCESSOR_MAX(3,2)==3)];
int test_arithmetic_34[0+(BOOST_PREPROCESSOR_MAX(4,5)==5)];

// ***

int
  main()
{ return 0;
}
