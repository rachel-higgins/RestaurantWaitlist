//*****************************************************************************
// Author: Rachel Higgins
// Date: October 24, 2022
// Course: CS260 Data Structures
// Assignment: C++ Project Assignment 2
// Descrtiption: main() is the test program for queue.cpp and stack.cpp. This 
// program is a menu driven program that manages a queue of a restaurant's 
// waitlist and a stack of the restaurant's promotional contact list.
// Input: Queue myKitchen, Stack myKitchenPromoList, ofstream file, char 
// reservation[], char currPromoList[], char contactList[], char promotion[], 
// int option.
// Output: Queue myKitchen, Stack myKitchenPromoList, char promotion[] (promo 
// text message).
//*****************************************************************************
#include <iostream>
#include "group.h"
#include "queue.h"
#include "stack.h"
using namespace std;

const int MAX_CHAR = 100;

int menu();
void add(Queue &);
void newPromotion(char *);
void openFile(ofstream &, const char fileName[]);

int main()
{
   Queue myKitchen;
   Stack myKitchenPromoList;
   ofstream file;
   char reservations[] = "reservations.txt";
   char currPromoList[] = "currPromoList.txt";
   char contactList[] = "contactList.txt";
   char promotion[MAX_CHAR + 1] = {};
   int option = 0;

   myKitchen.loadFromFile(reservations); // loading reservations to queue
   myKitchenPromoList.loadFromFile(currPromoList); // loading previous stack
   
   openFile(file, contactList); // Open file to store customer data after being removed from the stack

   while ((option = menu()) != 6)
   {
      Group aGroup;
      cin.ignore(101, '\n');
      switch (option)
      {
      case 1: // add group to queue
         add(myKitchen);
         break;
      case 2: // seat next group
         myKitchen.peek(aGroup);
         if (aGroup.getContactInput())
         {
            myKitchenPromoList.push(aGroup);
         }
         myKitchen.dequeue();
         break;
      case 3: // display queue list
         cout << "My Kitchen Waitlist" << endl;
         cout << myKitchen << endl;
         break;
      case 4: // display stack list
         cout << "My Kitchen Contact List" << endl;
         cout << myKitchenPromoList << endl;
         break;
      case 5: // send promo
         newPromotion(promotion);
         cout << endl
              << "Promotional Text: " << promotion << endl
              << endl;
         while (myKitchenPromoList.pop(aGroup))
         {
            cout << "Pop a group: " << aGroup;
            file << aGroup.getName() << ';' << aGroup.getContact() << endl;
            file.flush();
         }
         cout << endl;
         break;
      default:
         break;
      }
   }
   myKitchenPromoList.saveToFile(currPromoList); // saves current stack to a text file
   file.close();
   return 0;
}

// name: menu()
// description: this function displays a menu and gets input from the user.
// input: int option
// output: menu options as text
int menu()
{
   int option = 0;
   cout << "- My Kitchen Hostess Menu -" << endl;
   cout << "Select one of the following options:" << endl
        << "1. Add a new group" << endl
        << "2. Seat next group" << endl
        << "3. Display wait list" << endl
        << "4. Display contact list for promotional offers" << endl
        << "5. Send out a new promotional code" << endl
        << "6. Exit" << endl
        << "Enter option: ";
   cin >> option;
   cout << endl;
   return option;
}

// name: add()
// description: this function gets user input to create a new Group to add to 
// the queue.
// input: char currName[], char contact[], int size, char requestInput, char 
// contact UserInput, bool contactInput.
// output: user input requests
void add(Queue &aQueue)
{
   Group newGroup;
   char currName[MAX_CHAR + 1];
   char contact[MAX_CHAR + 1];
   int size = 0;
   char requestInput = 0;
   char contactUserInput = 0;
   bool contactInput = false;

   // getting group name
   cout << "Enter Group Name: ";
   cin.getline(currName, '\n');

   // getting group size
   cout << "Enter Group Size: ";
   cin >> size;

   // getting special requests
   cout << "Special Requests?" << endl;
   cout << "(H) High Chair\n(W) Wheel Chair\n(N) None\n";
   cout << "Enter option: ";
   cin >> requestInput;
   cin.ignore(MAX_CHAR, '\n');
   cout << "Enter phone #: ";
   cin.get(contact, MAX_CHAR, '\n');
   cout << "Would you like to recieve contactListal emails (Y/N)?: ";
   cin >> contactUserInput;
   cin.ignore(MAX_CHAR, '\n');
   cout << endl;
   if (contactUserInput == 'Y' || contactUserInput == 'y')
   {
      contactInput = true;
   }

   // setting the Group variables' w/ values
   newGroup.setContactInput(contactInput);
   newGroup.setName(currName);
   newGroup.setSize(size);
   newGroup.setRequest(requestInput);
   newGroup.setContact(contact);

   aQueue.enqueue(newGroup);
}

void newPromotion(char *promo)
{
   char promoType[MAX_CHAR + 1] = {};
   char promoCode[MAX_CHAR + 1] = {};

   // cout << "Enter Promotion: ";
   // cin.getline(promoType, MAX_CHAR, '\n');
   // cout << "Enter Promotion Code: ";
   // cin.getline(promoCode, MAX_CHAR, '\n');
   strcpy(promoType, "$5 off");    // for testing
   strcpy(promoCode, "HOLIDAY_5"); // for testing

   strcat(promo, "Get ");
   strcat(promo, promoType);
   strcat(promo, " at My Kitchen! Show this text during your next visit. CODE: ");
   strcat(promo, promoCode);
   strcat(promo, "\0");
}

// name: openFile()
// description: this function opens a file in append mode and displays an 
// error if file did not open successfully.
// input: none
// output: error message
void openFile(ofstream &file, const char fileName[])
{
   file.open(fileName, ios::app);
   if (!file)
   {
      cerr << "Fail to open " << fileName << " for writing!" << endl;
      exit(1);
   }
}