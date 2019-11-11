#ifndef POLY_H
#define POLY_H
#include <iostream>
#include <array>
using namespace std;
// ---------------------------------------------------------------------------
//poly.h
//Class for polynomials, uses int array for storage
//Author: Sonlam Nguyen
// ---------------------------------------------------------------------------
//Poly class : a container that stores polynomial functions inside of an 
//      int array
// -Exponent is represented by element of array and coefficient is represented
//by the int at the corresponding element of exponent. Array is a dynamic 
//array so any finite non negative exponent is allowed
// -Allows for addition, subtraction, multiplication of two polys
// -Array length is part of class and corresponds to the largest exponent of
//poly. Does not need to be passed
// Assumptions and implementation:
// -Poly is defaulted to 0x^0 which is 0 and had array length of size 1
// -User must input values greater than -1, and must enter -1 to 
//terminate the program.
// -When using an operator such as +/-/* with a poly and a primitive
//it will simply attach it at the end.
// -Two polys are equal when the entire array is compared and checked for
//equality on a primitive int level
//
// ---------------------------------------------------------------------------
class Poly
{

    friend ostream& operator<<(ostream&, const Poly&);
    friend istream& operator >> (istream&, Poly&);

public:
//----------------------------------------------------------------------------
    Poly();
    Poly(int);
    Poly(int, int);
    Poly(const Poly&);
    ~Poly();
    //operator overloads
    Poly operator+(const Poly&);
    Poly operator-(const Poly&);
    Poly operator*(const Poly&);
    Poly operator=(const Poly&);
    Poly operator+=(const Poly&);
    Poly operator-=(const Poly&);
    Poly operator*=(const Poly&);
    bool operator==(const Poly&);
    bool operator!=(const Poly&);   
    void setCoeff(int, int); //setter, allocates new memory for array
    void copy(const Poly&); //function to copy over contents of array
    int getCoeff(int); //getter for coeff, returns 0 if not found
    void makeNewArray(int, int); //function to allocate new memory for array
private:
    int inputInt1 = 0; //ints to store numbers for user input
    int inputInt2 = 0;
    int *polyArray; //pointer to chunk of memory for array
    int arrayLength = 0; //length of array will be highest exponent
};
#endif

