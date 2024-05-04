/*

    Student Names:          | ID:
    Fadhlallah Almohammed   | 2230006097
    Ahmed Al-Nasser         | 2220001575 
    Akbar Al-ali            | 2230005027
    Abbas Albasri           | 2230000457
    Ali Alzahrani           | 2230007267
    Abdulsalam Al-eissa     | 2230003739

*/


#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;


const string statFileName = "statistical_report.txt";
const int LIMIT = 1000;

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
/* loadData loads the employees data into the array */ 
void loadData(string, staffInfo [], int&);
void backUpData(string, string);
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
// sortRecords function sorts a specific category in records using Bubble Sort
void sortRecords(string fileName, staffInfo stfDetails[], int noOfStaff);
/*statisticalReport function provides a statistics about the employees data
given in the "staff_info.txt" file*/
void statisticalReport(string, staffInfo [], int&);
void displayReport();


int main() {

    const string stfFileName = "staff_info.txt";
    const string backupFileName = "backup_data.txt";

    int noOfStf = 0;
    staffInfo stfDetails[LIMIT];
    char userChoice(0);
    bool isFound = false;
    string idToDelete;
    varsToSearch searchValues;


    cout << "\n---------------------------------------------------\n"
        << "|       WELCOME TO THE STAFF MANAGEMENT SYSTEM    |"
        << "\n---------------------------------------------------\n";

    backUpData(stfFileName, backupFileName);
    loadData(stfFileName, stfDetails, noOfStf);
    statisticalReport(statFileName, stfDetails, noOfStf);

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
                displayReport();
                break;
            case '8':
                // Exit the program
                break;
            default:
                cout << "\nInvalid input. Please enter a correct number!\n";
                break;
        }
    } while (userChoice != '8');

    saveData(stfFileName, stfDetails, noOfStf);

    cout << "\n\n"
        << "==============================================================================================\n"
        << "|                                                                                            |\n"
        << "|    Thank you for using our Staff System! We hope it served you well.                       |\n"
        << "|                                                                                            |\n"
        << "|    ----------------------------------TEAM DEVELOPERS----------------------------------     |\n"
        << "|                                                                                            |\n"
        << "|   => Fadhlallah Almohammed                                                                 |\n"
        << "|   => Ali Alzahrani                                                                         |\n"
        << "|   => Ahmed Al-Nasser                                                                       |\n"
        << "|   => Abdulsalam al-eissa                                                                   |\n"
        << "|   => Akbar Al-ali                                                                          |\n"
        << "|   => Abbas albasri                                                                         |\n"
        << "|                                                                                            |\n"
        << "|   We appreciate your support and look forward to serving you again!                        |\n"
        << "|                                                                                            |\n"
        << "==============================================================================================\n"
        << "\n\n\n";


    return 0;
}


