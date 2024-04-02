#include "GenQueue.h"

GenQueue::GenQueue() {
  mSize = 64;
  front = 0;
  rear = 0;
  numElements = 0;
  myQueue = new char[mSize];
}

GenQueue::GenQueue(int maxSize) {
  mSize = maxSize;
  front = 0;
  rear = 0;
  numElements = 0;
  myQueue = new char[mSize];
}

GenQueue::~GenQueue() { delete[] myQueue; }

void GenQueue::Insert(char data) {
  if(IsFull()){
    throw runtime_error("Queue is full");
  }
  myQueue[rear++]=data;
  rear%=mSize;
  numElements++;
}

char GenQueue::Remove() {
  if(IsEmpty()){
    throw runtime_error("Queue is empty, nothing to remove");
  }
  char c = '\0';
  c = myQueue[front++];
  front%=mSize;
  numElements--;
  return c;
}

void GenQueue::Enqueue(char data){
  if(IsFull()){
    throw runtime_error("priority Queue is full");
  }

  int i= numElements-1;
  while(i>=0 && data<myQueue[i]){
    myQueue[i+1]=myQueue[i];
    i--;
  }
  myQueue[i+1]=data;
  numElements++;
}

char GenQueue::Peek() { 
  if(IsEmpty()){
    throw runtime_error("Queue is empty, nothing to remove");
  }
  return myQueue[front]; 
}

bool GenQueue::IsFull() { return (numElements == mSize); }

bool GenQueue::IsEmpty() { return (numElements == 0); }

unsigned int GenQueue::GetSize() { return numElements; }

void GenQueue::PrintArray(){
  cout  <<"Q: SIZE: "<<GetSize()<<endl;
  cout  <<"FRONT: "<<front<<endl;
  cout  <<"REAR: "<<rear<<endl;

  for(int i=0; i<mSize; ++i){
    cout  <<"Q["<<i<<"]: "<<myQueue[i]<<endl;
    if(i!=mSize-1){
      cout << " | ";
    }
  }
  cout <<endl;
}
