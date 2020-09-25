#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
  // declare variables
  const int N = 10;
  double * array=nullptr;
  //reserve memory
  array = new double [N] {0.0};
  // initialise array
  for (int ii = 0; ii < N; ++ii) {
    array[ii] = 2*(++ii); // != 2*(ii++) ? 
  }
  // print some values 
  int idx = 2;
  std::cout << array[idx] << std::endl;
  //idx = 10;
  //std::cout << array[idx] << std::endl; // compiles, but ... 

  // free memory
  delete [] array;

  return 0;
}