char menu() {

    

    while (true) {
        string choice;
        cout <<"===================================================" << endl
            << "|                     Menu                        |" << endl
            << "|-------------------------------------------------|" << endl
            << "| 1 - Display the Records                         |" << endl
            << "| 2 - Add a Record                                |" << endl
            << "| 3 - Update a Record                             |" << endl
            << "| 4 - Search for a Record                         |" << endl
            << "| 5 - Delete a Record                             |" << endl
            << "| 6 - Sort the Records                            |" << endl
            << "| 7 - Exit the Program                            |" << endl
            << "===================================================" << endl
            << endl
            << "Please choose from the menu : ";
        getline(cin, choice);
        

        if (choice.length() == 1) {
            return choice[0];
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

    if (noOfStaff < 0) {
        return;
    }

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
        << " Name: " << stfDetails[index].name << "\n"
        << " ID number: " << stfDetails[index].id << "\n"
        << " Position: " << stfDetails[index].position << "\n"
        << " Department: " << stfDetails[index].department << "\n"
        << " Email: " << stfDetails[index].email << "\n"
        << " Age: " << stfDetails[index].age << "\n"
        << " Salary: " << stfDetails[index].salary << "\n\n"
        << "---------------------------------------" << "\n\n";
}

varsToSearch searchingRecord(string fileName, staffInfo stfDetails[], int& noOfStaff) { 

    string search_for;
    varsToSearch values;
    int index = 0;
    bool found = false;
    while (true) {
        string check;
        bool isCorrect(true);
        cout << "\n - Enter the ID number: ";
        getline(cin, check);

        for (int i : check) {
            if (!isdigit(i)) {
                isCorrect = false;
                break;
            }
        }
        if (isCorrect) {
            for (int i = 0; i < noOfStaff; i++) {
                if (stfDetails[i].id == check) {
                index=i;
                found = true;
                break;
            } 
            
            }
            break;
        }
    else {
            cout << "\n X Invalid. Please enter a correct number! X \n\n";
        }
    }

    // Search if ID matches on the records data file.
    if (found) { 
        cout<<endl << "\n match found! \n" << endl;
        values.found = true;
        values.index = index;
    }   
    else {
        cout << "\n ? No match found ? \n\n";
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
        cout << "\n ID - " << stfDetails[searchValues.index].id << " - has been deleted successfully \n\n";
        saveData(fileName, stfDetails, noOfStaff);
    }
}

void addRecord(string fileName, staffInfo stfDetails[], int& noOfStf) {

    if (noOfStf >= LIMIT) {
        cout << "\n X Sorry. Can't add a record because the file is full X \n\n";
        return;
    }

    cout << "\n    ---- Adding a Record ----    \n\n";

    cout << " - Enter the full name of the employee: ";
    getline(cin, stfDetails[noOfStf].name);

    while (true) {
        string check;
        bool isCorrect(true);
        cout << " - Enter the ID number: ";
        getline(cin, check);
        
        for (int i : check) { 
            if (!isdigit(i)) {
                isCorrect = false;
                break;
            }
        }
        if (isCorrect) {
            stfDetails[noOfStf].id = check;
            break;
        } else {
            cout << "\n X Invalid. Please enter a correct number! X \n\n";
        }
    }

    cout << " - Enter the current position: ";
    getline(cin, stfDetails[noOfStf].position);

    cout << " - Enter the department: ";
    getline(cin, stfDetails[noOfStf].department);
    
    cout << " - Enter the official email address: ";
    getline(cin, stfDetails[noOfStf].email);

    
    while (true) {
        string check;
        bool isCorrect(true);
        cout << " - Enter the age: ";
        getline(cin, check);
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
            cout << "\n X Invalid. Please enter a correct number! X \n\n";
        }
    }
    
    while (true) {
        string check;
        bool isCorrect(true);
        cout << " - Enter the current salary: ";
        getline(cin, check);

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
            cout << "\n X Invalid. Please enter a correct number! X \n\n";
        }
    }
    
    noOfStf++;
    saveData(fileName, stfDetails, noOfStf);

    cout << "\n The employee has been added successfuly \n\n";

}

void sortRecords(string fileName, staffInfo stfDetails[], int noOfStaff) {

    bool valid(true);
    string sortType;
    do {    
        valid = true;
        cout << "\n    ---- Sort Options ----    \n"
            << " a - Name\n"
            << " b - ID\n"
            << " c - Department\n"
            << " d - Position\n"
            << " e - salary\n"
            << " f - Age\n"
            << "\n - Enter your choice: ";
        getline(cin, sortType);

        if (sortType.length() == 1) {
            switch (tolower(sortType[0])) {
                case 'a':
                    // Sort  by name alphabetically
                    for (int i = 0; i < noOfStaff - 1; i++) {
                        for (int j = i + 1; j < noOfStaff; j++) {
                            if (stfDetails[i].name > stfDetails[j].name) {
                                swap(stfDetails[i], stfDetails[j]);
                            }
                        }
                    }
                    cout << "\n Data sorted successfully! \n";
                    break;

                case 'b':
                    // Sort by ID in ascending order
                    for (int i = 0; i < noOfStaff - 1; i++) {
                        for (int j = i + 1; j < noOfStaff; j++) {
                            if (stfDetails[i].id > stfDetails[j].id) {
                                swap(stfDetails[i], stfDetails[j]);
                            }
                        }
                    }
                    cout << "\n Data sorted successfully! \n";
                    break;

                case 'c':
                    // Sort by department alphabetically
                    for (int i = 0; i < noOfStaff - 1; i++) {
                        for (int j = i + 1; j < noOfStaff; j++) {
                            if (stfDetails[i].department > stfDetails[j].department) {
                                swap(stfDetails[i], stfDetails[j]);
                            }
                        }
                    }
                    cout << "\n Data sorted successfully! \n";
                    break;
                
                case 'd':
                    // Sort by position alphabetically
                    for (int i = 0; i < noOfStaff - 1; i++) {
                        for (int j = i + 1; j < noOfStaff; j++) {
                            if (stfDetails[i].position > stfDetails[j].position) {
                                swap(stfDetails[i], stfDetails[j]);
                            }
                        }
                    }
                    cout << "\n Data sorted successfully! \n";
                    break;

                case 'e':
                    // Sort by salary in ascending order
                    for (int i = 0; i < noOfStaff - 1; i++) {
                        for (int j = i + 1; j < noOfStaff; j++) {
                            if (stfDetails[i].salary > stfDetails[j].salary) {
                                swap(stfDetails[i], stfDetails[j]);
                            }
                        }
                    }
                    cout << "\n Data sorted successfully! \n";
                    break;

                case 'f':
                    // Sort by age in ascending order
                    for (int i = 0; i < noOfStaff - 1; i++) {
                        for (int j = i + 1; j < noOfStaff; j++) {
                            if (stfDetails[i].age > stfDetails[j].age) {
                                swap(stfDetails[i], stfDetails[j]);
                            }
                        }
                    }
                    cout << "\n Data sorted successfully! \n";
                    break;

                default:
                    cout << "\n X Invalid. Please enter a correct letter! X " << endl;
                    valid = false;
                break;
            }
        } else {
            cout << "\n X Invalid. Please enter a single letter! X " << endl;
            valid = false;
        }

        saveData(fileName, stfDetails, noOfStaff);

    } while (!valid);

}

