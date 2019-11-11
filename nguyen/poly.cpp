#include "poly.h"
// ---------------------------------------------------------------------------
//poly.cpp
//Member function definitions for class Poly
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
// Assumptions:
// -Poly is defaulted to 0x^0 which is 0 and had array length of size 1
// -User must input values greater than -1, and must enter -1 to 
//terminate the program.
// ---------------------------------------------------------------------------

//Default Constructor
//Creates an array of size one and initializes to zero
Poly::Poly()
{
    int elementOfOne = 1;
    int beginningOfArray = 0;
    polyArray = new int[elementOfOne];
    polyArray[beginningOfArray] = 0;
    arrayLength = 0;
}

// ---------------------------------------------------------------------------
//Single Coefficient constructor
//Makes an array size one and sets the coefficient to input
Poly::Poly(int inputCoeff) {
    int elementOfOne = 1;
    int beginningOfArray = 0;
    polyArray = new int[elementOfOne];
    polyArray[beginningOfArray] = inputCoeff;
}

// ---------------------------------------------------------------------------
//The main constructor
//Will be creating array ofthe size of the input exponent, then setting 
//that coefficient
Poly::Poly(int inputCoeff, int inputExponent) {
    polyArray = new int[inputExponent+1]; //+1 because you need one extraspot
    arrayLength = inputExponent; //set length
    //initialize array
    for (int i = 0; i <= arrayLength; i++) {
        polyArray[i] = 0;
    }
    polyArray[inputExponent] = inputCoeff;
    
}

// ---------------------------------------------------------------------------
//Copy Constructor, calls upon the copy function
Poly::Poly(const Poly& inputPoly) {
    copy(inputPoly);
}

// ---------------------------------------------------------------------------
//Destructor
Poly::~Poly() {
    delete[] this->polyArray;
    polyArray = nullptr;
}

