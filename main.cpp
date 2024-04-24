#include <iostream>
#include <string>
#include <cctype>
using namespace std;


char menu();

struct staffInfo {

    string name;
    string id;
    string position;
    string department;
    string email;
    int age;
    double salary;
};


int main() {

    const int LIMIT = 1000;
    int noOfStf = 0;
    int stfDetails[LIMIT];
    int userChoice(0);


    cout << "------- Welcome to the Staff System -------";

    userChoice = menu();




    return 0;
}


char menu() {

    char choice;

    while (true) {
        cout << "\nMenu:"   << endl
            << "1 - Display the records" << endl
            << "2 - Add a record"        << endl
            << "3 - Update a record"     << endl
            << "4 - Search for a record" << endl
            << "5 - Delete a record"     << endl
            << "6 - Sort the records"    << endl
            << "7 - Exit the program"    << endl
            << endl
            << "Please choose from the menu: ";
        choice = cin.get();
        cin.ignore();

        if (choice >= '1' && choice <= '7') {
            return choice;
        }
        else {
            cout << "\nInvalid input. Please enter a correct number!\n";
        
        }
    }
}

