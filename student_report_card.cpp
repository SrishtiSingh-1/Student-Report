#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    string rollNumber;
    string name;
    float marksMath;
    float marksScience;
    float marksEnglish;
    float totalMarks;
    float percentage;

public:
    void addStudent();
    void displayStudents();
    void searchStudent();
    void deleteStudent();
    void calculateTotalAndPercentage();
};

void Student::addStudent() {
    fstream file;
    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Marks in Mathematics: ";
    cin >> marksMath;
    cout << "Enter Marks in Science: ";
    cin >> marksScience;
    cout << "Enter Marks in English: ";
    cin >> marksEnglish;

    calculateTotalAndPercentage();

    file.open("reportcard.txt", ios::app | ios::out);
    file << rollNumber << " " << name << " " << marksMath << " " << marksScience << " "
         << marksEnglish << " " << totalMarks << " " << percentage << "\n";
    file.close();
    cout << "Student added successfully!" << endl;
}

void Student::calculateTotalAndPercentage() {
    totalMarks = marksMath + marksScience + marksEnglish;
    percentage = (totalMarks / 300) * 100; // Assuming each subject is out of 100
}

void Student::displayStudents() {
    fstream file;
    file.open("reportcard.txt", ios::in);
    if (!file) {
        cout << "No data is available." << endl;
        file.close();
        return;
    }

    cout << "\nRoll No\tName\tMath\tScience\tEnglish\tTotal\tPercentage\n";
    cout << "-------------------------------------------------------------\n";
    while (file >> rollNumber >> name >> marksMath >> marksScience >> marksEnglish >> totalMarks >> percentage) {
        cout << rollNumber << "\t" << name << "\t" << marksMath << "\t" << marksScience << "\t" 
             << marksEnglish << "\t" << totalMarks << "\t" << percentage << "%" << endl;
    }
    file.close();
}

void Student::searchStudent() {
    fstream file;
    string searchRollNumber;
    bool found = false;

    cout << "Enter Roll Number to search: ";
    cin >> searchRollNumber;

    file.open("reportcard.txt", ios::in);
    if (!file) {
        cout << "No data is available." << endl;
        file.close();
        return;
    }

    while (file >> rollNumber >> name >> marksMath >> marksScience >> marksEnglish >> totalMarks >> percentage) {
        if (rollNumber == searchRollNumber) {
            cout << "\nRoll Number: " << rollNumber << endl;
            cout << "Name: " << name << endl;
            cout << "Marks - Math: " << marksMath << ", Science: " << marksScience 
                 << ", English: " << marksEnglish << endl;
            cout << "Total Marks: " << totalMarks << endl;
            cout << "Percentage: " << percentage << "%" << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Student not found!" << endl;
    }
}

void Student::deleteStudent() {
    fstream file, tempFile;
    string deleteRollNumber;
    bool found = false;

    cout << "Enter Roll Number to delete: ";
    cin >> deleteRollNumber;

    file.open("reportcard.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    if (!file) {
        cout << "No data is available." << endl;
        file.close();
        return;
    }

    while (file >> rollNumber >> name >> marksMath >> marksScience >> marksEnglish >> totalMarks >> percentage) {
        if (rollNumber == deleteRollNumber) {
            found = true;
            cout << "Student deleted successfully!" << endl;
        } else {
            tempFile << rollNumber << " " << name << " " << marksMath << " " << marksScience 
                     << " " << marksEnglish << " " << totalMarks << " " << percentage << "\n";
        }
    }

    file.close();
    tempFile.close();

    remove("reportcard.txt");
    rename("temp.txt", "reportcard.txt");

    if (!found) {
        cout << "Student not found!" << endl;
    }
}

int main() {
    Student student;
    int choice;

    while (true) {
        cout << "\nStudent Report Card System\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                student.addStudent();
                break;
            case 2:
                student.displayStudents();
                break;
            case 3:
                student.searchStudent();
                break;
            case 4:
                student.deleteStudent();
                break;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}