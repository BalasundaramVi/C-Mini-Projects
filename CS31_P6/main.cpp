//
//  main.cpp
//  Project 6
//
//  Created by Vignesh Balasundaram on 5/29/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
using namespace std;

// return true if two C strings are equal
bool match(const char str1[], const char str2[])
{
    while (*str1 != 0  &&  *str2 != 0)  // zero bytes at ends
    {
        if (*str1 != *str2)  // compare corresponding characters
            return false;
        str1++;            // advance to the next character
        str2++;
    }
    return *str1 == *str2;   // both ended at same time?
}

int main()
{
    char a[10] = "pointed";
    char b[10] = "pointer";
    
    if (match(a,b))
        cout << "They're the same!\n";
}
