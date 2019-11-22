#include "polynomial.h"

using namespace std;

int main() {
    Polynomial myPoly;
    cout << myPoly << endl;
    //creating, changing, and removing terms terms
    cout << "adding, removing, changing terms: " << endl;
    myPoly.changeCoefficient(1, 5);
    cout << "adding x^5: " << myPoly << endl;
    myPoly.changeCoefficient(-3, 5);
    cout << "changing x^5 to -3x^5: " << myPoly << endl;
    myPoly.changeCoefficient(7, 2);
    cout << "adding 7x^2: " << myPoly << endl;
    myPoly.changeCoefficient(-500, 2);
    cout << "changing 7^2 to -500x^2: " << myPoly << endl;
    myPoly.changeCoefficient(23, 4);
    cout << "adding 23x^4: " << myPoly << endl;
    myPoly.changeCoefficient(4, 1);
    cout << "adding 4x: " << myPoly << endl;
    myPoly.changeCoefficient(1, 1);
    cout << "changing 4x to x: " << myPoly << endl;  
    myPoly.changeCoefficient(-1, 2);
    cout << "changing -500x^2 to -x^2: " << myPoly << endl;
    myPoly.changeCoefficient(1, 5);
    cout << "changing -3x^5 to x^5: " << myPoly << endl;
    myPoly.changeCoefficient(99, 0);
    cout << "adding 99: " << myPoly << endl << endl;

    //using accessor functions
    cout << "using accessor functions: " << endl;
    cout << "highest degree: " << myPoly.degree();
    cout << "-> coefficient of power 0 term: " << myPoly.coefficient(0) << endl << endl;

    //removing terms, adding more
    cout << "more adding, removing, changing: " << endl;
    myPoly.changeCoefficient(0, 5);
    cout << "removing x^5: " << myPoly << endl;
    myPoly.changeCoefficient(-12.7, 7);
    cout << "adding -12.7x^7: " << myPoly << endl;
    myPoly.changeCoefficient(5, 0);
    cout << "changing 99 to 5: " << myPoly << endl;
    myPoly.changeCoefficient(0, 4);
    cout << "removing 23x^4: " << myPoly << endl << endl;

    //testing overloaded comparison operators 
    cout << "testing comparison operators: " << endl;
    Polynomial myPoly2;
    myPoly2.changeCoefficient(-8.9, 7);
    myPoly2.changeCoefficient(-1, 1);
    myPoly2.changeCoefficient(132, 12);
    Polynomial myPolyIdentical;
    myPolyIdentical.changeCoefficient(-12.7, 7);
    myPolyIdentical.changeCoefficient(-1, 2);
    myPolyIdentical.changeCoefficient(1, 1);
    myPolyIdentical.changeCoefficient(5, 0);
    cout << myPoly << " and " << myPoly2 << (myPoly == myPoly2 ? " are " : " are not ") << "the same." << endl;
    cout << myPoly << " and " << myPoly2 << (myPoly != myPoly2 ? " are " : " are not ") << "different." << endl;
    cout << myPoly << " and " << myPolyIdentical << (myPoly == myPolyIdentical ? " are " : " are not ") << "the same." << endl;
    cout << myPoly << " and " << myPolyIdentical << (myPoly != myPolyIdentical ? " are " : " are not ") << "different." << endl << endl;
   

    //testing overloaded arithmetic operators
    cout << "testing additions and subtraction operators: " << endl;
    Polynomial sumPoly = myPoly + myPoly2;
    cout << "(" << myPoly << ") + (" << myPoly2 << ") = " << sumPoly << endl;
    Polynomial diffPoly = myPoly - myPoly2;
    cout << "(" << myPoly << ") - (" << myPoly2 << ") = " << diffPoly << endl << endl;

    //testing copy constructor
    cout << "testing copy constructor: " << endl;
    cout << " ...constructing copy of: " << sumPoly << endl;
    Polynomial copyPoly = sumPoly;
    cout << "copy: " << copyPoly << endl;
    cout << "comparison: " << endl;
    cout << copyPoly << " and " << sumPoly << (copyPoly == sumPoly ? " are " : " are not ") << "the same." << endl;
    cout << " ...constructing copy of: " << diffPoly << endl;
    Polynomial copyPoly2(diffPoly);
    cout << "copy: " << copyPoly2 << endl;
    cout << "comparison: " << endl;
    cout << copyPoly2 << " and " << diffPoly << (copyPoly2 == diffPoly ? " are " : " are not ") << "the same." << endl << endl;


    //testing overloaded assignment operators
    cout << "testing assignment operator: " << endl;
    Polynomial myPoly3;
    myPoly3.changeCoefficient(90, 5);
    cout << "assigning " << copyPoly << " to " << myPoly3 << endl;
    copyPoly = myPoly3;
    cout << "comparison: " << endl;
    cout << copyPoly << " and " << myPoly3 << (copyPoly == myPoly3 ? " are " : " are not ") << "the same." << endl << endl;
    cout << "testing subtraction assignment operator: " << endl;    
    Polynomial testPoly;
    testPoly.changeCoefficient(-4, 4);
    testPoly.changeCoefficient(9, 3);
    testPoly.changeCoefficient(1, 0);
    Polynomial testPolyOG = testPoly;
    Polynomial subPoly;
    subPoly.changeCoefficient(-3, 0);
    subPoly.changeCoefficient(2, 4);
    cout << testPoly << " -= " << subPoly << " ...produces... " << (testPoly -= subPoly) << endl;
    cout << "comparing to a copy of the original: " << endl;
    cout << testPoly << " and " << testPolyOG << (testPoly == testPolyOG ? " are " : " are not ") << "the same." << endl << endl;
    cout << "testing addition assignment operator: " << endl;    
    Polynomial addPoly;
    addPoly.changeCoefficient(-3, 0);
    addPoly.changeCoefficient(2, 4);
    cout << testPoly << " += " << addPoly << " ...produces... " << (testPoly += addPoly) << endl;
    cout << "comparing to a copy of the original: " << endl;
    cout << testPoly << " and " << testPolyOG << (testPoly == testPolyOG ? " are " : " are not ") << "the same." << endl << endl;
    return 0;
}