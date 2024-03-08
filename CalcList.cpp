/*
Name: Felicia Drysdale
Class: COP 4530 - Section 3
Summary: The calculator will be able to perform addition, subtraction, multiplication, and division. 
The calculator will keep a running total of the operations completed, the number of operations completed, 
and what those operations were. The calculator will have an undo function to remove the last operation
*/

#include "CalcList.hpp"

//constructor
CalcList::CalcList() {
    head = nullptr; 
    curr = new CalcNode;
}

//deconstructor
CalcList::~CalcList() {
	while (!empty()) removeFront();
}

void CalcList::removeFront() {
CalcNode* curr = head; // save current head
    head = curr->next; // skip over old head
    delete curr; // delete the old head
}

//if empty
bool CalcList::empty() const{
    return head == nullptr;
}

//This method returns the current total of the CalcList
double CalcList::total() const {

    //check if empty -> return 0 (test case)
    if (empty()) {
        return 0;
    }

    //return first element of linkedlist (current total) (head)
    return head->mytotal;
}

//Adds an operation to the CalcList and creates a new total.
void CalcList::newOperation(const FUNCTIONS func, const double operand) {

    //make new node for each operation therefore we can always pull newtotal first without walking
    CalcNode* newNode = new CalcNode;

    //get current total
    double newtotal = total();

    //Do conversion for each function so new total can be put into node of linked list
    if (func == ADDITION) {
        newtotal += operand;

    } else if (func == SUBTRACTION) {
        newtotal -= operand;

    } else if (func == DIVISION) {
        if (operand == 0) {
            throw std::invalid_argument("Cannot divide by 0");
        }
        else {
            newtotal /= operand;
        }

    } else if (func == MULTIPLICATION) {
        newtotal *= operand;
    }

    //always add to front to access easy
    newNode->mytotal = newtotal;
    newNode->myoperand = operand;
    newNode->myoperation = func;

    if (curr == nullptr) {
        head = newNode;
        newNode->next = nullptr;
    }

    //update pointers
    newNode->next = head;
    head = newNode;
}

//Removes the last operation from the calc list and restores the previous total.
void CalcList::removeLastOperation() {

    //check if empty
    if (empty()) {
        throw std::invalid_argument("List is empty");
    }

    CalcNode* curr = head; //save current head
    head = curr->next; //skip over old
    delete curr; //delete the old head
}

//Returns a string of the list of operations completed so far formatted with a fixed point precision. 
std::string CalcList::toString(unsigned short precision) const {

     std::ostringstream oss;
    //make sure node is starting at head
    CalcNode *curr = head;

    int i = 1;
    //loop so we get length of linkedlist
    while (curr->next != nullptr) {

        curr = curr->next;
        i++;
    }

    oss.precision(precision);

    //restart back at head for next loop
    curr = head;

    float x = 0.000;
    //loop
    while (curr != nullptr) {

        //check so we can make sure the last total is 0 (well technically the first but i added to head)
        if (curr->next != nullptr) {
            oss << i << ": " << std::fixed << std::setprecision(precision) << curr->next->mytotal;

        } else {
            //x = 1;
            oss << i << ": " << std::fixed << std::setprecision(precision) << x;
        }

        //ussing sstream to change to function operation symbol
        if (curr->myoperation == ADDITION) {
            oss << '+';

        } else if (curr->myoperation == SUBTRACTION) {
            oss << '-';

        } else if (curr->myoperation == DIVISION) {
            oss << '/';

        } else if (curr->myoperation == MULTIPLICATION) {
            oss << '*';
        }

        oss << std::fixed << std::setprecision(precision) << curr->myoperand << "=";
        oss << std::fixed << std::setprecision(precision) << curr->mytotal<< "\n";

        curr = curr->next;
        i--;
    }
    return oss.str();
 }




