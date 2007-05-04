#ifndef BOOST_INTRUSIVE_TEST_TEST_TEMPLATES_HPP
#define BOOST_INTRUSIVE_TEST_TEST_TEMPLATES_HPP

#include <vector>

namespace boost {
namespace intrusive {
namespace test {

template<class Container>
void test_shift()
{
   typedef typename ValueTraits::value_type testvalue_t;
   boost::test_tools::output_test_stream test_seq;
   Container test_cont;
   const int NumElem = 6;

   std::vector<typename Container::value_type> values(NumElem);
   for(int i = 0; i < NumElem; ++i){
      values[i] = i+1;
   }

   const int num_values = (int)values.size();
   std::vector<int> expected_values(num_values);

   //Shift forward all possible positions 3 times
   for(int i = 0; i < num_values*3; ++i){
      test_cont.assign(values.begin(), values.end());
      test_cont.shift_forward(i);
      for(int j = 0; j < num_values; ++j){
         expected_values[(j + num_values - i%num_values) % num_values] = (j + 1);
      }
      std::copy (test_cont.begin(), test_cont.end(),
                  std::ostream_iterator<testvalue_t> (test_seq));
      std::stringstream stream;
      std::copy (expected_values.begin(), expected_values.end(),
                  std::ostream_iterator<testvalue_t> (stream));
      stream << std::ends;
      BOOST_CHECK (test_seq.is_equal (stream.str().c_str()));
      test_cont.clear();
   }

   //Shift backwards all possible positions
   for(int i = 0; i < num_values*2; ++i){
      test_cont.assign(values.begin(), values.end());
      test_cont.shift_backwards(i);
      for(int j = 0; j < num_values; ++j){
         expected_values[(j + i) % num_values] = (j + 1);
      }
      std::copy (test_cont.begin(), test_cont.end(),
                  std::ostream_iterator<testvalue_t> (test_seq));
      std::stringstream stream;
      std::copy (expected_values.begin(), expected_values.end(),
                  std::ostream_iterator<testvalue_t> (stream));
      stream << std::ends;
      BOOST_CHECK (test_seq.is_equal (stream.str().c_str()));
      test_cont.clear();
   }
}  

}  //namespace test {
}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_TEST_TEST_TEMPLATES_HPP
