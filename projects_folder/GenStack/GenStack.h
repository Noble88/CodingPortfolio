#ifndef GENSTACK_H
#define GENSTACK_H

#include <iostream>
using namespace std;

class GenStack{
  public: 
    GenStack();
    GenStack(int maxSize);  
    ~GenStack();

    //Core functions
    void push(char data); //places element at top of stack
    char pop(); //return and remove
    char peek(); //returns top of stack

    //Aux functions  
    bool isEmpty();
    bool isFull();
    int getSize();


  private:
    int top;
    int mSize;
    char *myArray; // We dont know size of stack so we need pointer & will point to the first memory adress... Remember if know starting adress of array and data type than it will be X bytes over (in this case a char is 1 byte)
};

#endif