/*

    Student Names:          | ID:
    Fadhlallah Almohammed   | 2230006097
    Ahmed Al-Nasser         | 2220001575 
    Akbar Al-ali            |
    Abbas Albasri           | 
    Ali Alzahrani           | 
    Abdulsalam Al-eissa     |


*/


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
void loadData(string, staffInfo [], int&);
void displayRecords(string, staffInfo [], int&);
void displayRecord(staffInfo[], int);
bool searchingRecords(string, staffInfo[], int&);
   

// saveData function saves the data as following: name, id, position, department, email, age, salary
void saveData(string, staffInfo [], int&);

void deleteItem(string, staffInfo [], int&, const string&);


int main() {

    const string stfFileName = "staff_info.txt";

    const int LIMIT = 1000;
    int noOfStf = 0;
    staffInfo stfDetails[LIMIT];
    char userChoice(0);
    bool isFound = false;


    cout << "------- Welcome to the Staff System -------";


    loadData(stfFileName, stfDetails, noOfStf);

    displayRecords(stfFileName, stfDetails, noOfStf);

    do {
        userChoice = menu();

        switch (userChoice) {
            case '1': {
                displayRecords(stfFileName,stfDetails, noOfStf);
                break;
            }
            case '2': {
                // Add record function call goes here
                break;
            }
            case '3': {
                // Update record function call goes here
                break;
            }
            case '4': {
                isFound = searchingRecords(stfFileName, stfDetails, noOfStf);
                break;
            }
            case '5': {
                string idDelete;
                cout << "Enter an ID to Delete : ";
                cin >> idDelete;
                deleteItem(idDelete, stfDetails, noOfStf, stfFileName);
                break;
            }
            case '6': {
                // Sort records function call goes here
                break;
            }
            case '7': {
                // Exit the program
                break;
            }
            default: {
                cout << "\nInvalid input. Please enter a correct number!\n";
                break;
            }
        }
    } while (userChoice != '7');


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

void saveData(string fileName, staffInfo stfDetails[], int& noOfStaff) {

    ofstream staffFile(fileName);

    if (staffFile.is_open()) {
        for (int i = 0; i < noOfStaff; i++) {
            if (stfDetails[i].id != ""){
            staffFile << stfDetails[i].name << ", ";
            staffFile << stfDetails[i].id << ", ";
            staffFile << stfDetails[i].position << ", ";
            staffFile << stfDetails[i].department << ", ";
            staffFile << stfDetails[i].email << ", ";
            staffFile << stfDetails[i].age << ", ";
            staffFile << stfDetails[i].salary;

            if (i != noOfStaff-1) {
                staffFile << endl;
                }
            }
        }
        staffFile.close();
    }
}


// Deleting Function
void deleteItem(string id, staffInfo stfDetails[], int& noOfStaff, const string& fileName) {

    bool found = false;


    // bool found = searchingRecords(fileName, stfDetails, noOfStaff);

    // Search if ID matches on the records data file.
    for (int i = 0; i < noOfStaff; i++) {
        if (stfDetails[i].id == id) {
            found = true;

        for (int j = i; j < noOfStaff - 1; j++) {
        stfDetails[j] = stfDetails[j + 1];
        }

        noOfStaff-- ; //Fix the Array size for new entries
        cout << "ID : " << id << " - has deleted successfully ☑️. \n\n";
        saveData(fileName, stfDetails, noOfStaff);
        cout << "Date saved successfully ✅ \n"; 

    return;

        }
    }

    if (!found) { 
        cout << "Record for this ID : " << id << " not found. \n\n";
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

void displayRecord(staffInfo stfDetails[], int index) {

    cout << "\n----------------------------------------" << '\n'
         << "Name: " << stfDetails[index].name << "\n"
         << "ID number: " << stfDetails[index].id << "\n"
         << "Position: " << stfDetails[index].position << "\n"
         << "Department: " << stfDetails[index].department << "\n"
         << "Email: " << stfDetails[index].email << "\n"
         << "Age: " << stfDetails[index].age << "\n"
         << "Salary: " << stfDetails[index].salary << "\n\n"
         << "---------------------------------------" << "\n\n";
}


bool searchingRecords(string fileName, staffInfo stfDetails[], int& noOfStaff) { 
   
    string search_for;

    cout << "What do you want to search for? ";
    getline(cin, search_for); // Use getline to capture the entire line of input


    int index = 0;
    bool found = false; // Initialize found to false

    // Search if ID matches on the records data file.
    for (int i = 0; i < noOfStaff; i++) {
        if (stfDetails[i].id == search_for) {
            index=i;
            found = true;
            break;
        }
    }

    if (found) { 
        cout<<endl << "match found!" << endl;
        displayRecord(stfDetails, index);
          
        return true;
    }   
    else {
        cout << "No match found\n";
        return false; 
    }
}