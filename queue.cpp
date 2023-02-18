//*****************************************************************************
// Name: queue.cpp
// Descrtiption: This is the executable file for the Queue class object.
//*****************************************************************************
#include "queue.h"

// name: Queue()
// description: this function is the constructor.
// input: none
// output: none
Queue::Queue() : front(nullptr), back(nullptr), size(0) {}

// name: Queue(const Queue &aQueue)
// description: this function is the param constructor.
// input: none
// output: none
Queue::Queue(const Queue &aQueue) : front(nullptr), back(nullptr), size(0)
{
   *this = aQueue;
}

// name: ~Queue()
// description: this function is the destructor
// input: none
// output: none
Queue::~Queue()
{
   destroy();
}

// name: destroy(Node *aNode)
// description: this function deletes all node elements of the queue.
// input: none
// output: none
void Queue::destroy()
{
   Node *curr = front;
   for (int i = 0; i < size; i++)
   {
      front = curr->next;
      delete curr;
      curr = front;
   }
   front = nullptr;
   back = nullptr;
   size = 0;
}

// name: enqueue(const Group &aGroup)
// description: this function adds a new node element to the end of the queue.
// input: none
// output: none
void Queue::enqueue(const Group &aGroup)
{
   Node *newNode = new Node(aGroup, this->size + 1);
   if (isEmpty())
   {
      front = newNode;
   }
   else
   {
      back->next = newNode;
   }
   this->size++;
   back = newNode;
   back->next = front;
}

// name: dequeue(const Group &aGroup)
// description: this function removes the first element in the queue if the
// queue is not empty and then updates the remaining element queueNums.
// input: none
// output: none
bool Queue::dequeue()
{
   if (!isEmpty())
   {
      Node *target = front;
      if (front == back)
      {
         front = nullptr;
         back = nullptr;
      }
      else
      {
         front = front->next;
         back->next = front;
      }
      delete target;
      target = nullptr;
      size--;
      updateQueuePos(front, size); // update all element queueNum's recursively
      return true;
   }
   return false;
}
// name: updateQueuePos(Node *&aNode)
// description: this function updates queueNum of every element recursively
// after a dequeue.
// input: none
// output: none
void Queue::updateQueuePos(Node *&aNode, const int size)
{
   if (aNode && size != 0)
   {
      updateQueuePos(aNode->next, size - 1);
      aNode->queueNum--;
   }
}

// name: peek(Group &aGroup) const
// description: this function returns false and displays an error message if
// the queue is empty or true if not empty and passes the first element in the
// queue by reference back to the caller program.
// input: none
// output: error message if Queue is empty.
bool Queue::peek(Group &aGroup) const
{
   if (isEmpty())
   {
      cerr << "peek() called with empty queue" << endl
           << endl;
      return false;
   }
   aGroup = *front->data;
   return true;
}

// name: getSize() const
// description: this function returns size.
// input: none
// output: none
int Queue::getSize() const
{
   return size;
}

// name: isEmpty() const
// description: this function returns the bool value of size == 0.
// input: none
// output: none
bool Queue::isEmpty() const
{
   return size == 0;
}

// name: &operator=(const Queue &aQueue)
// description: this function is the copy assignment operator function.
// input: none
// output: none
const Queue &Queue::operator=(const Queue &queueSrc)
{
   if (this == &queueSrc)
      return *this;
   if (this->front)
      destroy();

   int count = 0;

   for (Node *srcCurr = queueSrc.front; count < queueSrc.size; srcCurr = srcCurr->next)
   {
      enqueue(*srcCurr->data);
      count++;
   }
   return *this;
}

// name: &operator<<(ostream &out, const Queue &aQueue)
// description: this function is the output assignment operator function.
// input: none
// output: formatted text and the values of each Queue element.
ostream &operator<<(ostream &out, const Queue &aQueue)
{
   Queue::Node *curr = aQueue.front;
   cout << "Displaying the queue..." << endl
        << endl
        << "Order\tName\tTable\t Request   Phone #   Promo List" << endl
        << "--------------------------------------------------------" << endl;
   for (int i = 0; i < aQueue.size; i++)
   {
      out << curr->queueNum << ". \t";
      out << *(curr->data);
      curr = curr->next;
   }
   return out;
}

// name: loadFromFile(const char *fileName)
// description: this function opens a file and uses the data in each line item
// to create group elements and send them to the enqueue function to be added
// to the queue.
// input: none
// output: error message if file fails to open.
void Queue::loadFromFile(const char *fileName)
{
   ifstream file;
   const int MAX_CHAR = 100;
   char currName[MAX_CHAR + 1];
   char contact[MAX_CHAR + 1];
   int size = 0;
   char request = 0;
   char contactInput = 0;
   bool contactList = false;

   file.open(fileName);
   if (!file)
   {
      cerr << "Failed to open" << fileName << " for reading!" << endl;
      exit(1);
   }

   file.get(currName, MAX_CHAR, ';');
   while (!file.eof())
   {
      file.ignore(1);
      file >> size;
      file.ignore(1);
      file >> request;
      file.ignore(1);
      file >> contactInput;
      file.ignore(1);
      file.get(contact, MAX_CHAR, '\n');
      file.ignore(1);
      if (contactInput == 'y' || contactInput == 'Y')
      {
         contactList = true;
      }
      else
      {
         contactList = false;
      }
      Group currGroup(currName, size, request, contactList, contact);
      enqueue(currGroup);
      file.get(currName, MAX_CHAR, ';');
   }
   file.close();
}

// name: saveToFile(const char *fileName) const
// description: this function opens a file in append mode and saves the first
// queue element's name & contact information.
// input: none
// output: error message if file fails to open.
void Queue::saveToFile(const char *fileName) const
{
   ofstream file;
   Group aGroup;

   if (peek(aGroup) && aGroup.getContactInput())
   {
      file.open(fileName, ios::app);
      if (!file)
      {
         cerr << "Fail to open " << fileName << " for writing!" << endl;
         exit(1);
      }
      file << aGroup.getName() << ';' << aGroup.getContact() << endl;
      file.close();
   }
}
