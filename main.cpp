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
#include <algorithm>
#include <ctime>
using namespace std;


const string statFileName = "statistical_report.txt";

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

// functions' prototypes
char menu();
void loadData(string, staffInfo [], int&);
void displayRecord(string, staffInfo [], int&);
void displayRecord(staffInfo[], int);
void addRecord(string, staffInfo [], int&);
/* updateRecord prompt the user to update one of the items in the record except the
identification number. It continues prompting to update until the user choose to exit */
void updateRecord(string, staffInfo [], int&);
/* searchingRecord return a struct of two variables. return boolean if employee is found
and the index of the employee in the array  */
varsToSearch searchingRecord(string, staffInfo[], int&);
// saveData function saves the data as following: name, id, position, department, email, age, salary
void saveData(string, staffInfo [], int&);
void deleteItem(staffInfo [], int&, const string&);
// sortRecords function sorts the ID numbers in records using Bubble Sort
void sortRecords(string fileName, staffInfo stfDetails[], int noOfStaff);
/*statisticalReport function provides a statistics about the employees data
 given in the "staff_info.txt" file*/
void statisticalReport(string, staffInfo [], int&);


int main() {

    const string stfFileName = "staff_info.txt";
    const string beckupFileName = "backup_data.txt";

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
                updateRecord(stfFileName, stfDetails, noOfStf);
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
                sortRecords(stfFileName, stfDetails, noOfStf);
                break;
            case '7':
                // Exit the program
                break;
            default:
                cout << "\nInvalid input. Please enter a correct number!\n";
                break;
        }
    } while (userChoice != '7');

    saveData(stfFileName, stfDetails, noOfStf);

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

    statisticalReport(statFileName, stfDetails, noOfStaff);
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

    while (true) {
        string check;
        bool isCorrect(true);
        cout << "Enter the ID number: ";
        cin >> check;
        for (int i : check) { // 112345
            if (!isdigit(i)) {
                isCorrect = false;
                break;
            }
        }
        if (isCorrect) {
            stfDetails[noOfStf].id = check;
            break;
        } else {
            cout << "Invalid. Please enter a correct number!\n\n";
        }
    }

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

    cout << "\nThe employee has been added successfuly \n\n";

}


void sortRecords(string fileName, staffInfo stfDetails[], int noOfStaff) {
    char sortType;
    cout << "\n Choose from the following to sort: " << endl
        << "a - sort alphabetically" << endl
        << "b - sort by ID" << endl
        << "Enter your choice: ";
    cin >> sortType;
    cin.ignore();

    bool sortByName = true;
    if (tolower(sortType) == 'a') {
        sortByName = false;}

        if(sortByName){
        // Sort alphabetically by name (case-insensitive)
            for (int i = 0; i < noOfStaff - 1; i++) {
                for (int j = i + 1; j < noOfStaff; j++) {
                    if (stfDetails[i].name > stfDetails[j].name) {
                        swap(stfDetails[i], stfDetails[j]);
                    }
                }
            }
    }

    else{
    // Sort by ID in ascending order
    for (int i = 0; i < noOfStaff - 1; i++) {
            for (int j = i + 1; j < noOfStaff; j++) {
                if (stfDetails[i].id > stfDetails[j].id) {
                    swap(stfDetails[i], stfDetails[j]);
                    }
                }   
            }
        }
        saveData(fileName, stfDetails, noOfStaff);
        cout << "\nData sorted successfully!\n";
}

void updateRecord(string fileName, staffInfo stfDetails[], int& noOfStaff) {

    string idEmployee;
    char choiceToUpdate;
    varsToSearch searchResult;

    searchResult = searchingRecord(fileName, stfDetails, noOfStaff);

    if (searchResult.found) {

        do {
            cout << "Which one would you like to update: " << endl
                << "1 - Name" << endl
                << "2 - Position" << endl
                << "3 - Department" << endl
                << "4 - Email" << endl
                << "5 - Age" << endl
                << "6 - Salary" << endl
                << "7 - Exit" << endl
                << "Enter your choice: ";
            cin >> choiceToUpdate;
            cin.ignore();

            

            bool updated(false);
            
            switch (choiceToUpdate) {
                case '1':
                    cout << "Enter the employee name: ";
                    getline(cin, stfDetails[searchResult.index].name);
                    updated = true;
                    break;
                case '2':
                    cout << "Enter the position: ";
                    getline(cin, stfDetails[searchResult.index].position);
                    updated = true;
                    break;
                case '3':
                    cout << "Enter the department: ";
                    getline(cin, stfDetails[searchResult.index].department);
                    updated = true;
                    break;
                case '4':
                    cout << "Enter the email address: ";
                    getline(cin, stfDetails[searchResult.index].email);
                    updated = true;
                    break;
                case '5':
                    while (true) {
                        string check;
                        bool isCorrect(true);
                        cout << "Enter the age: ";
                        cin >> check;
                        for (int i : check) {
                            if (!isdigit(i)) {
                                isCorrect = false;
                                break;}
                            }   
                        if (isCorrect) {
                            stfDetails[searchResult.index].age = stoi(check);
                            updated = true;
                            break;
                        } else {
                            cout << "Invalid. Please enter a correct number!\n\n"; }
                    }
                    break;
                case '6': 
                    while (true) {
                        string check;
                        bool isCorrect(true);
                        cout << "Enter the salary: ";
                        cin >> check;
                        for (int i : check) {
                            if (!isdigit(i)) {
                                isCorrect = false;
                                break;}
                            }   
                        if (isCorrect) {
                            stfDetails[searchResult.index].salary = stoi(check);
                            updated = true;
                            break;
                        } else {
                            cout << "Invalid. Please enter a correct number!\n\n"; }
                    }
                    break;
                case '7':
                    break;
                default:
                    cout << "Invalid. Please enter a correct number";
                    break;
            }
            if (updated) {
                cout <<"Updated successfuly\n\n";
            }
            
        } while (choiceToUpdate != '7');
        
    } else {
            cout << "Employee not found!\n\n";
        }
    saveData(fileName, stfDetails, noOfStaff);
}

void statisticalReport(string fileName, staffInfo stfDetails[], int& noOfStaff) {

    time_t timeNow = time(0);
    tm *currentTime = localtime(&timeNow);

    int totalSalaries(0);

    for (int i = 0; i < noOfStaff; i++) {
        totalSalaries += stfDetails[i].salary;
    }

    ofstream statFile(fileName);

    if (statFile.is_open()) {
        statFile << "Number of Employees: " << noOfStaff << endl
                 << "Last update: " << currentTime->tm_mday << "-" << currentTime->tm_mon << "-" << (currentTime->tm_year + 1900) << endl
                 << "Time of last update (GMT+3): " << currentTime->tm_hour << ":" << currentTime->tm_min << endl
                 << "Total salaries of employees: " << totalSalaries << " SR" << endl;
    }

}

