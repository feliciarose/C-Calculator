/*
Name: Felicia Drysdale
Class: COP 4530 - Section 3
Remember (textbook): header file typically contains many declarations, including classes, structures, constants, enumerations, and typedefs.
 Header files generally do not contain the definition (body) of a function. In-line functions are an excep- tion, 
 however, as their bodies are given in a header file.
 */

#ifndef CALCLIST_H
#define CALCLIST_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "CalcListInterface.hpp"
using namespace std;

//Node for linked list
class CalcNode {
private:
    CalcNode* next; //next item in the list
    friend class CalcList; //access to friend list
    FUNCTIONS myoperation; //operation
    double myoperand; //operand
    double mytotal = 0; //total of operations
};

//Linked list
class CalcList: public CalcListInterface {

public:
    CalcList(); //constructor
    ~CalcList(); //deconstructor
    bool empty() const; //is list empty?
    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();
    void removeFront();
    std::string toString(unsigned short precision) const;
    CalcNode* curr; //current node

private:
    CalcNode* head; //head of linked list
};

#endif //CALCLIST_H