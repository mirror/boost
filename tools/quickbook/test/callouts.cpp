//[ example1

/*`
 Now we can define a function that simulates an ordinary
 six-sided die.
*/
int roll_die() {
  boost::uniform_int<> dist(1, 6); /*< create a uniform_int distribution >*/
}

//]

//[ example2

int roll_die() {
  /*<< [important test] >>*/
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
}

//]

//[ example3

int roll_die() {
  /*<< [important test]
  >>*/
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
}

//]
