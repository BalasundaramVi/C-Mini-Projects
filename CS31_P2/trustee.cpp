//
//  trustee.cpp
//  CS31
//
//  Created by Vignesh Balasundaram on 4/5/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main () {
    cout << "Asset name: ";
    string asset_name;
    getline(cin,asset_name);
    
    cout << "Value (in thousands): ";
    double value;
    cin >> value;
    cin.ignore(10000, '\n');
    
    cout << "Category: ";
    string category;
    getline(cin,category);
    
    cout << "---" << endl;
    
    double fee = 0;
    
    if (value<=1000) {
        fee = (value*0.013);
    }
    else if (value>1000 && value <=10000) {
        double mid = 0.01;
        if (category == "mutual fund" || category == "royalty") {
            mid = 0.2;
        }
        fee = (1000*.013) + ((value-1000)*mid);
    }
    else {
        double mid = 0.01;
        if (category == "mutual fund" || category == "royalty") {
            mid = 0.002;
        }
        fee = (1000*.013) + (9000*mid) + ((value-10000)*0.009);
    }
    
    long long int total_fee;
    double fraction;
    fraction = (fee*1000);
    total_fee = (fee*1000);
    
    if ((fraction-total_fee) >= 0.5)
        total_fee++;
    
    bool check=true;
    
    if (asset_name == "" && check == true) {
        cout << "You must enter an asset name." << endl;
        check = false;
    }
    if (value<0 && check == true) {
        cout << "The asset value must be nonnegative." << endl;
        check = false;
    }
    if (category == "" && check==true) {
        cout << "You must enter an asset category." << endl;
        check = false;
    }
    if (check==true){
        cout << "The trustee fee for " << asset_name << " is $" << total_fee << "." << endl;
    }
}
