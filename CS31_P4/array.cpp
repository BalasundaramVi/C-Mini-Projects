//
//  main.cpp
//  Project 4
//
//  Created by Vignesh Balasundaram on 5/11/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int enumerate (const string a[], int n, string target); // line 30
int locate(const string a[], int n, string target);// line 50
bool locateSequence(const string a[], int n, string target, int& begin, int& end); //line 65
int locationOfMin(const string a[], int n); // line 93
int moveToEnd(string a[], int n, int pos); // line 113
int moveToBeginning(string a[], int n, int pos); // line 130
int locateDifference(const string a1[], int n1, const string a2[], int n2); // line 145
int eliminateDups(string a[], int n); //lin 179
bool subsequence(const string a1[], int n1, const string a2[], int n2); // line 215
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max); // line 241
int divide(string a[], int n, string divider); //line 294

int main () {
    cout << "I hope I get an A on this project!" << endl;
}

// ENUMERATE FUNCTION
int enumerate (const string a[], int n, string target)
{
    if (n==0)                   //failsafe
        return 0;
    if (a[n-1]=="")             //failsafe
        return -1;
    if (n<0)                    //failsafe
    {
        return -1;
    }
    int count=0;
    for (int i=0; i < n; i++)   //counts number of strings equal to target
    {
        if (a[i]==target)
            count++;
    }
    return count;
}

// LOCATE FUNCTION
int locate(const string a[], int n, string target)
{
    if (a[n-1]=="")             //failsafe
        return -1;
    if (n<0)                    //failsafe
        return -1;
    for (int i=0; i < n; i++)   //locates target
    {
        if (a[i] == target)
            return i;
    }
    return -1;
}

// LOCATE SEQUENCE FUNCTION
bool locateSequence(const string a[], int n, string target, int& begin, int& end)
{
    if (a[n-1]=="")             //failsafe
        return -1;
    if (n<0)                    //failsafe
        return false;
    for (int i=0; i<n; i++)     //finds target
    {
        if (a[i] == target)
        {
            begin = i;
            for (int k = i; k<n; k++) // finds end of target
            {
                if (a[k] == target)
                    continue;
                else
                {
                    end = k-1;
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

// LOCATION OF MINIMUM FUNCTION
int locationOfMin(const string a[], int n)
{
    if (a[n-1]=="")             //failsafe
        return -1;
    string smallest = a[0];
    int position = 0;
    if (n<0)                    //failsafe
        return -1;
    for (int i=0; i<n; i++)
    {
        if (a[i] < smallest)    //finds smallest string
        {
            smallest=a[i];
            position = i;
        }
    }
    return position;
}

// MOVE TO END FUNCTION
int moveToEnd(string a[], int n, int pos)
{
    if (a[n-1]=="")             //failsafe
        return -1;
    string end;
    end = a[pos];               //copies the string that needs to be moved to end
    
    for (int i = pos;i<(n-1);i++)   //shifts all strings one to the left
    {
        a[i]=a[i+1];
    }
    a[n-1] = end;
    return pos;
}

// MOVE TO BEGINNING FUNCTION
int moveToBeginning(string a[], int n, int pos)
{
    if (a[n-1]=="")             //failsafe
        return -1;
    string begin;
    begin = a[pos];             //copies the string that needs to be moved to the beginning
    
    for (int i = pos; i>0 ;i--)     //shifts all strings one to the right
    {
        a[i]=a[i-1];
    }
    a[0] = begin;
    return pos;
}

// LOCATE DIFFERENCE FUNCTION
int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (a1[n1-1]=="" || a2[n2-1]=="")       //failsafe
        return -1;
    if (n1 < 0 || n2 < 0)                   //failsafe
        return -1;
    if (n1>=n2)                             //figures which string to use as base string to compare
    {
        for (int i = 0; i<n1; i++)
        {
            if (i == n2)
                return n2;
            if (a1[i]!=a2[i])               //finds difference
            {
                return i;
            }
        }
    }
    else                                    //figures which string to use as base string to compare
    {
        for (int i = 0; i<n2; i++)
        {
            if (i == n1)
                return n1;
            if (a1[i]!=a2[i])               //finds difference
            {
                return i;
            }
        }
    }
    return 0;
}

// ELIMINATE DUPLICATES FUNCTION
int eliminateDups(string a[], int n)
{
    if (a[n-1]=="")                         //failsafe
        return -1;
    if (n<0)                                //failsafe
        return -1;
    for (int i = 0; i<n; i++)               //replaces all duplicates with space character
    {
        if (a[i]==a[i+1])
        {
            a[i] = " ";
        }
    }
    
    int count;
    
    for (int j=0; j<n; j++)                 //shifts all characters one to left if previous character is a space character
    {
        if (a[j] == " ")
        {
            for (int k=j+1; k<n; k++)
                if (a[k]!=" ")
                {
                    a[j] = a[k];
                    a[k] = " ";
                    count++;
                    break;
                }
        }
        else                                //otherwise continues
            count++;
    }
    return count;
}

// SUB SEQUENCE FUNCTION
bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (a1[n1-1]=="" || a2[n2-1]=="")       //failsafe
        return -1;
    if (n2 == 0)                            //failsafe
        return true;
    for (int i=0; i<n2;)                    //finds start of subsequence
    {
        for (int j=0; j<n1;j++)
        {
            if (a2[i]==a1[j])
            {
                i++;
            }
            if (j==(n1-1) && i!=n2)         //failsafe
                return false;
        }
        if (i==n2)                          //makes sure entire subsequence exists
        {
            return true;
        }
    }
    return false;
}

// MAKE MERGER FUNCTION
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    for (int i1=0; i1<(n1-1); i1++)         //failsafe
    {
        if (a1[i1]>a1[i1+1])
            return -1;
    }
    for (int i2=0; i2<(n2-1); i2++)         //failsafe
    {
        if (a2[i2]>a2[i2+1])
            return -1;
    }
    if ((n1+n2)>max)                        //failsafe
        return -1;
    
    int place=0;
    for (int i=0; i<n1; i++)                //places string 1 at the beggining of string 'result'
    {
        result[place]=a1[i];
        place++;
    }
    for (int j=0; j<n2; j++)                //places string 2 after string 1 in string 'result'
    {
        result[place]=a2[j];
        place++;
    }
    
    string lowest;
    string highest;
    
    for (int count=0; count<(n1+n2); count++)   //alphabetizes string 'result'
    {
        for (int i=count; i<(n1+n2); i++)
        {
            if (lowest > result[i])
            {
                lowest = result[i];
                result[i] = result[count];
                result[count] = lowest;
            }
            if (highest < result[i])
            {
                highest = result[i];
            }
        }
        lowest = highest;
    }
    
    return (n1+n2);
}


// DIVIDE FUNCTION
int divide(string a[], int n, string divider)
{
    if (n<0)                                //failsafe
        return -1;
    string lowest = a[0];
    string highest = "";
    
    for (int count=0; count<n; count++)     //alphabetizes the string
    {
        for (int i=count; i<n; i++)
        {
            if (lowest > a[i])
            {
                lowest = a[i];
                a[i] = a[count];
                a[count] = lowest;
            }
            if (highest < a[i])
            {
                highest = a[i];
            }
        }
        lowest = highest;
    }

    for (int j=0; j<n; j++)                 //finds where the divider would land in the new alphabetized string
    {
        if (a[j]>=divider)
            return j;                       //returns position where divide happens
    }
    return 0;
}
