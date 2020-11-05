//
//  bankingApp.cpp
//  cpp-banking-app
//
//  Created by Rihards Mednis on 05/11/2020.
//  Copyright © 2020 Rihards Mednis. All rights reserved.
//

#include "bankingApp.hpp"
#include <iostream>
#include<fstream>
#include<iomanip>
#include<ctime>
#include <string.h>
#include <stdio.h>

using namespace std;

//-------------------------------------------------- HEADER -------------------------------

void header() {
    cout <<"---------------------------------------------------------------" << endl ;
    cout << setw(15) << "Account" << setw(10) << "Name"  << setw(15) << "Last name" << setw(15) << "Balance" << endl;
    cout <<"---------------------------------------------------------------" << endl ;
}

//-------------------------------------------------- MENU -------------------------------

int menu () {
    
    int choice;
    
    cout << "\n" << endl;
    cout << "1. Pievienot ierakstu;" << endl;
    cout << "2. Dzēst ierakstu;" << endl;
    cout << "3. Izvadīt visus ierakstus;" << endl;
    cout << "4. Meklēt klientu;" << endl;
    cout << "5. Izmainīt konta balansu;" << endl;
    cout << "6. Izvadīt lietotājus ar negatīvu balansu;" << endl;
    cout << "7. Izvadīt lietotāju skaitu datubāzē;" << endl;
    cout << "8. Izveidot datubāzes kopiju;" << endl;
    cout << "9. Ģenerēt lietotājus;" << endl;
    cout << "10. Iztukšot datubāzi;" << endl;
    cout << "11. Iziet ..\n\n" << endl;
    cout << "Izvēlieties veicamo darbību:  ";
    cin >> choice;
    cout<<"\n\n" << endl;
    
    if ( choice <=0 || choice > 10) {
        cout << "Šāda darbība nav piedāvāta." << endl;
        menu();
    }
    return choice;
}

//-------------------------------------------------- DISPLAY DETAILS -------------------------------

void display_details(client cl) {
    cout << setw(15) << cl.accnum << setw(10) << cl.name << setw(15) << cl.lname << setw(15) << cl.balance << endl;
}

//-------------------------------------------------- CREATE USER -------------------------------

void create_client(client cl) {
    fstream file;
    
    file.open("dati.dat", ios::out | ios::binary | ios::app);
    
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
    
    file.write((char*)&cl, sizeof(client));
    file.close();
    cout << "\n\n Klients pievienots." << endl;
}

//-------------------------------------------------- DATA INPUT -------------------------------

void data_input () {
    client cl;

    cout << "Ievadiet lietotāja numuru: " ;
    cin >> cl.accnum ;
    cout << "Ievadiet vārdu: " ;
    cin >> cl.name;
    cout << "Ievadiet uzvārdu: " ;
    cin >> cl.lname;
    cout << "Ievadiet konta atlikumu: " ;
    cin >> cl.balance ;
    
    if ( strlen(cl.name) > 10 || strlen(cl.lname) > 15) {
        cout << " \n\n Vārds ir pārāk garš";
    } else if ( strlen(cl.lname) > 15) {
        cout << " \n\n Uzvārds ir pārāk garš ";
    } else if ( strlen(cl.name) > 10 ) {
        cout << " \n\n Gan vārds, gan uzvārds ir pārāk garš ";
    }
    
    create_client(cl);
}

//----------------------------------------------------------------------------OUTPUT------------------------------------------------------------------------------

void display_all() {
    client cl;
    fstream file;
    
    header();
    
    file.open("dati.dat", ios::in | ios::binary);
       
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
    
    file.read((char*)&cl, sizeof(client));
    
        while(file) {
            if (cl.accnum !=0) display_details(cl);
            file.read((char*)&cl, sizeof(client));
        }
    
    file.close();
}

//----------------------------------------------------------------------------DELETE------------------------------------------------------------------------------

void client_delete(int input) {
    client cl;
    bool found = false;
    fstream file, tempfile;
 
    file.open("dati.dat", ios::in | ios::binary);
    
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
        
    tempfile.open("temp.dat", ios::out | ios::binary);
         
    if(!tempfile) {
        cerr <<"Kļūda izveidojot pagaidu failu ..\n"<<endl;
        exit(1);
    }
    
    while (file.read((char*)&cl, sizeof(client))  && !file.eof()) {
        if (cl.accnum != input) {
            tempfile.write((char*)&cl, sizeof(client));
        }
    }
    
    file.close();
    tempfile.close();
    file.open("dati.dat", ios::in | ios::binary);
        
    while(file.read((char*)&cl, sizeof(client))) {
        if (cl.accnum == input) {
            header();
            display_details(cl);
            found = true;
        }
    }

    if (found != true) {
        cout << "Klients nav atrasts." << endl ;
    } else {
        cout<<"\n\n\tKlients ir izdzēsts ..";
    }
    
    file.close();
    remove("dati.dat");
    rename("temp.dat","dati.dat");
}

//-------------------------------------------------- FIND -------------------------------

