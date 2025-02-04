#include "Stack.h"
#include <iostream>

// Constructor to initialize an empty stack
Stack::Stack() {
    // TODO: Your code here
    top = -1;
}

// Adds a province to the top of the stack
void Stack::push(int province) {
    // TODO: Your code here
    if(getSize() == MAX_SIZE){
        std::cout<<"stack is full"<<std::endl;
        return; //sil
    }
    else{
        top++;
        data[top] = province;
    }
}

// Removes and returns the top province from the stack
int Stack::pop() {
    // TODO: Your code here
    if(isEmpty()==true){
        //std::cout<<"stack is empty"<<std::endl;
        return -1;
    }else{
        int value = data[top];
        top--;
        return value;
    }
}

// Returns the top province without removing it
int Stack::peek() const {
    // TODO: Your code here
    if(isEmpty()==true){
        std::cout<<"stack is empty"<<std::endl;
        return -1;
    }else{
        int value = data[top];
        return value;
    }
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    // TODO: Your code here
    if(top == -1){
        //std::cout<<"stack is empty"<<std::endl;
        return true;
    }
    return false;
}

// Function to get the current size of the stack
int Stack::getSize() const {
    // TODO: Your code here
    return top + 1;
}
