/*

    Student Names:          | ID:
    Fadhlallah Almohammed   | 2230006097
    Ahmed Al-Nasser         | 2220001575 
    Akbar Al-ali            |
    Abbas Albasri           | 
    Ali Alzahrani           | 
    Abdulsalam Al-eissa     |2230003739


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

/* searchValues struct helps the function searchingRecord to 
return boolean if the id is found and the index of the id element */
struct varsToSearch {
    bool found = false;
    int index;
};


char menu();
void loadData(string, staffInfo [], int&);
void displayRecord(string, staffInfo [], int&);
void displayRecord(staffInfo[], int);
void addRecord(string, staffInfo [], int&);
varsToSearch searchingRecord(string, staffInfo[], int&);
   

// saveData function saves the data as following: name, id, position, department, email, age, salary
void saveData(string, staffInfo [], int&);

void deleteItem(staffInfo [], int&, const string&);

void sortRecords(staffInfo stfDetails[], int noOfStaff);

int main() {

    const string stfFileName = "staff_info.txt";

    const int LIMIT = 1000;
    int noOfStf = 0;
    staffInfo stfDetails[LIMIT];
    char userChoice(0);
    bool isFound = false;
    string idToDelete;
    varsToSearch searchValues;


    cout << "------- Welcome to the Staff System -------\n";


    loadData(stfFileName, stfDetails, noOfStf);

    do {
        userChoice = menu();

        switch (userChoice) {
            case '1':
                displayRecord(stfFileName,stfDetails, noOfStf);
                break;
            case '2':
                addRecord(stfFileName, stfDetails, noOfStf);
                break;
            case '3':
                // Update record function call goes here
                break;
            case '4':
                searchValues = searchingRecord(stfFileName, stfDetails, noOfStf);

                if (searchValues.found) {
                    displayRecord(stfDetails, searchValues.index);
                }
                break;
            case '5':
                deleteItem(stfDetails, noOfStf, stfFileName);
                break;
            case '6':
                // Sort records function call goes here
                break;
            case '7':
                // Exit the program
                break;
            default:
                cout << "\nInvalid input. Please enter a correct number!\n";
                break;
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
            staffFile << stfDetails[i].name << ',';
            staffFile << stfDetails[i].id << ',';
            staffFile << stfDetails[i].position << ',';
            staffFile << stfDetails[i].department << ',';
            staffFile << stfDetails[i].email << ',';
            staffFile << stfDetails[i].age << ',';
            staffFile << stfDetails[i].salary;

            if (i != noOfStaff-1) {
                staffFile << endl;
            }
            
        }
        staffFile.close();
    }
}

void displayRecord(string fileName, staffInfo stfDetails[], int& noOfStaff) {
    
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

varsToSearch searchingRecord(string fileName, staffInfo stfDetails[], int& noOfStaff) { 
   
    string search_for;
    varsToSearch values;

    cout << "Please enter your ID: ";
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
        values.found = true;
        values.index = index;
    }   
    else {
        cout << "No match found\n";
        values.found = false; 
    }
    return values;
}

void deleteItem(staffInfo stfDetails[], int& noOfStaff, const string& fileName) {

    varsToSearch searchValues;

    searchValues = searchingRecord(fileName, stfDetails, noOfStaff);

    if (searchValues.found) { //Shifting elements
        for (int j = searchValues.index; j < noOfStaff - 1; j++) {
        stfDetails[j] = stfDetails[j + 1];
        }
        
        noOfStaff-- ; //Fix the Array size for new entries
        cout << "ID : " << stfDetails[searchValues.index].id << " has been deleted successfully ✓ \n\n";
        saveData(fileName, stfDetails, noOfStaff);
    }
}

void addRecord(string fileName, staffInfo stfDetails[], int& noOfStf) {
   
    cout << "Enter the full name of the employee: ";
    getline(cin, stfDetails[noOfStf].name);

    cout << "Enter the ID number: ";
    getline(cin, stfDetails[noOfStf].id);

    cout << "Enter the current position: ";
    getline(cin, stfDetails[noOfStf].position);

    cout << "Enter the department: ";
    getline(cin, stfDetails[noOfStf].department);
    
    cout << "Enter the official email address: ";
    getline(cin, stfDetails[noOfStf].email);

    
    while (true) {
        string check;
        bool isCorrect(true);
        cout << "Enter the age: ";
        cin >> check;
        for (int i : check) {
            if (!isdigit(i)) {
                isCorrect = false;
                break;
            }
        }
        if (isCorrect) {
            stfDetails[noOfStf].age = stoi(check);
            break;
        } else {
            cout << "Invalid. Please enter a correct number!\n\n";
        }
    }
    
    while (true) {
        string check;
        bool isCorrect(true);
        cout << "Enter the current salary: ";
        cin >> check;
        for (int i : check) {
            if (!isdigit(i)) {
                isCorrect = false;
                break;
            }
        }
        if (isCorrect) {
            stfDetails[noOfStf].salary = stoi(check);
            break;
        } else {
            cout << "Invalid. Please enter a correct number!\n\n";
        }
    }
    
    noOfStf++;
    saveData(fileName, stfDetails, noOfStf);
}

// Function to sort ID numbers in records using Bubble Sort
void sortRecords(staffInfo stfDetails[], int noOfStaff) {
    for (int i = 0; i < noOfStaff - 1; i++) {
        for (int j = 0; j < noOfStaff - i - 1; j++) {
            if (stfDetails[j].id > stfDetails[j + 1].id) {
                // Swap the records
                staffInfo temp = stfDetails[j];
                stfDetails[j] = stfDetails[j + 1];
                stfDetails[j + 1] = temp;
            }
        }
    }
}
=======
    cout << "\nThe employee has been added successfuly \n\n";
}