void find(int input) {
    client cl;
    fstream file;
    bool found = false;
    
    file.open("dati.dat", ios::out | ios::in | ios::binary);
    
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
    
    while(!file.eof() && found==false) {
        file.read((char*)&cl, sizeof(client));
        if (cl.accnum == input) {
            header();
            display_details(cl);
            found = true;
        }
    }

    if (found != true) cout << "Klients nav atrasts." << endl ;
    file.close();
}

//-------------------------------------------------- COPY DATABASE -------------------------------

void copy() {
    client cl;
    fstream file, copyfile;
    
    file.open("dati.dat", ios::in | ios::binary);
    copyfile.open("dati_copy.dat", ios::out | ios::binary);
    
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
    
    if(!copyfile) {
        cerr <<"Kļūda izveidojot kopijas failu...\n"<<endl;
        exit(1);
    }
    
    while (file.read((char*)&cl, sizeof(client)) && !file.eof()) {
        copyfile.write((char*)&cl, sizeof(client));
    }
    
    file.close();
    copyfile.close();
    cout << "Datubāzes kopija izveidota veiksmīgi.\n" << endl ;
    
    copyfile.open("dati_copy.dat", ios::in | ios::binary);
    header ();
    
    copyfile.seekg(0,ios::beg);
    copyfile.read((char*)&cl, sizeof(client));
    
        while(copyfile) {
            if (cl.accnum !=0) display_details(cl);
            copyfile.read((char*)&cl, sizeof(client));
        }
    
    copyfile.close();
}

//-------------------------------------------------- CHANGE BALANCE -------------------------------

void change_balance(int input) {
    int sum;
    client cl;
    fstream file, tempfile;
    bool found = false;
   
    file.open("dati.dat", ios::out | ios::in | ios::binary);
    
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
    
    while(!file.eof() && found==false) {
        file.read((char*)&cl, sizeof(client));
        if (cl.accnum == input) {
            header();
            display_details(cl);
            cout << " \nIevadiet summu ar '-' zīmi, ja vēlaties pamazināt balansu. \n\n Summa: ";
               cin >> sum;
            cl.balance += sum;
            int pos=(-1)*static_cast<int>(sizeof(client));
            file.seekp(pos,ios::cur);
            file.write((char*)&cl, sizeof(client));
            found = true;
        }
    }
  
    file.close();
    
    if (found== false) cout << "Šāds klients neeksistē.." << endl ;
    else cout << " Ieraksts atjaunots \n"<< endl ;
    
}

//-------------------------------------------------- NEGATIVE BALANCE -------------------------------

void negative_balance() {
    client cl;
    fstream file;
    
    file.open("dati.dat", ios::in | ios::binary);
  
    if(!file) {
        cerr <<"Kļūda atverot datubāzi...\n"<<endl;
        exit(1);
    }
    
    while (file.read((char*)&cl, sizeof(client))) {
        if(cl.balance < 0) {
            header();
            break;
        }
    }
    
    file.seekp(36,ios::beg);
    
    while (file.read((char*)&cl, sizeof(client))) {
        if(cl.balance < 0) {
            display_details(cl);
        }
    }
}

//-------------------------------------------------- CLIENT COUNT --------------------------------------------------------------------------

void client_count() {
    client cl;
    fstream file;
    int count = 0;
    
    file.open("dati.dat", ios::in | ios::binary);
    file.seekp(36,ios::beg);
    
    while (file.read((char*)&cl, sizeof(client))) {
        count++;
    }
    
    cout << "Klientu skaits: " << count << endl ;
}

//-------------------------------------------------- CLIENT GENERATION ---------------------------------------------------------------------

void user_generation() {
    client cl;
    time_t t;
    srand((unsigned) (time(&t))/87);
    fstream namesfile;
    string line;
    bool flag = true;
    
    namesfile.open("names.txt", ios::in);
    
            for (int g = 0; g<2; g++) {
                
                        while (!namesfile.fail() && !namesfile.eof()) {
                            
                                for (int i = 0; i<2; i++) {
                                    namesfile >> line;
                                    cout << line << endl;
                                    
                                    if (flag == true) {
                                        strcpy(cl.name, line.c_str());
                                        flag = false;
                                    } else {
                                        strcpy(cl.lname, line.c_str());
                                        flag = true;
                                    }
                                }
                           
                            cl.accnum = 1000 + (rand() % (9000 - 1000 + 1));
                            cl.balance = (float) rand()/(RAND_MAX +1)-9000+(rand()%18000);
                            cout << fixed;
                            cout << setprecision(2);
                            cout << cl.balance << endl ;
                            create_client(cl);
                        }
            }
}

//-------------------------------------------------- DATABASE CLEAR--------------------------------------------------------------------------

void delete_all() {
    fstream file, tempfile;
    
    tempfile.open("temp.dat", ios::out | ios::binary);
    remove("dati.dat");
    rename("temp.dat","dati.dat");
    cout << "DATUBĀZE DATI TIKA DZĒSTI .. " << endl ;
}
