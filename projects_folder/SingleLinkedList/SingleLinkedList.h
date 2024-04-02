#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include "ListNode.h"

class SingleLinkedList{
  private:
    ListNode *front;
    ListNode *back;
    unasigned int size;
  
  public: 
    SingleLinkedList();
    ~SingleLinkedList(); 

    void InsertFront(int d);
    void InsertBack(int d);
    int RemoveFront();
    int Find(int val);
    int DeleteAtPos(int pos);
    bool IsEmpty();
    unsigned int GetSize();
};
  
#endif