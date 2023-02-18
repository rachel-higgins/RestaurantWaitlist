//*****************************************************************************
// Name: group.cpp
// Descrtiption: This is the executable file for the Group class object.
//*****************************************************************************
#include "group.h"

// name: Group()
// descriptipn: this function is the constructor.
// input: none
// output: none
Group::Group() : name(nullptr), size(0), request(0), contactInput(false), contact(nullptr) {}

// name: Group(const char*, int, char, bool)
// descriptipn: this function is a param constructor.
// input: none
// output: none
Group::Group(const char *name, int size, char request, bool contactInput, const char *contact) : name(nullptr), contact(nullptr)
{
   init(name, size, request, contactInput, contact);
}

// name: Group(const char*, int, char, bool)
// descriptipn: this function is a param constructor
// input: none
// output: none
Group::Group(const char *name, bool contactInput, const char *contact) : name{nullptr}, contact(nullptr)
{
   init(name, 0, 0, contactInput, contact);
}

// name: Group(const Group*)
// descriptipn: this function is a copy constructor.
// input: none
// output: none
Group::Group(const Group &aGroup) : name(nullptr), contact(nullptr)
{
   init(aGroup.name, aGroup.size, aGroup.request, aGroup.contactInput, aGroup.contact);
}

// name: init(const char*, int, char, bool)
// descriptipn: this function initializes all the private members.
// input: none
// output: none
void Group::init(const char *name, int size, char request, bool contactInput, const char *contact)
{
   setName(name);
   setSize(size);
   setRequest(request);
   setContactInput(contactInput);
   setContact(contact);
}

// name: ~Group()
// descriptipn: this function is the destructor
// input: none
// output: none
Group::~Group()
{
   if (this->name)
   {
      delete[] this->name;
   }
   if (this->contact)
   {
      delete[] this->contact;
   }
   this->name = nullptr;
   this->contact = nullptr;
}

// name: setName(const char*)
// descriptipn: this function sets name.
// input: none
// output: none
void Group::setName(const char *name)
{
   if (this->name)
   {
      delete[] this->name;
      this->name = nullptr;
   }
   this->name = new char[strlen(name) + 1];
   strcpy(this->name, name);
}

// name: *getName() const
// descriptipn: this function returns name.
// input: none
// output: none
const char *Group::getName() const
{
   return name;
}

// name: setSize(int)
// descriptipn: this function sets size.
// input: none
// output: none
void Group::setSize(int size)
{
   this->size = size;
}

// name: getSize() const
// descriptipn: this function returns size.
// input: none
// output: none
int Group::getSize() const
{
   return size;
}

// name: setRequest(char)
// descriptipn: this function sets request.
// input: none
// output: none
void Group::setRequest(char request)
{
   this->request = request;
}

// name: getRequest() const
// descriptipn: this function returns request.
// input: none
// output: none
char Group::getRequest() const
{
   return request;
}

// name: setcontactInput(bool)
// descriptipn: this function sets contactInput.
// input: none
// output: none
void Group::setContactInput(bool contactInput)
{
   this->contactInput = contactInput;
}

// name: getcontactInput() const
// descriptipn: this function returns contactInput.
// input: none
// output: none
bool Group::getContactInput() const
{
   return contactInput;
}

// name: setContact(const char*)
// description: this function sets the contact private member.
// input: none
// output: none
void Group::setContact(const char *contact)
{
   if (this->contact)
   {
      delete[] this->contact;
      this->contact = nullptr;
   }
   this->contact = new char[strlen(contact) + 1];
   strcpy(this->contact, contact);
}

// name: getContact() const
// description: this function returns contact.
// input: none
// output: none
const char *Group::getContact() const
{
   return contact;
}

// name: &operator=(const Group &aGroup)
// descriptipn: this function is copy assignment operator function.
// input: none
// output: none
const Group &Group::operator=(const Group &aGroup)
{
   if (this == &aGroup)
   {
      return *this;
   }
   init(aGroup.name, aGroup.size, aGroup.request, aGroup.contactInput, aGroup.contact);
   return *this;
}

// name: &operator<<(ostream &out, const Group &aGroup)
// descriptipn: this function is an ouput assignment operator function.
// input: none
// output: none
ostream &operator<<(ostream &out, const Group &aGroup)
{
   out << aGroup.name << "\t  ";
   if (aGroup.size != 0)
   {
      out << aGroup.size << "\t   ";
   }
   out << aGroup.request << "\t "
       << aGroup.contact << "\t";
   if (aGroup.contactInput)
   {
      out << "Y" << endl;
   }
   else
   {
      cout << "N" << endl;
   }
   return out;
}