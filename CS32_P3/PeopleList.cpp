//
//  main.cpp
//  Project 3
//
//  Created by Vignesh Balasundaram on 7/26/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
#include <string>
#include "PeopleList.h"

PeopleList::PeopleList()          // Create an empty List
{
    head = nullptr;
}

PeopleList::~PeopleList()         // Destructor
{
    while (!empty())
    {
        Person* trail;
        trail = head;
        head = head->next;
        trail->next = nullptr;
        delete trail;
        trail = nullptr;
    }
}

//COPY CONSTRUCTOR
//copies the list to the one in the argument
PeopleList::PeopleList(const PeopleList& aList)
{
    if (aList.head == NULL)         //if empty list, then new empty list is created
        head = NULL;
    else
    {
        head = new Person;          //sets the first person to the head
        head->setValue(aList.head->getValue());
        head->setName(aList.head->getFirstName(), aList.head->getLastName());
        
        Person* trail = head;
        for (Person* original = aList.head->next; original != nullptr; original = original->next)
        {       //goes through original until NULL and creates identical Person nodes
            trail->next = new Person;
            trail = trail->next;
            trail->setValue(original->getValue());
            trail->setName(original->getFirstName(), original->getLastName());
        }
        trail->next = nullptr;      //finally sets the last Person node pointing to NULL
    }
}

//ASSIGNMENT OPERATOR
PeopleList& PeopleList::operator = (const PeopleList& rhs)
{
    
    if (&rhs != this)
    {
        Person* trail;
        
        while (head != nullptr)
        {
            trail = head;
            head = head->next;
            delete trail;
        }
        
        if (rhs.head == nullptr)
            head = nullptr;
        else
        {
            Person* temp = rhs.head;
            while (temp != nullptr)
            {
                std::string first = temp->getFirstName();
                std::string last = temp->getLastName();
                InfoType val = temp->getValue();
                add(first, last, val);
                temp = temp->next;
            }
        }
    }
    return *this;
}

//EMPTY FUNCTION
// Return true if the list is empty, otherwise false.
bool PeopleList::empty() const
{
    if (head==nullptr)                  //checks if head is NULL (meaning list is empty)
        return true;
    else
        return false;
}

//SIZE OF LIST FUNCTION
//RETURNS THE NUMBER OF ELEMENTS IN THE LINKED LIST
int PeopleList::size() const
{
    int count=0;
    Person* trail = head;
    while (trail!=nullptr)
    {
        count++;                        //increases the count every time the pointer does not point to NULL
        trail = trail->next;
    }
    return count;                       //returns count, or the number of elements in the list
}

//ADD FUNCTION
//adds a person node to the linked list
bool PeopleList::add(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
    if (head==nullptr)                      //checks if list is empty
    {
        Person* first = new Person(firstName, lastName, value);     //if list is empty, new Person gets created
        head = first;
        first->next = nullptr;
        first->last = nullptr;
        return true;
    }
    else                     //if list is not empty, checks to make sure not a duplicate name
    {
        Person* trail = head;
        while (trail!=nullptr)
        {
            if (lastName > trail->getLastName() && trail->next == nullptr)  //checks if name goes at the very end of the array
            {
                Person* add1 = new Person (firstName, lastName, value);
                add1->next = nullptr;                       //if at the end of the array, next points to NULL
                add1->last = trail;
                trail->next = add1;
                return true;
            }
            
            if (trail->getFirstName() == firstName && trail->getLastName() == lastName) //checks to make sure not a duplicate name
                return false;
            else if (lastName < trail->getLastName())   //if last name is less (or higher alphabetically) then the new Person gets added earlier in the list
            {
                Person* add1 = new Person (firstName, lastName, value);
                add1->next = trail;
                add1->last = trail->last;
                if (trail->last == nullptr)             //checks to make sure this is not the very first Person in the linked list
                {
                    head = add1;
                    trail->last = add1;
                }
                else
                {
                    trail->last->next=add1;
                    trail->last=add1;
                }
                return true;
            }
            else if (lastName == trail->getLastName())  //if the last names are the same, then moves on to first names
            {                                           //same checks as last name are going to be performed except with first name
                if (firstName > trail->getFirstName() && trail->next == nullptr)
                {
                    Person* add1 = new Person (firstName, lastName, value);
                    add1->next = nullptr;
                    add1->last = trail;
                    trail->next = add1;
                    return true;
                }
                else if (firstName < trail->getFirstName())
                {
                    Person* add1 = new Person(firstName, lastName, value);
                    add1->next = trail;
                    add1->last = trail->last;
                    
                    if (trail->last == nullptr)
                    {
                        head = add1;
                        trail->last = add1;
                    }
                    else
                    {
                        trail->last->next=add1;
                        trail->last=add1;
                    }
                    return true;
                }
            }
            trail = trail->next;
        }
    }
    return false;
}

