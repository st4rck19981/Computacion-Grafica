/*
g++ main.cpp escaner.cpp -o output `pkg-config --cflags --libs opencv`
./output
*/

#include <iostream>
#include "escaner.h"
using namespace std;

int main(int argc, char *argv[])
{
    escaner scan;
    scan.ejecutar();

    return 0;
}
