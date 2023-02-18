//*****************************************************************************
// Name: queue.h
// Descrtiption: This is the header file for the Queue class object.
//*****************************************************************************
#ifndef QUEUE_H
#define QUEUE_H
#include "group.h"
#include <fstream>

class Queue
{
public:
   Queue();
   Queue(const Queue &aQueue);
   ~Queue();
   void enqueue(const Group &aGroup);
   bool dequeue();
   bool peek(Group &aGroup) const;
   int getSize() const;
   bool isEmpty() const;
   const Queue &operator=(const Queue &queueSrc);
   friend ostream &operator<<(ostream &out, const Queue &aQueue);
   void loadFromFile(const char *fileName);
   void saveToFile(const char *fileName) const;

private:
   struct Node
   {
      Node()
      {
         data = nullptr;
         next = nullptr;
         queueNum = 0;
      }
      Node(const char *name, int size, char request, bool contactInput, const char *contact, int queueNum)
      {
         data = new Group(name, size, request, contactInput, contact);
         next = nullptr;
         this->queueNum = queueNum;
      }
      Node(const Group &aGroup, int queueNum) : data(nullptr), next(nullptr)
      {
         data = new Group(aGroup);
         this->queueNum = queueNum;
      }
      ~Node()
      {
         delete data;
         data = nullptr;
         next = nullptr;
         queueNum = 0;
      }
      Group *data;
      Node *next;
      int queueNum;
   };
   Node *front, *back;
   int size;
   void destroy();
   void updateQueuePos(Node *&, const int);
};

#endif