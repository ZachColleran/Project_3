#include <iostream>
using namespace std;

#ifndef HACKER_H
#define HACKER_H

class Hacker
{
    public:
        // constructors
        Hacker();
        Hacker(string n, int f);

        // setters
        void setName(string n);
        void setFloor(int f);

        // getters
        string getName();
        int getFloor();

    private:

        string name;
        int floor;
};

#endif