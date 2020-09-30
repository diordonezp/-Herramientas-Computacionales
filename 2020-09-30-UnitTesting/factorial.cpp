#include "factorial.h"

// function definition or implementation
// n! = n*(n-1)*(n-2)*...*2*1
// n! = n*(n-1)!
long factorial(long n)
{
    if (n < 0) {
        std::cerr << "ERROR: Cannot compute factorial for negative numbers. Received n:"
                  << n << "\n";
        return 0; 
    }
    return n <= 1 ? 1 : n*factorial(n-1);
}
