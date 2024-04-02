#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"

class LinkedList{
  private:
    ListNode *front;
    ListNode *back;
    unsigned int size;

  public: 
    LinkedList();
    ~LinkedList(); 

    void InsertFront(int d);
    void InsertBack(int d);
    int RemoveFront();
    int Find(int val);
    int DeleteAtPos(int pos);
    bool IsEmpty();
    unsigned int GetSize();
};

#endif