// ---------------------------------------------------------------------------
//Addition overload
//Will figure out which Poly has a higher exponent, fill out the gap of 
//variables between the two arrays, then fill in the rest by adding
//coefficients with corresponding exponents together
Poly Poly::operator+(const Poly &inputPoly) {
    Poly tempPoly;
    bool thisIsBigger = false;  //this as in this poly
    int beginningOfArray = 0;

    if (inputPoly.arrayLength < arrayLength) {
        thisIsBigger = true;
        tempPoly.polyArray = new int[arrayLength+1];
        tempPoly.arrayLength = arrayLength;
    }
    else {
        tempPoly.polyArray = new int[inputPoly.arrayLength+1];
        tempPoly.arrayLength = inputPoly.arrayLength;
    }


    if (thisIsBigger) { //fill in difference of coeffs between exponent gaps
        for (int i = arrayLength; i > inputPoly.arrayLength; i--) {
            tempPoly.polyArray[i] = polyArray[i];
        }
        //then combine like terms
        for (int i = inputPoly.arrayLength; i >= beginningOfArray; i--) {
            tempPoly.polyArray[i] = polyArray[i] + inputPoly.polyArray[i];
        }
    }
    else {
        for (int i = inputPoly.arrayLength; i > arrayLength; i--) {
            tempPoly.polyArray[i] = inputPoly.polyArray[i];
        }
        for (int i = arrayLength; i >= beginningOfArray; i--) {
            tempPoly.polyArray[i] = polyArray[i] + inputPoly.polyArray[i];
        }
    }
    return tempPoly;
}
// ---------------------------------------------------------------------------
//Subtraction overload
//Does the same thing as addition except this time for the polynomials
//You can simply distribute the negative to the right hand side polynomial
//Then combine like terms, in this case we choose to always have the
//inputPoly be the right hand side.
Poly Poly::operator-(const Poly &inputPoly) {
    Poly tempPoly;
    bool thisIsBigger = false;
    int elementOfOne = 1;
    int beginningOfArray = 0;

    //distributing the negative
    for (int i = 0; i <= inputPoly.arrayLength; i++) {
        if (inputPoly.polyArray[i] != 0) {
            inputPoly.polyArray[i] *= -1;
        }
    }
    //initializing and creating our temp poly to hold the highest exponent
    if (inputPoly.arrayLength < arrayLength) {
        thisIsBigger = true;
        tempPoly.polyArray = new int[arrayLength+1];
        tempPoly.arrayLength = arrayLength;

        for (int i = 0; i <= tempPoly.arrayLength; i++) {
            tempPoly.polyArray[i] = 0;
        }

    }
    else {
        tempPoly.polyArray = new int[inputPoly.arrayLength+1];
        tempPoly.arrayLength = inputPoly.arrayLength;

        for (int i = 0; i <= tempPoly.arrayLength; i++) {
            tempPoly.polyArray[i] = 0;
        }

    }
    //same method of the addition function
    if (thisIsBigger) {
        for (int i = arrayLength; i > inputPoly.arrayLength; i--) {
            tempPoly.polyArray[i] = polyArray[i];
        }
        for (int i = inputPoly.arrayLength; i >= beginningOfArray; i--) {
            tempPoly.polyArray[i] = polyArray[i] + inputPoly.polyArray[i];
        }
    }
    else {
        for (int i = inputPoly.arrayLength; i > arrayLength; i--) {
            tempPoly.polyArray[i] = inputPoly.polyArray[i];
        }
        for (int i = arrayLength; i >= beginningOfArray; i--) {
            tempPoly.polyArray[i] = polyArray[i] + inputPoly.polyArray[i];
        }
    }

    //return the right hand side polynomial to original to not mess with
    //the polynomial outside of this function
    for (int i = 0; i <= inputPoly.arrayLength; i++) {
        inputPoly.polyArray[i] *= -1;
    }

    return tempPoly;
}
// ---------------------------------------------------------------------------
//Multiplication overload
//Distribution method. Uses a nested loop to multiple each variable of the
//left hand side polynomial with each variable of the right hand side
// polynomial one time, then adds the exponents together and places them
//in the correct array element of the new array.
Poly Poly::operator*(const Poly &inputPoly) {
    Poly tempPoly(0, arrayLength + inputPoly.arrayLength);
    int elementOfOne = 1;
    int beginningOfArray = 0;
    for (int i = arrayLength; i >= beginningOfArray; i--) {
        for (int j = inputPoly.arrayLength; j >= beginningOfArray; j--) {
            if (inputPoly.polyArray[j] != 0 && polyArray[i] != 0) {

                if (tempPoly.polyArray[i + j] != 0) {
                    tempPoly.polyArray[i + j] += polyArray[i] 
                        * inputPoly.polyArray[j];
                }
                else {
                    tempPoly.polyArray[i + j] = polyArray[i] 
                        * inputPoly.polyArray[j];
                }
            }
        }
    }

    return tempPoly;
}
// ---------------------------------------------------------------------------
//Assignment overload
//Uses the copy function, as long as it does equal itself
Poly Poly::operator=(const Poly &inputPoly) {
    if (*this != inputPoly) {
        copy(inputPoly);
    }
    return *this;
}
// ---------------------------------------------------------------------------
//+=
//returns an addition of the two objects
Poly Poly::operator+=(const Poly &inputPoly) {
    *this = *this + inputPoly;
    return *this;
}
// ---------------------------------------------------------------------------
//-=
//returns the subtraction of the two objects
Poly Poly::operator-=(const Poly &inputPoly) {
    *this = *this - inputPoly;
    return *this;
}
// ---------------------------------------------------------------------------
//*=
//returns the subtraction of the two objects
Poly Poly::operator*=(const Poly &inputPoly) {
    *this = *this * inputPoly;
    return *this;
}
// ---------------------------------------------------------------------------
//Equality
//compares each element of both arrays, must be identical to be considered
// "equal"
bool Poly::operator==(const Poly &inputPoly) {
    if (arrayLength != inputPoly.arrayLength) {
        return false;
    }
    for (int i = 0; i <= arrayLength; i++) {
        if (polyArray[i] != inputPoly.polyArray[i]) {
            return false;
        }
    }
    return true;
}
// ---------------------------------------------------------------------------
//!=
//Returns opposite of equality
bool Poly::operator!=(const Poly &inputPoly) {
    return !(*this == inputPoly);
}
// ---------------------------------------------------------------------------
//Printer overload
// Prints out in (c)x^(e) format with c being the coeff and e being the
//exponent
ostream& operator<<(ostream &output, const Poly &inputPoly) {
    bool coeffChecker = false;
    int beginningOfArray = 0;
    int elementOfOne = 1;
    //array has to not be "Null" or a 0 to proceed with printing it
    for (int i = inputPoly.arrayLength; i >= beginningOfArray; i--) {
        if (inputPoly.polyArray[i] != 0) {
            coeffChecker = true;
        }

        if (coeffChecker) {
            if (inputPoly.polyArray[i] > 0 && i > 2) {
                output << " " << "+" << inputPoly.polyArray[i] << "x^" << i;
                coeffChecker = false; //resets the bool
            }
            else if (inputPoly.polyArray[i] < 0 && i > 2) {
                output << " " << inputPoly.polyArray[i] << "x^" << i;
                coeffChecker = false;
            }
            //sepcial case at x=1 because the format changes
            else if (i == elementOfOne) {
                output << " ";
                if (0 < inputPoly.polyArray[i]) {
                    output << "+";
                }
                output << inputPoly.polyArray[i] << "x";
                coeffChecker = false;
            }
            //sepcial case at x=0 because the format changes
            else if (i == beginningOfArray) {
                output << " ";
                if (0 < inputPoly.polyArray[i]) {
                    output << "+";
                }
                output << inputPoly.polyArray[i];
                coeffChecker = false;
            }
        }
    }
    return output;
}
// ---------------------------------------------------------------------------
// Read in overload. reads in pairs of ints and calls setCoeff to deal with 
// the pair of numbers to assign them and allocate memory properly
istream& operator >> (istream &in, Poly& inputPoly) {
    while (inputPoly.inputInt1 != -1) {
        in >> inputPoly.inputInt1 >> inputPoly.inputInt2;
        inputPoly.setCoeff(inputPoly.inputInt1, inputPoly.inputInt2);
    }
    return in;
}
// ---------------------------------------------------------------------------
//Copy function
//Copies array contents from called parameter into "this" Poly
void Poly::copy(const Poly& toCopy) {
    arrayLength = toCopy.arrayLength;
    polyArray = new int[arrayLength+1];

    for (int i = 0; i <= arrayLength; i++) {
        polyArray[i] = toCopy.polyArray[i];
    }
}
// ---------------------------------------------------------------------------
//setCoeff function
//Sets the coefficient at called exponent. Will call another function to 
//allocate more memory if needed 
void Poly::setCoeff(int inputCoeff, int inputExponent) {
    if (inputExponent >= arrayLength) {
        makeNewArray(inputCoeff, inputExponent);
    }
    if (inputExponent >= 0 && inputExponent <= arrayLength) {
        polyArray[inputExponent] = inputCoeff;
    }
}
// ---------------------------------------------------------------------------
//Getter
// simple getter for coeff, will return 0 if out of bounds or has no coeff
int Poly::getCoeff(int inputExponent) {
    if (inputExponent >= 0 && inputExponent <= arrayLength) {
        return polyArray[inputExponent];
    }
    else {
        return 0;
    }
}
// ---------------------------------------------------------------------------
//function makeNewArray
//allocates new memory when exponent wants to be added higher than current 
// size by storing contents into a temporary Poly, then copying it back over
// back to the original after new memory is allocated.
void Poly::makeNewArray(int inputCoeff, int inputExponent) {
    Poly tempPoly;
    tempPoly = *this;
    polyArray = new int[inputExponent+1];
    arrayLength = inputExponent;
    for (int i = 0; i <= arrayLength; i++) {
        polyArray[i] = 0;
    }
    //cout << tempPoly << endl;
   // polyArray[inputExponent] = inputCoeff;
    for (int i = 0; i <= tempPoly.arrayLength; i++) {
        polyArray[i] = tempPoly.polyArray[i];
    }
}
