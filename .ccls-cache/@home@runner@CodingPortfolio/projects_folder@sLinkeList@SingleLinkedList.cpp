#include "SingleLinkedList.h"
#include "ListNode.h"

SingleLinkedList::SingleLinkedList(){
  front = NULL;
  back = NULL;
  size=0;
}

SingleLinkedList::~SingleLinkedList(){

}

void SingleLinkedList::InsertFront(int d){
  ListNode* node = new ListNode(d);
  if(IsEmpty()){ // check to first node can be assigned to front and back
    back = node;
  }
  else{
    node->next = front;
  }

  front = node;
  size++;
}

void SingleLinkedList::InsertBack(int d){
  ListNode *node = new ListNode(d);

  if(IsEmpty()){
    front = node;
  }
  else{
    back->next = node;
  }
  back = node;
  size++;
}

bool SingleLinkedList::IsEmpty(){
  return (size==0);
}

unsigned int SingleLinkedList::GetSize(){
  return size;
}

int SingleLinkedList::RemoveFront(){
  if(IsEmpty()){
    cout << "LIST EMPTY" << endl;
    return -1;
  }

  int temp=front->data; //get front data
  
  ListNode *ft = front; // stores the front object
  front = front ->next; //get the second front from the front object
  ft->next=NULL; //NULL current front (aka delete it)
  size--;
  delete ft; //delete the object data from heap
  return temp;
}

int SingleLinkedList::Find(int val){
  int pos =-1;
  ListNode *curr = front;
  
  while(curr != NULL){
   ++pos;
    if(curr->data==val){
      break;
    }
    curr=curr->next;
  }
  if(front->data == val){
    pos = 0;
  }
  if(curr==NULL){
    pos = -1;
  }
  return pos;
}

int SingleLinkedList::DeleteAtPos(int pos){
  //assuming valid of posiiton

  int count =0;
  ListNode *curr = front;
  ListNode *prev = front;

  while(count != pos){
    prev= curr;
    curr = curr->next;
    count++;
  }

  if(curr==front){
    front = curr->next;
  }
  if(curr==back){
    back = prev;
  }
  
  prev->next = curr->next;
  curr-> next = NULL;
  int temp = curr->data;
  size--;
  delete curr;
  return temp;
  
}