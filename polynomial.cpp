/*
A program for an abstract representation of a polynomial via implementing a linked list of Term structs.
*/
#include "polynomial.h"
using namespace std;

/*
*----------------------------- I/O OPERATORS ---------------------------------
*/
//------------------------- operator<< overload ------------------------------
//print out a polynomial ADT in common polynomial form
//precondition: a polynomial object
//postcondition: that object, unchanged, will have been printed to output
ostream& operator<<(ostream& output, const Polynomial &p) {
    Polynomial::Term *curptr = p.head->next;
    while (curptr != p.head) {
        if (curptr->prev == p.head) { //formatting for first term (keep sign attached)
            if (curptr->coeff == 1) {  
                if (curptr->power == 1) output << "x";
                else if (curptr->power == 0) output << curptr->coeff;
                else output << "x^" << curptr->power;
            }
            else if (curptr->coeff == -1) {
                if (curptr->power == 1) output << "-x";
                else if (curptr->power == 0) output << curptr->coeff;
                else output << "-x^" << curptr->power;
            }
            else {
                if (curptr->power == 1) output << curptr->coeff << "x";
                else if (curptr->power == 0) output << curptr->coeff;
                else output << curptr->coeff << "x^" << curptr->power;
            }
        }
        else if (curptr->coeff < 0) { //formatting for negative terms after head (replace sign with a subtraction operand to the left)
            output << " - ";
            if (curptr->coeff == -1) { 
                if (curptr->power == 1) output << "x";
                else if (curptr->power == 0) output << abs(curptr->coeff);
                else output << "x^" << curptr->power;
            }
            else {
                if (curptr->power == 1) output << abs(curptr->coeff) << "x";
                else if (curptr->power == 0) output << abs(curptr->coeff);
                else output << abs(curptr->coeff) << "x^" << curptr->power;
            }
        }
        else if (curptr->coeff > 0) { //formatting for positive terms, place addition operand to the left
            output << " + ";
            if (curptr->coeff == 1) {
                if (curptr->power == 1) output << "x";
                else if (curptr->power == 0) output << curptr->coeff;
                else output << "x^" << curptr->power;
            }
            else {
                if (curptr->power == 1) output << curptr->coeff << "x";
                else if (curptr->power == 0) output << curptr->coeff;
                else output << curptr->coeff << "x^" << curptr->power;
            }
        }
        curptr = curptr->next;
    }
    return output;
}

/*
*------------------------ CONSTRUCTORS/DESTRUCTORS ----------------------------
*/
//------------------------------- default -------------------------------------
//creates a polynomial 
//precondition: none
//postcondition: an empty polynomial
Polynomial::Polynomial() {
    size = 0;
    head = new Term;
    head->next = head;
    head->prev = head;
    head->power = 0;
    head->coeff = 0.0;
}

//---------------------------- copy constructor -------------------------------
//creates a polynomial as a copy of another polynomial
//precondition: two polynomials, one being initialized as a copy of the other, or being assigned the value of the other
//postcondition: both polynomials will be identical
Polynomial::Polynomial(const Polynomial &p) {
    size = p.size;
    head = new Term;
    head->next = head;
    head->prev = head;
    head->power = 0;
    head->coeff = 0.0;

    Term *prevptr = head;
    Term* origptr = p.head->next;
    while (origptr != p.head) {
        Term* newptr = new Term;
        newptr->coeff = origptr->coeff;
        newptr->power = origptr->power;
        newptr->prev = prevptr;
        newptr->next = head;
        head->prev = newptr;
        prevptr->next = newptr;
        prevptr = newptr;		// update pointer
        origptr = origptr->next; 	// update pointer
    }
}

//------------------------------ destructor -----------------------------------
//deallocates a polynomial from system memory
//precondition: a polynomial
//postcondition: all polynomials (all Terms within) will be deallocated from system memory
Polynomial::~Polynomial() {
    Term *curptr = head->next;
    while (curptr != head) {
        remove(curptr);
        curptr = curptr->next; 
    }
    if (curptr == head) {
        head->next = NULL;
        head->prev = NULL;
        delete curptr;
    }
}

/*
*--------------------------- MUTATORS/ACCESSORS -------------------------------
*/
//-------------------------------- degree -------------------------------------
//returns highest degree of a polynomial
//precondition: must call on a Polynomial object
//postconditions: returns the highest degree of a polynomial
//                will return 0 for an empty polynomial
int Polynomial::degree() const {
    return head->next->power;
}

//------------------------------ coefficient ----------------------------------
//returns the coefficient of the x^power term
//precondition: must call on a Polynomial object
//postconditions: returns the coefficient of the x^power term
//                returns 0.0 if no term with such power was found
double Polynomial::coefficient( const int power ) const { 
    Term *curptr = head->next;
    while (curptr != head) {
        if (curptr->power == power) return curptr->coeff;
        curptr = curptr->next;
    }
    return 0.0;
}