void updateRecord(string fileName, staffInfo stfDetails[], int& noOfStaff) {

    string idEmployee;
    string choiceToUpdate;
    varsToSearch searchResult;

    searchResult = searchingRecord(fileName, stfDetails, noOfStaff);

    if (searchResult.found) {

        do {
            cout << "    ---- Update Options ----    : " << endl
                << " 1 - Name" << endl
                << " 2 - Position" << endl
                << " 3 - Department" << endl
                << " 4 - Email" << endl
                << " 5 - Age" << endl
                << " 6 - Salary" << endl
                << " 7 - Exit" << endl
                << "\n - Enter your choice: ";
            getline(cin, choiceToUpdate);

            

            bool updated(false);
            
            if (choiceToUpdate.length() == 1) {
                switch (choiceToUpdate[0]) {
                    case '1':
                        cout << " - Enter the employee name: ";
                        getline(cin, stfDetails[searchResult.index].name);
                        updated = true;
                        break;
                    case '2':
                        cout << " - Enter the position: ";
                        getline(cin, stfDetails[searchResult.index].position);
                        updated = true;
                        break;
                    case '3':
                        cout << " - Enter the department: ";
                        getline(cin, stfDetails[searchResult.index].department);
                        updated = true;
                        break;
                    case '4':
                        cout << " - Enter the email address: ";
                        getline(cin, stfDetails[searchResult.index].email);
                        updated = true;
                        break;
                    case '5':
                        while (true) {
                            string check;
                            bool isCorrect(true);
                            cout << " - Enter the age: ";
                            getline(cin, check);

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
                                cout << "\n X Invalid. Please enter a correct number! X \n\n";
                                }
                        }
                        break;
                    case '6': 
                        while (true) {
                            string check;
                            bool isCorrect(true);
                            cout << " - Enter the salary: ";
                            getline(cin, check);
                            
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
                                cout << "\n X Invalid. Please enter a correct number! X \n\n"; }
                        }
                        break;
                    case '7':
                        break;
                    default:
                        cout << "\n X Invalid. Please enter a correct number! X \n\n";
                        break;
                }
                if (updated) {
                    cout <<"\n Updated successfuly \n\n";
                }
            } else {
                cout << "\n X Invalid. Please enter a single number X \n\n";
            }
                
        } while (choiceToUpdate[0] != '7');
    
    }
    saveData(fileName, stfDetails, noOfStaff);
}

void statisticalReport(string fileName, staffInfo stfDetails[], int& noOfStaff) {

    time_t timeNow = time(0);
    tm *currentTime = localtime(&timeNow);

    int totalSalaries(0);
    int avgAge(0);


    //calculate average age and summation of salaries
    for (int i = 0; i < noOfStaff; i++) {
        totalSalaries += stfDetails[i].salary;
        avgAge += stfDetails[i].age;
    }
    avgAge /= noOfStaff;

    ofstream statFile(fileName);

    if (statFile.is_open()) {
        statFile << "Number of Employees: " << noOfStaff << endl
                << "Last update: " << currentTime->tm_mday << "-" << currentTime->tm_mon << "-" << (currentTime->tm_year + 1900) << endl
                << "Time of last update (GMT+3): " << currentTime->tm_hour << ":" << currentTime->tm_min << endl
                << "Total salaries of employees: " << totalSalaries << " SR" << endl
                << "Average age of employees: " << avgAge << " y/o" << endl;
    }
}


void backUpData(string fileName, string backupFileName) {
    ofstream backupFile(backupFileName);
    ifstream originFile(fileName);

    string line;
    do {
        if (originFile.is_open() && backupFile.is_open()) {
            getline(originFile, line);
            backupFile << line << endl;
        }
    } while (!originFile.eof());
}

void displayReport() {

    ifstream reportFile(statFileName);
    string line;


    if (reportFile.is_open()) {
        cout << "\n  ---- Report ----  \n";
        do {
            getline(reportFile, line);
            cout << line << endl;
        } while (!reportFile.eof());
    } else {
        cout << "\n ? Sorry. The file couldn't be opened ? \n\n";
    }
}