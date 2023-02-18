//*****************************************************************************
// Name: stack.cpp
// Descrtiption: This is the executable file for the Stack class object.
//*****************************************************************************
#include "stack.h"

// name: Stack()
// description: this function is the constructor.
// input: none
// output: none
Stack::Stack() : top(0)
{
   currCapacity = INIT_CAP;
   aStack = new Group *[currCapacity];
   for (int i = 0; i < currCapacity; i++)
   {
      aStack[i] = nullptr;
   }
}

// name: Stack(const Stack &aStack)
// description: this function is param constructor.
// input: none
// output: none
Stack::Stack(const Stack &aStack) : aStack(nullptr), top(0)
{
   *this = aStack;
}

// name: ~Stack()
// description: this function is the destructor.
// input: none
// output: none
Stack::~Stack()
{
   destroy();
}

// name: destroy()
// description: this function deletes every element of the Group **array.
// input: none
// output: none
void Stack::destroy()
{
   for (int i = 0; i < top; i++)
   {
      if (aStack[i])
      {
         delete aStack[i];
      }
   }
   if (aStack)
   {
      delete[] aStack;
   }
}

// name: expand()
// description: this function creates a new Group **array with additional 
// space and copies elements from the current stack to the larger stack 
// keeping them in their original positions.
// input: none
// output: none
void Stack::expand()
{
   currCapacity *= GROWTH_FACTOR;
   Group **tempStack = new Group *[currCapacity];
   for (int i = 0; i < top; i++)
   {
      tempStack[i] = aStack[i];
   }
   delete[] aStack;
   aStack = tempStack;
}

// name: operator=(const Stack &aGroup)
// description: this function is the copy assignment operator function.
// input: none
// output: none
const Stack &Stack::operator=(const Stack &srcStack)
{
   if (this == &srcStack)
   {
      return *this;
   }
   destroy();
   top = srcStack.top;
   currCapacity = srcStack.currCapacity;
   aStack = new Group *[currCapacity];
   for (int i = 0; i < top; i++)
   {
      aStack[i] = new Group(*(srcStack.aStack[i]));
   }
   return *this;
}

// name: operator<<(ostream &out, const Stack &srcStack))
// description: this function is the output assignment operator function.
// input: none
// output: none
ostream &operator<<(ostream &out, const Stack &srcStack)
{
   out << "Displaying the stack..." << endl
       << endl
       << "Order\tName\t\t Phone #" << endl
       << "------------------------------------------" << endl;
   for (int i = 0; i < srcStack.top; i++)
   {
      out << i + 1 << ". \t"
          << *(srcStack.aStack[i]);
   }
   return out;
}

// name: push(const Group&)
// description: this function adds new elements at the top of the stack array.
// input: none
// output: none
void Stack::push(const Group &aGroup)
{
   if (currCapacity == top)
   {
      expand();
   }
   aStack[top] = new Group(aGroup.getName(), aGroup.getContactInput(), aGroup.getContact());
   top++;
}

// name: pop(Group &)
// description: this function removes the newest element at the top of the 
// stack array and returns true or if the array is empty then it returns 
// false. The Group element being removed is passed by reference back to the 
// caller program.
// input: none
// output: none
bool Stack::pop(Group &aGroup)
{
   if (top == 0)
   {
      return false;
   }
   aGroup = *(aStack[top - 1]);
   delete aStack[top - 1];
   aStack[top - 1] = nullptr;
   top--;
   return true;
}

// name: peek(Group &aGroup) const
// description: this function returns true if there is an element at the top 
// of the stack array and passes it by reference back to the caller program.
// input: none
// output: none
bool Stack::peek(Group &aGroup) const
{
   if (isEmpty())
   {
      return false;
   }
   aGroup = *(aStack[top -1]);
   return true;
}

// name: isEmpty() const
// description: this function returns the bool value of top == 0.
// input: none
// output: none
bool Stack::isEmpty() const
{
   return top == 0;
}

// name: getSize() const
// description: this function returns top.
// input: none
// output: none
int Stack::getSize() const
{
   return top;
}

// name: loadFromFile
// description: this function opens a file and uses the data in each line item 
// to create group elements and push them onto the stack.
// input: none
// output: none
void Stack::loadFromFile(const char *fileName)
{
   fstream file;
   const int MAX_CHAR = 101;
   char currName[MAX_CHAR + 1];
   char currContact[MAX_CHAR + 1];

   file.open(fileName, ios::in);
   if (!file)
   {
      cerr << "Fail to open " << fileName << " for reading!" << endl;
      exit(1);
   }

   file.get(currName, MAX_CHAR, ';');

   while (!file.eof())
   {
      file.ignore(1);
      file.get(currContact, MAX_CHAR, '\n');
      file.ignore(1);
      Group currGroup(currName, true, currContact);
      push(currGroup);
      file.get(currName, MAX_CHAR, ';');
   }
   file.close();
}

// name: saveToFile
// description: this function opens a file in truncate mode. It writes into 
// the file the data from each element in the stack array.
// input: none
// output: none
void Stack::saveToFile(const char *fileName) const
{
   ofstream file;
   file.open(fileName, ios::trunc);
   if (!file)
   {
      cerr << "Fail to open " << fileName << " for writing!" << endl;
      exit(1);
   }
   for (int i = 0; i < top; i++)
   {
      file << aStack[i]->getName() << ';' << aStack[i]->getContact() << endl;
      
   }
   file.close();
}