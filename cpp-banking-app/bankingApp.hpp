//
//  bankingApp_hpp
//  Mednis_Rihards_bank_acc_v3
//
//  Created by SOSA on 19/09/2019.
//  Copyright © 2019 EKA. All rights reserved.
//

#ifndef bankingApp_hpp
#define bankingApp_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class client {
    
public:
    int accnum;
    char name[10];
    char lname[15];
    float balance;
    
    int menu ();
    void find (int);
    void data_input ();
    void create_client (client);
    void display_details (client);
    void header ();
    void display_all ();
    void client_delete(int);
    void copy();
    void change_balance(int);
    void negative_balance();
    void client_count();
    void user_generation();
    void delete_all();
};

#endif /* bankingApp_hpp */
