//
//  main.cpp
//  Project 3
//
//  Created by Vignesh Balasundaram on 7/26/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "PeopleList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main ()
{
    PeopleList m, test, test2;
    
    m.add("Skyler", "White", 45);
    m.add("James", "McGill", 49);
    m.add("Charles", "McGill", 58);
    m.add("Walter", "White", 52);
    m.add("Jesse", "Pinkman", 27);
    
    
    psearch("*", "McGill", m, test);
    
    test.change("Charles", "McGill", 11);
    combine(m, test, test2);
    
    for (int n = 0; n < test2.size(); n++)
    {
        string f;
        string l;
        int v;
        test2.get(n, f, l, v);
        cout << f << " " << l << " " << v << endl;
    }
}