//--------------------------- changeCoefficient -------------------------------
//adds, remove, or changes a coefficient in this polynomial
//preconditions: must call on a Polynomial object, newPower should be a positive integer
//postconditions: the coefficient of a term to the power of "newPower" becomes newCoeff. 
//                if no term exists, a new term is created with newCoeff and newPower as it's values.
//                if newCoeff was 0, than either nothing is added, or the existing term with power "newPower" is removed.
bool Polynomial::changeCoefficient(double newCoeff, int newPower) {
    Term *curptr = head->next;
    while ((curptr != head) && (curptr->power > newPower)) { //traverse until the end OR until we found a power less than or equal to newPower
        curptr = curptr->next;
    }
    if (curptr == head) { //if we are at the end, or the list is empty, insert a new term before header
        if (newCoeff == 0) {
            return true;
        }
        insert(curptr, newCoeff, newPower);
    }
    else if (curptr->power == newPower){ //if we have found a term with the same power as what this function was called with, change its coefficent
        if (newCoeff == 0) {
            remove(curptr);
            return true;
        }
        curptr->coeff = newCoeff;
    }
    else if (curptr->power < newPower) { //if we have found a term with a power less than newPower, than we insert a new term before it
        if (newCoeff == 0) {
            return true;
        }
        insert(curptr, newCoeff, newPower);
    }
    return true;
}