//CHANGE FUNCTION
//changes the value of the name in the list
bool PeopleList::change(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
    Person* trail;
    trail = head;
    while (trail != nullptr)
    {
        if (trail->getFirstName() == firstName && trail->getLastName() == lastName)             //finds the Person on the list with the same name
        {
            trail->setValue(value);                                                             //sets the value of that person to the value given
            return true;
        }
        trail = trail->next;
    }
    return false;                                                                               //if no name is found, returns false
}

//ADD OR CHANGE FUNCTION
//either adds or changes a name in the list
bool PeopleList::addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
    if (change(firstName, lastName, value))             //runs the change function, and if it returns true (meaning the value of the name was changed) it returns true
        return true;
    else                                                //if change returns false, then the Person is added to the list and returns true
    {
        add(firstName, lastName, value);
        return true;
    }
}

//REMOVE FUNCTION
//removes a name from the list
bool PeopleList::remove(const std::string& firstName, const std::string& lastName)
{
    Person* trail;
    trail = head;
    while (trail != nullptr)
    {
        if (trail->getFirstName() == firstName && trail->getLastName() == lastName)             //searches for a matching name
        {
            if (trail==head)
            {
                trail->next->last = nullptr;
                head = trail->next;
            }
            else
            {
                if (trail->next!=nullptr)
                    trail->next->last = trail->last;                                                //changes the last pointer of the next person to the last person
                if (trail->last!=nullptr)
                    trail->last->next = trail->next;                                                //changes the next pointer of the last person to the next person
            }
                delete trail;                                                                       //Person is deleted
            trail = nullptr;
            return true;
        }
        trail = trail->next;
    }
    return false;
}

//CONTAINS FUNCTION
//checks if the list contains a certain Person
bool PeopleList::contains(const std::string& firstName, const std::string& lastName) const
{
    Person* trail;
    trail = head;
    while (trail != nullptr)
    {
        if (trail->getFirstName() == firstName && trail->getLastName() == lastName)             //checks first and last name and if found returns true
        {
            return true;
        }
        trail = trail->next;                                                                    //goest through the list checking names
    }
    return false;                                                       //returns false if no name is found
}

//LOOKUP FUNCTION
//finds the value of a certain name
bool PeopleList::lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const
{
    Person* trail;
    trail = head;
    while (trail != nullptr)
    {
        if (trail->getFirstName() == firstName && trail->getLastName() == lastName)
        {
            value = trail->getValue();                                  //sets the value of the name found to the value
            return true;
        }
        trail = trail->next;                                            //goes through the list checking names
    }
    return false;                                                       //if no name is found, no change is made to the value parameter and returns false
}

//GET FUNCTION
//finds the specified person and gets the first name, last name, and value of that person
bool PeopleList::get(int i, std::string& firstName, std::string& lastName, InfoType& value) const
{
    int count = 0;
    if (0<=i && i<size())
    {
        Person* trail = head;
        while (count!=i)                            //goes through the list increasing count until it matches the value given
        {
            if (trail == nullptr)                    //if i is ever beyond the length of the list, then returns false
                return false;
            trail=trail->next;
            count++;
        }
        if (count==i)                               //if specified person is found
        {
            firstName = trail->getFirstName();      //gets first name
            lastName = trail->getLastName();        //gets last name
            value = trail->getValue();              //gets value
            return true;
        }
    }
    return false;                                   //should never reach here
}

