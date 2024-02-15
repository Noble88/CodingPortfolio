#include "GenStack.h"

GenStack::GenStack(){ //default constrcutor
  mSize = 64; //dafualt size of stack
  top = -1; //Its -1 cuz first push() will make it 0 for the first addition
  myArray = new char[mSize]; //Since myArray is a pointer we do new (allocated memory on to the heap)
}
GenStack::GenStack(int maxSize){
  mSize = maxSize; //dafualt size of stack
  top = -1;
  myArray = new char[mSize];
}
GenStack::~GenStack(){//deconstructor
  cout << "stack destroyed, garbage taken out has been" << endl;
  delete[] myArray;
}

//Core functions
void GenStack::push(char data){
  if(isFull()){
    cout << "resizing stack " << endl;
    char *temp = new char[mSize*2];
    for(int i=0; i<mSize; ++i){
      temp[i]=myArray[i];
    }
    mSize*=2;
    delete[] myArray;
    myArray = temp;
    throw runtime_error("stack if full");
  }
  myArray[++top] = data;
}
char GenStack::pop(){
  if(isEmpty()){
    throw runtime_error("stack if Empty");
  }
  //Check if Empty
  return myArray[top--]; // 'top--' instead of '--top' as post increment -> checks top number then decrements
}
char GenStack::peek(){
  return myArray[top];
}

//Aux functions  
bool GenStack::isFull(){
  return (top == mSize - 1);
}
bool GenStack::isEmpty(){
  return (top==-1);
}

int GenStack::getSize(){
  return top+1;
}