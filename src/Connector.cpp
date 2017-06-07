#include "Connector.h"

#include <iostream>

using namespace std;

// checks for left and right commands for tree used in parsing
void Connector::errorCheck() {
    if (!leftChild) {
        cout << "No left child" << endl;
        exit(1);
    } else if (!rightChild) {
         cout << "No right child" << endl;
        exit(1);
    }
}

void Connector::setLeftChild(Shell* left) {
    leftChild = left;
}

void Connector::setRightChild(Shell * right) {
    rightChild = right;
}

bool And::execute() {
    // checks to make sure there is a left and right child
    errorCheck();
    return (leftChild->execute() && rightChild->execute());
}

bool Or::execute() {
    errorCheck();
    return (leftChild->execute() || rightChild->execute());
}

bool SemiColon::execute() {
    // temp variable
    bool temp = leftChild->execute();   
    //use temp to avoid error from compiler
    temp = rightChild->execute();       
    return temp;
}

bool Parentheses::execute() {
    // always returns true to execute first
    return true;

}


