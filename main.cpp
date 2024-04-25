#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;


struct staffInfo {

    string name;
    string id;
    string position;
    string department;
    string email;
    int age;
    double salary;
};


char menu();
void loadData(string, staffInfo, int&);
void displayRecords(string, staffInfo [], int&);

int main() {

    const string staffFile = "staff_info.txt";

    const int LIMIT = 1000;
    int noOfStf = 0;
    staffInfo stfDetails[LIMIT];
    int userChoice(0);


    cout << "------- Welcome to the Staff System -------";

    userChoice = menu();

    displayRecords(staffFile, stfDetails, noOfStf);




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


void loadData(string fileName, staffInfo stfDetails[], int& noOfStaff) {

    ifstream staffFile(fileName);

    if (staffFile.is_open()) {
        int count(0);

        while (!staffFile.eof()) {
            getline(staffFile, stfDetails[count].name, ',');
            getline(staffFile, stfDetails[count].id, ',');
            getline(staffFile, stfDetails[count].position, ',');
            getline(staffFile, stfDetails[count].department, ',');
            getline(staffFile, stfDetails[count].email, ',');
            staffFile >> stfDetails[count].age;
            staffFile.ignore(1);
            staffFile >> stfDetails[count].salary;
            staffFile.ignore(1);

            count++;
        }
        staffFile.close();
        noOfStaff = count;
    }
}


void displayRecords(string fileName, staffInfo stfDetails[], int& noOfStaff) {
    
    loadData(fileName, stfDetails, noOfStaff);

    cout << "\nEmployees Info: \n\n";

    for (int i = 0; i < noOfStaff; i++) {
        
        cout << "Name: " << stfDetails[i].name << "\n"
             << "ID number: " << stfDetails[i].id << "\n"
             << "Position: " << stfDetails[i].position << "\n"
             << "Department: " << stfDetails[i].department << "\n"
             << "Email: " << stfDetails[i].email << "\n"
             << "Age: " << stfDetails[i].age << "\n"
             << "Salary: " << stfDetails[i].salary << "\n\n"
             << "---------------------------------------" << "\n\n";
    }
}

