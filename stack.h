//*****************************************************************************
// Name: stack.h
// Descrtiption: This is the header file for the Stack class object.
//*****************************************************************************
#ifndef STACK_H
#define STACK_H
#include "group.h"
#include <fstream>

class Stack
{
public:
   Stack();
   Stack(const Stack &aStack);
   ~Stack();
   void push(const Group &aGroup);
   bool pop(Group &aGroup);
   bool peek(Group &aGroup) const;
   int getSize() const;
   bool isEmpty() const;
   const Stack &operator=(const Stack &srcStack);
   friend ostream& operator<<(ostream &out, const Stack &srcStack);
   void loadFromFile(const char *fileName);
   void saveToFile(const char *fileName) const;

private:
   Group **aStack;
   const static int INIT_CAP = 3;
   const static int GROWTH_FACTOR = 2;
   int currCapacity;
   int top;
   void destroy();
   void expand();
};

#endif