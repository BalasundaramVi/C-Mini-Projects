//
//  PeopleList.h
//  Project 3
//
//  Created by Vignesh Balasundaram on 7/26/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#ifndef PeopleList_h
#define PeopleList_h

#include <iostream>
#include <string>

typedef int InfoType;

class PeopleList
{
public:
    PeopleList();          // Create an empty List
    
    ~PeopleList();         // Destructor
    
    PeopleList(const PeopleList& aList);
    
    PeopleList& operator = (const PeopleList& rhs);
        
    bool empty() const;    // Return true if the list is empty, otherwise false.
    
    int size() const;      // Return the number of elements in the linked list.
    
    bool add(const std::string& firstName, const std::string& lastName, const InfoType& value);
    
    bool change(const std::string& firstName, const std::string& lastName, const InfoType& value);
    
    bool addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value);
    
    bool remove(const std::string& firstName, const std::string& lastName);
    
    bool contains(const std::string& firstName, const std::string& lastName) const;
    
    bool lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const;
    
    bool get(int i, std::string& firstName, std::string& lastName, InfoType& value) const;
    
    void swap(PeopleList& other);
    
    
private:
    class Person
    {
    public:
        //constructors
        Person();
        Person(const std::string& fName, const std::string& lName, const InfoType& val);
        Person(const std::string& fName, const std::string& lName);
        
        //accessors
        InfoType getValue();
        std::string getFirstName();
        std::string getLastName();
        Person* next;
        Person* last;
        
        //mutators
        void setName (const std::string& fName, const std::string& lName);
        void setValue (const InfoType& val);
        
    private:
        std::string firstName;
        std::string lastName;
        InfoType value;
        
    };

    Person* head;
};

bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result);

void psearch (const std::string& fsearch, const std::string& lsearch, const PeopleList& p1, PeopleList& result);

#endif /* PeopleList_h */