/*
*--------------------------- ARITHMETIC OPERATORS -----------------------------
*/
//-------------------------------- addition -----------------------------------
//adds two polynomials together
//precondition: two Polynomials as operands
//postconditions: return the sum of the Polynomial operands
Polynomial Polynomial::operator+( const Polynomial& p ) const { 
    Polynomial sum;                                             
    Term *curptrA = head->next;
    Term *curptrB = p.head->next;
    while (curptrA != head && curptrB != p.head) { //iterate to find matching powers, add their sum to sum polynomial
        if (curptrA->power == curptrB->power) {     
            sum.changeCoefficient((curptrA->coeff + curptrB->coeff), curptrA->power);
            curptrA = curptrA->next; 
            curptrB = curptrB->next; 
        }
        else if (curptrA->power > curptrB->power) {
            sum.changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
        else if (curptrB->power > curptrA->power) {
            sum.changeCoefficient(curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }
    }
    if (curptrA != head) { //add remaining unmatched terms from left side operand to sum polynomial
        while (curptrA != head) {
            sum.changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
    }
    if (curptrB != p.head) { //add remaining unmatched terms from right side operand to sum polynomial
        while (curptrB != p.head) {
            sum.changeCoefficient(curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }       
    }
    return sum;
}

//------------------------------ subtraction ----------------------------------
//subtracts one polynomial from another
//precondition: two Polynomials as operands
//postconditions: return the difference of the Polynomial operands, subtracting right from left
Polynomial Polynomial::operator-( const Polynomial& p ) const {
    Polynomial diff;                                             
    Term *curptrA = head->next;
    Term *curptrB = p.head->next;
    while (curptrA != head && curptrB != p.head) { //iterate to find matching powers, add their difference to diff polynomial
        if (curptrA->power == curptrB->power) {     
            diff.changeCoefficient((curptrA->coeff - curptrB->coeff), curptrA->power);
            curptrA = curptrA->next; 
            curptrB = curptrB->next; 
        }
        else if (curptrA->power > curptrB->power) {
            diff.changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
        else if (curptrB->power > curptrA->power) {
            diff.changeCoefficient(-curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }
    }
    if (curptrA != head) { //add remaining unmatched terms from left side operand to diff polynomial
        while (curptrA != head) {
            diff.changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
    }
    if (curptrB != p.head) { //add remaining unmatched terms from right side operand to diff polynomial
        while (curptrB != p.head) {
            diff.changeCoefficient(-curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }       
    }
    return diff;
}

/*
*--------------------------- COMPARISON OPERATORS -----------------------------
*/
//-------------------------------- equal to -----------------------------------
//checks whether two polynomials are identical
//precondition: two Polynomials as operands
//postconditions: returns true if operands are identical, returns false if they are not
bool Polynomial::operator==( const Polynomial& p ) const {
    bool sameness = false;
    if (p.size != size) return sameness;

    Term *curptrA = head->next;
    Term *curptrB = p.head->next;
    while (curptrA->coeff == curptrB->coeff && curptrA->power == curptrB->power) {
        if (curptrA->next == head) {
            sameness = true;
            break;
        }
        curptrA = curptrA->next;
        curptrB = curptrB->next;
    }
    return sameness;
}


//------------------------------ not equal to ---------------------------------
//checks whether two polynomials are not identical
//precondition: two Polynomials as operands
//postconditions: returns true if operands are not identical, returns false if they are
bool Polynomial::operator!=( const Polynomial& p ) const {
    bool unsameness = true;
    if (p.size != size) return unsameness;

    Term *curptrA = head->next;
    Term *curptrB = p.head->next;
    while (curptrA->coeff == curptrB->coeff && curptrA->power == curptrB->power) {
        if (curptrA->next == head) {
            unsameness = false;
            break;
        }
        curptrA = curptrA->next;
        curptrB = curptrB->next;
    }
    return unsameness;
}

/*
*--------------------------- ASSIGNMENT OPERATORS -----------------------------
*/
//--------------------------- simple assignment -------------------------------
//assigns left polynomial to right polynomial
//precondition: two Polynomials as operands
//postconditions: left operand will be identical to right operand
Polynomial& Polynomial::operator=( const Polynomial& p ) {
    Term *curptr = head->next;
    while (curptr != head) {
        remove(curptr);
        curptr = curptr->next; 
    }

    size = p.size;
    Term *prevptr = head;
    Term *origptr = p.head->next;
    while (origptr != p.head) {
        Term *newptr = new Term;
        newptr->coeff = origptr->coeff;
        newptr->power = origptr->power;
        newptr->prev = prevptr;
        newptr->next = head;
        head->prev = newptr;
        prevptr->next = newptr;
        prevptr = newptr;	
        origptr = origptr->next; 	
    }
    return *this;
}

//--------------------------- addition assignment -----------------------------
//increments left polynomial by the right polynomial
//precondition: two Polynomials as operands
//postconditions: returns left operand as a sum of itself plus right operand
Polynomial& Polynomial::operator+=( const Polynomial& p ) { //
    Term *curptrA = head->next;
    Term *curptrB = p.head->next;
    while (curptrA != head && curptrB != p.head) { //iterate to find matching powers, add their sum to sum polynomial
        if (curptrA->power == curptrB->power) {     
            changeCoefficient((curptrA->coeff + curptrB->coeff), curptrA->power);
            curptrA = curptrA->next; 
            curptrB = curptrB->next; 
        }
        else if (curptrA->power > curptrB->power) {
            changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
        else if (curptrB->power > curptrA->power) {
            changeCoefficient(curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }
    }
    if (curptrA != head) { //add remaining unmatched terms from left side operand to sum polynomial
        while (curptrA != head) {
            changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
    }
    if (curptrB != p.head) { //add remaining unmatched terms from right side operand to sum polynomial
        while (curptrB != p.head) {
            changeCoefficient(curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }       
    }
    return *this;
}

//-------------------------- subtraction assignment ---------------------------
//decrements left polynomial by right polynomial
//precondition: two Polynomials as operands
//postconditions: returns left operand as the difference of itself minus right operand
Polynomial& Polynomial::operator-=( const Polynomial& p ) {
    Term *curptrA = head->next;
    Term *curptrB = p.head->next;
    while (curptrA != head && curptrB != p.head) { //iterate to find matching powers, add their difference to diff polynomial
        if (curptrA->power == curptrB->power) {     
            changeCoefficient((curptrA->coeff - curptrB->coeff), curptrA->power);
            curptrA = curptrA->next; 
            curptrB = curptrB->next; 
        }
        else if (curptrA->power > curptrB->power) {
            changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
        else if (curptrB->power > curptrA->power) {
            changeCoefficient(-curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }
    }
    if (curptrA != head) { //add remaining unmatched terms from left side operand to diff polynomial
        while (curptrA != head) {
            changeCoefficient(curptrA->coeff, curptrA->power);
            curptrA = curptrA->next; 
        }
    }
    if (curptrB != p.head) { //add remaining unmatched terms from right side operand to diff polynomial
        while (curptrB != p.head) {
            changeCoefficient(-curptrB->coeff, curptrB->power);
            curptrB = curptrB->next; 
        }       
    }
    return *this;
}

//--------------------------------- insert ------------------------------------
//inserts a polyonmial before the parameter polynomial
//precondition: must be called with a Term that exists within a polynomial
//postcondition: a new term is inserted before an existing Term within a polynomial
bool Polynomial::insert(Term* pos, const double newCoeff, const int newPower) {
    Term *newptr = new Term;
    newptr->coeff = newCoeff;
    newptr->power = newPower;
    newptr->next = pos;
    newptr->prev = pos->prev;
    pos->prev = newptr;
    newptr->prev->next = newptr;
    size++;
    return true;
}

//--------------------------------- remove ------------------------------------
//removed the parameter polynomial
//precondition: must be called with a Term that exists within a polynomial
//postcondition: the given term is removed from the list
bool Polynomial::remove(Term* pos) {
    Term *del = pos;
    del->prev->next = del->next;
    del->next->prev = del->prev;
    delete del;
    size--; 
    return true;
}


