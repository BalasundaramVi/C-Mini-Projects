//
//  main.cpp
//  Project 3
//
//  Created by Vignesh Balasundaram on 4/28/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "graphlib.h"
#include <iostream>
#include <cctype>
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int BG = 0;
const int FG = 1;

int executeCommands(string commandString, char& plotChar, int& mode, int& badPos);
bool plotHorizontalLine(int& p_R, int& p_C, int distance, char ch, int fgbg);
bool plotVerticalLine(int& p_R, int& p_C, int distance, char ch, int fgbg);
bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg);


int main()
{   clearGrid();
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = executeCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot execute command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "executeCommands returned " << status << "!" << endl;
        }
    }
}


int executeCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int r=1; // r = row
    int c=1; // c = column
    
    int travel; // keeps track of length travelled (distance along axis)
    
    for (int i=0; i<commandString.length(); i++)
    {
        int original = i; // keeps track of start of command even if command is multiple characters
        if (commandString[i] != 'H' && commandString[i] != 'h'
            && commandString[i] != 'V' && commandString[i] != 'v'
            && commandString[i] != 'F' && commandString[i] != 'f'
            && commandString[i] != 'B' && commandString[i] != 'b'
            && commandString[i] != 'C' && commandString[i] != 'c')
        {
        badPos = i;
        return 1;
        }
        
        if (commandString[i] == 'C' || commandString[i] == 'c') // THE CLEAR COMMAND
        {
            for (int r = 1; r <= 20; r++)
                for (int c = 1; c <= 30; c++)
                    setChar(r,c, ' ');
            r = 1;
            c = 1;
            mode = FG;
            plotChar = '*';
        }
        
        else if (commandString[i] == 'F' || commandString[i] == 'f') // The Foreground command
        {
            if (!isprint(commandString[i+1]))
            {
                badPos = i+1;
                return 1;
            }
            else
            {
                mode = FG;
                plotChar = commandString[i+1];
                i++;
            }
        }
       
        else if (commandString[i] == 'B' || commandString[i] == 'b') // The Background command
        {
            if (!isprint(commandString[original+1]))
            {
                badPos = i+1;
                return 1;
            }
            else
            {
                mode = BG;
                plotChar = commandString[original+1];
                i++;
            }
        }
        
        else if (commandString[i] == 'H' || commandString[i] == 'h' ||
                 commandString[i] == 'V' || commandString[i] == 'v') // To find 'travel' (distance)
        {
            if ((int(commandString[i+1]))>= 48 && (int(commandString[i+1]) <= 57))
            {
                if (int(commandString[i+2]) >= 48 && int(commandString[i+2]) <= 57)
                {
                    travel = (int(commandString[i+1])-48) * 10;
                    travel += (int(commandString[i+2])-48);
                    i+=2;
                }
                else
                {
                    travel = (int(commandString[i+1])-48);
                    i++;
                }
            }
            
            else if (int(commandString[i+1])==45) // in case distance is negative
            {
                if ((int(commandString[i+2]) >= 48 && int(commandString[i+2]) <= 57))
                {
                    if (int(commandString[i+3]) >= 48 && int(commandString[i+3]) <= 57)
                    {
                        travel = (int(commandString[i+2])-48) * 10;
                        travel += (int(commandString[i+3])-48);
                        i+=3;
                    }
                    else
                    {
                        travel = (int(commandString[i+2])-48);
                        i+=2;
                    }
                }
                else
                {
                    badPos = i+2;
                    return 1;
                }
                
                travel *= -1; // to incorporate for the negative value
            }
            else
            {
                badPos = i+1;
                return 1;
            }
            
            if (commandString[original] == 'H' || commandString[original] == 'h') // The Horizontal Command
            {
                if ((c+travel)>30 || (c+travel)<0) // 1st check for values outside grid
                {
                    badPos = original;
                    return 2;
                }
                (plotLine(r, c,HORIZ,travel,plotChar, mode));
                c += travel;
            }
            else if (commandString[original] == 'V' || commandString[original] == 'v') // The Vertical Command
            {
                if ((r+travel)>20 || (r+travel)<0) // 1st check for values outside grid
                {
                    badPos = original;
                    return 2;
                }
                (plotLine(r, c,VERT,travel,plotChar,mode));
                r += travel;
                
            }
        }
        
        else // code should never get here
        {
            badPos = i;
            return 1;
        }
    }
    return 0;
}

bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg) // Given Plotline Function
{
    if (!isprint(plotChar)) // checks to make sure plotChar is an plot-able character
        return false;
    
    // pointers necessary to keep track of location on grid in case of multi-command command lines
    int * R = &r; 
    int * C = &c;
    
    if (dir == VERT)
    {
        if (plotVerticalLine(*R, *C,distance, plotChar, fgbg))
            return true;
    }
    else if (dir == HORIZ)
    {
        if (plotHorizontalLine(*R, *C, distance, plotChar, fgbg))
            return true;
    }
    
    // next few lines should be unnecessary, but are failsafe in case something strange happens during execution of command line
    else
        return false;
    return false;
}

bool plotHorizontalLine(int &r, int &c, int distance, char ch, int fgbg)
{
    int * p_R = &r;
    int * p_C = &c;
    
    r=*p_R;
    c=*p_C;
    
    if (r<1 || r>20 || c<1 || c>30) // 2nd check for values outside grid
        return false;
    
    if (distance<0) //plots negative Horizontal values
    {
        for (int k=0; k>=distance; k--)
        {
            if (c<1)
                return false;
            if (fgbg == 0)
            {
                if (getChar(r,c) == ' ')
                    setChar(r,c,ch);
            }
            else if (fgbg==1)
                setChar(r,c,ch);
            else
                return false;
            
            if (k!=distance)
                c--;
        }
    }
    else if (distance>=0) //plots positive Horizontal values
    {
        for (int k=0; k<=distance; k++)
        {
            if (c>30)
                return false;
            if (fgbg==0)
            {
                if (getChar(r,c) == ' ')
                    setChar(r,c,ch);
            }
            else if (fgbg==1)
                setChar(r,c,ch);
            else
                return false;
            if (k!=distance)
                c++;
        }
    }
    else
        return false;
    return true;
}

bool plotVerticalLine(int &r, int &c, int distance, char ch, int fgbg)
{
    int * p_R = &r;
    int * p_C = &c;
    
    r= *p_R;
    c= *p_C;
    
    
    if (r<1 || r>20 || c<1 || c>30) // 2nd check for values outside grid
        return false;
    
    if (distance<0) // plots negative Vertical values
    {
        for (int k=0; k>=distance; k--)
        {
            if (r<1)
                return false;
            if (fgbg==0)
            {
                if (getChar(r,c) == ' ')
                    setChar(r,c,ch);
            }
            else if (fgbg==1)
                setChar(r,c,ch);
            else
                return false;
            if (k!=distance)
                r--;
        }
    }
    else if (distance>=0) // plots positive Vertical values
    {
        for (int k=0; k<=distance; k++)
        {
            if (r>20)
                return false;
            if (fgbg==0)
            {
                if (getChar(r,c) == ' ')
                    setChar(r,c,ch);
            }
            else if (fgbg==1)
                setChar(r,c,ch);
            else
                return false;
            if (k!=distance)
                r++;
        }
    }
    return true;
}
