#include <iostream>
#include "Hacker.h"
using namespace std;


Hacker::Hacker()
{
    name = "";
    floor = 0;
}
Hacker::Hacker(string n, int f)
{
    name = n;
    floor = f;
}

// setters
void Hacker::setName(string n)
{
    name = n;
}
void Hacker::setFloor(int f)
{
    floor = f;
}

// getters
string Hacker::getName()
{
    return name;
}
int Hacker::getFloor()
{
    return floor;
}