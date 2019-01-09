//
//  main.cpp
//  CS31 - PROJECT 5
//
//  Created by Vignesh Balasundaram on 5/24/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool decrypt(const char ciphertext[], const char crib[]);
void fixed_STRING(const char ciphertext[], char fixedcipher[4861]);
bool find_MATCH(char fixedcipher[], char fixedcrib[], char TRANSLATION[]);
bool check_MATCH(char fixedcipher[], char fixedcrib[], int& location);
void translate (char TRANSLATION[], char output[], const char ciphertext[], char fixedcrib[]);

//FUNCTION TO CONVERT STRING INTO NEW STRING WITH ONLY ALPHABETICAL CHARACTERS, SPACES, AND NEW LINES
void fixed_STRING(const char ciphertext[], char fixedcipher[])
{
    int count = 0;
    
    for (int i=0; ciphertext[i] != '\0';)                               //runs through ciphertext
    {
        if (isalpha(ciphertext[i]) || ciphertext[i] == '\n')            //checks to make sure character is alphabet or endline;
        {
            fixedcipher[count]=ciphertext[i];
            count++;
            i++;
        }
        
        else                                                            //removes unnecessary characters
        {
            fixedcipher[count]=' ';
            count++;
            while (!isalpha(ciphertext[i]) && ciphertext[i]!='\n')
                i++;
        }
    }
    
    fixedcipher[count]='\0';
}


//FUNCTION TO FIND MATCHING WORD(S) BETWEEN CRIB AND CIPHER
bool find_MATCH(char fixedcipher[], char fixedcrib[], char TRANSLATION[])
{
    int count = 0;
    int crib_count=0;
    int new_count=0;
    int length = 0;
    
    
    for (int len = 0; fixedcrib[len]!='\0'; len++)                      //cannot use strlen to find length of new crib
    {
        length++;
    }
    
    for (int i=0; fixedcipher[i]!='\0';i++)
    {
        for (crib_count=0;fixedcrib[crib_count]!='\0';)
        {
            if ((fixedcrib[crib_count]==' ' && fixedcipher[i+crib_count]==' ') || (isalpha(fixedcrib[crib_count]) && isalpha(fixedcipher[i+crib_count])))
            {
                crib_count++;                                           //keeps track of location in crib, and increases incrementally
                count++;                                                //keeps track of whether full crib was found or not
            }
            
            else
            {
                count = 0;                                              //if full crib not found, count is reset to 0
                break;
            }
        }
        
        if (count != 0 && fixedcipher[i+crib_count]!=' ' && fixedcipher[i+crib_count] !='\0')      //checks for repeats in the crib or cipher
        {
            count =0;
            while (fixedcipher[i] != '\0' && fixedcipher[i]!= ' ') i++;
            i--;
        }
        
        if (count != 0)                                                 //makes sure that crib is actually found
        {
            
            for (new_count=0, crib_count=0; new_count<length; new_count++, crib_count++)
            {
                TRANSLATION[new_count] = fixedcipher[i + crib_count];           //part of translation process to input characters to new string
            }
            
            TRANSLATION[new_count]='\0';
            
            
            for (new_count=0, crib_count=0; TRANSLATION[new_count] != '\0';)    //failsafe to make sure repetitions are proceeding correctly
            {
                for (int j=0; TRANSLATION[j]!='\0'; j++)
                {
                    if ((TRANSLATION[new_count]==TRANSLATION[j])&&(fixedcrib[new_count]!=fixedcrib[j]))
                        return false;
                }
                new_count++;
            }
            
            return true;
        }
    }
    
    return false;                                                   //Failsafe so if code reaches this line - returns false
}


//FUNCTION THAT TRANSLATES THE OLD TEXT INTO THE NEW SEQUENCE OF CHARACTERS
void translate (char TRANSLATION[], char output[], const char ciphertext[], char fixedcrib[])
{
    int i;
    bool failsafe = false;                                          //Failsafe initialization
    
    for (i=0; ciphertext[i] != '\0'; i++)
    {
        for (int j=0; TRANSLATION[j]!=0; j++)
        {
            if (ciphertext[i]==TRANSLATION[j])
            {
                output[i] = toupper(fixedcrib[j]);                  //capitalizes appropriate characters
                failsafe = true;
            }
        }
        
        if (failsafe == true)                                       //keeps loop going until necessary failsafe has been completed
        {
            failsafe = false;
        }
        
        else
        {
            output[i] = ciphertext[i];
        }
    }
    
    output[i] = '\0';
    cout << output;
}


//MAIN DECRYPTION FUNCTION THAT CALLS ALL OTHER FUNCTIONS TO OUTPUT CORRECT STRING
bool decrypt(const char ciphertext[], const char crib[])
{
    if (crib[0] == '\0')                                        //failsafe to make sure crib is not empty
        return false;
    
    char cipher_FIXED[60*80 + 60 + 1];
    
    /*max array size found because largest ciphertext line is 80 characters, most newlines are 60 (hence 60*80)
     then 60 more to incorporate for the newline characters themselves, and finally 1 more for the null character
     so therefore this equals (60 * 80 + 60 + 1 = 4861) */
    
    char crib_FIXED[80];                                        //80 is max ciphertext length
    char crib_TRANSLATE[80];                                    //80 is max ciphertext length
    char output[60*80 + 60 + 1];
    
    if (strlen(crib) > 80)
        return false;
    
    fixed_STRING(crib, crib_FIXED);
    
    fixed_STRING(ciphertext, cipher_FIXED);
    
    if (find_MATCH(cipher_FIXED, crib_FIXED, crib_TRANSLATE) == false)          //checks to make sure that crib and cipher match
        return false;
    
    else
    {
        translate(crib_TRANSLATE, output, ciphertext, crib_FIXED);
    }
    
    return true;
}

//VOID FUNCTION PROVIDED
void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}
