#include <iomanip>
#include <iostream>
#include <fstream>
#include "bankingApp.hpp"
using namespace std;

int menu ();
void find(int);
void create_client(client);
void client_delete(int);
void data_input();
void display_all();
void copy();
void change_balance (int);
void header ();
void display_details (client);
void negative_balance();
void client_count();
void user_generation();
void delete_all();

int input, sum;
client cl;

//----------------------------------------------------------MAIN--------------------------------------------------------------------------------------------------------------------

int main() {
    int choice = menu ();
    
    while (choice!=11) {
        switch (choice) {
            case 1:
                data_input();
                break;
            case 2:
                cout << "Ievadiet lietotāja numuru: ";
                cin >> input;
                client_delete(input);
                break;
            case 3:
                display_all();
                break;
            case 4:
                cout << "Ievadiet lietotāja numuru: ";
                cin >> input;
                find(input);
                break;
            case 5:
                cout << "Ievadiet klienta numuru: " ;
                cin >> input;
                change_balance(input);
                break;
            case 6:
                negative_balance();
                break;
            case 7:
                client_count();
                break;
            case 8:
                copy();
                break;
            case 9:
                user_generation();
                break;
            case 10:
                delete_all();
        }
        choice = menu ();
    }
}
