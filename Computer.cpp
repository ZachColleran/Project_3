#include <iostream>
#include "Computer.h"
using namespace std;

Computer::Computer() // default
{
    partName = "";
    partQuantity = 0;
}
Computer::Computer(string n, int q) // parametrized
{
    partName = n;
    partQuantity = q;
}
// setters
void Computer::setPartName(string n)
{
    partName = n;
}
void Computer::setPartQuantity(int q)
{
    partQuantity = q;
}

// getters
string Computer::getPartName() // may not need
{
    return partName;
}

int Computer::getPartQuantity()
{
    return partQuantity;
}