//SWAP FUNCTION
//swaps the contents of one list with the other
void PeopleList::swap(PeopleList& other)
{
    Person* temp = head;
    head = other.head;
    other.head = temp;
}


//NON-MEMBER FUNCTIONS

//COMBINE FUNCTION
//combines two lists
bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result)
{
    std::string fnameA, fnameB, lnameA, lnameB;
    InfoType vA, vB;
    PeopleList A, B, C;
    A = m1;
    B = m2;
    
    result = C;         //empties result function in case it wasn't empty before
    
    bool check = true;
    
    for (int i=0; i<A.size(); i++)
    {
        for (int j=0; j<B.size(); j++)
        {
            A.get(i, fnameA, lnameA, vA);
            B.get(j, fnameB, lnameB, vB);
            
            if (fnameA == fnameB && lnameA == lnameB)           //goes through to find any duplicates
            {
                if (vA != vB)
                {
                    A.remove(fnameA, lnameA);                   //if duplicate is found and the values don't match
                    B.remove(fnameA, lnameA);                   //person is removed from both lists
                    check = false;                              //check bool tracks if same person with different value is found in both lists
                }
                else
                    A.remove(fnameA, lnameA);                   //if values do match, person is only removed from one list
            }
        }
    }
    
    for (int a=0; a<A.size(); a++)                      //now the lists are added together
    {
        A.get(a, fnameA, lnameA, vA);
        result.add(fnameA, lnameA, vA);
    }
    for (int b=0; b<B.size(); b++)
    {
        B.get(b, fnameB, lnameB, vB);
        result.add(fnameB, lnameB, vB);
    }
    
    return check;                                       //check is returned either true or false depending on if match is found
}

//SEARCH FUNCTION
//makes a list of persons that match the search terms
void psearch (const std::string& fsearch, const std::string& lsearch, const PeopleList& p1, PeopleList& result)
{
    result = PeopleList();
    std::string first, last;
    InfoType val;
    
    for (int i=0; i<p1.size(); i++)
    {
        p1.get(i, first, last, val);
        if (first == fsearch && lsearch == "*")         //for all the last names that are wild cards
        {
            result.add(first, last, val);
        }
        else if (last == lsearch && fsearch == "*")     //for all the first names that are wild cards
        {
            result.add(first, last, val);
        }
        else if (lsearch == "*" && fsearch == "*")      //for a situation in which both names are wild cards
        {
            result.add(first, last, val);
        }
    }
}

////PERSON FUNCTIONS//////

//constructors

//DEFAULT CONSTRUCTOR
//sets first and last name as blank and the value to empty
PeopleList::Person::Person()
{
    setName("", "");
    setValue(NULL);
}

//CONSTRUCTOR WITH NAME AND VALUE
//sets first and last name, and value as given
PeopleList::Person::Person(const std::string& fName, const std::string& lName, const InfoType& val)
{
    setName(fName, lName);
    setValue(val);
}

//CONSTRUCTOR WITH ONLY NAME
//sets first and last name as given, and value to empty
PeopleList::Person::Person(const std::string& fName, const std::string& lName)
{
    setName(fName, lName);
    setValue(NULL);
}

//accessors
InfoType PeopleList::Person::getValue()                 //returns the value
{
    return value;
}
std::string PeopleList::Person::getFirstName()          //returns the first name
{
    return firstName;
}
std::string PeopleList::Person::getLastName()           //returns the last name
{
    return lastName;
}

//mutators
void PeopleList::Person::setName (const std::string& fName, const std::string& lName)       //sets the name to given
{
    firstName = fName;
    lastName = lName;
}
void PeopleList::Person::setValue (const InfoType& val)         //sets the value to given
{
    value = val;
}


