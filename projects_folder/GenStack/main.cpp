// Project1/main.cpp
#include <iostream>

//TODO: Add debugger Terminal Handler

#include "GenStack.h"
int main() {
  GenStack *myStack = new GenStack(5);

  try{
    cout <<"Size of Stack is "<< myStack->getSize() << endl;
    
    cout << "Pushing: H,E,L,L,O" << endl;
    myStack->push('H'); myStack->push('E'); myStack->push('L'); myStack->push('L'); myStack->push('O');

    cout << "SIZE: " << myStack->getSize() << endl;
    cout << "PEEK: " << myStack->peek() << endl;
    cout << "POP: " << myStack->pop() << endl;
    
    cout << "SIZE: " << myStack->peek() << endl;
    cout << "PEEK: " << myStack->peek() << endl;
    
    cout << "Adding 1 more above the size limit \'S\'" << endl;
    myStack->push('O');
    myStack->push('S');

    cout << "emptying stack" << endl;
    while(!myStack->isEmpty()){
      cout << "POP: " << myStack->pop() << endl;
    }
    
    cout << "SIZE: " << myStack->getSize() << endl;
    cout << "PEEK: " << myStack->peek() << endl;
    
  }
  catch(runtime_error &except){
    cout << except.what() << endl; //returns the error message made in .cpp
  }
  delete myStack; //Things stored on heap need to be manually deleted
  
  return 0;
}
