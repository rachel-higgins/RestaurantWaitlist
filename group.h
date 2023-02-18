//*****************************************************************************
// Name: group.h
// Descrtiption: This is the header file for the Group class object.
//*****************************************************************************
#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <cstring>
using namespace std;

class Group
{
public:
   Group();
   Group(const char *, int, char, bool, const char *);
   Group(const char *, bool, const char *);
   Group(const Group &);
   ~Group();
   void setName(const char *);
   const char *getName() const;
   void setSize(int);
   int getSize() const;
   void setRequest(char);
   char getRequest() const;
   void setContactInput(bool);
   bool getContactInput() const;
   void setContact(const char *);
   const char *getContact() const;
   const Group &operator=(const Group &aGroup);
   friend ostream &operator<<(ostream &out, const Group &aGroup);

private:
   char *name;
   int size;
   char request;
   bool contactInput;
   char *contact;
   void init(const char *, int, char, bool, const char *);
};

#endif