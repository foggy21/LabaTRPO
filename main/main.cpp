#include <iostream>
#include "Integer.h"
using namespace arbitary_precision_arithmetic;

int main()
{
    Integer *a = new Integer();
    std::cout << sizeof(*a);
}
