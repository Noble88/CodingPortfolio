#ifndef GENQUEUE_H
#define GENQUEUE_H

#include <exception>
#include <iostream>
using namespace std;

class GenQueue {
public:
  GenQueue(); // default
  GenQueue(int maxSize);
  ~GenQueue(); // deconstructor

  // core functions
  void Insert(char data); // places element at back of queue
  char Remove(); //dequeue
  char Peek(); // returns front of queue

  bool IsEmpty();
  bool IsFull();
  unsigned int GetSize(); //unsigned means wont return NEGATIVE
  void PrintArray(); //Help ufnction to help visualie our array

private:
  unsigned int mSize;
  unsigned int front;
  unsigned int rear;
  unsigned int numElements;
  char *myQueue;
};

#endif
