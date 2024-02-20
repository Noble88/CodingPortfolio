#include "GenQueue.h"

int main (int argc, char **argv){
  GenQueue *myQueue = new GenQueue(5);

  try {
    myQueue -> Insert('f');
    myQueue -> Insert('o');
    myQueue -> Insert('o');
    myQueue -> Insert('b');
    myQueue -> Insert('a');

    cout << "PEEK: " << myQueue -> Peek() <<endl;
    cout << "REMOVE: " << myQueue -> Remove() <<endl;
    cout << "PEEK: " << myQueue -> Peek() <<endl;

    myQueue->PrintArray();
  }
  catch(runtime_error &expect){
    cerr<< expect.what() << endl;
  }
  
  delete myQueue;
    
  
  return 0;
}