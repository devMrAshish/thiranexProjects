#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Student
{
    int rollNo;
    char name[50];
    float marks;
};

void addStudent()
{
    Student s;

    ofstream file("students.txt", ios::app);

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Marks: ";
    cin >> s.marks;

    file << s.rollNo << " "
         << s.name << " "
         << s.marks << endl;

    file.close();

    cout << "\nRecord Added Successfully!\n";
}

void displayStudents()
{
    Student s;

    ifstream file("students.txt");

    cout << "\n----- STUDENT RECORDS -----\n";

    while(file >> s.rollNo >> s.name >> s.marks)
    {
        cout << "\nRoll No : " << s.rollNo;
        cout << "\nName    : " << s.name;
        cout << "\nMarks   : " << s.marks;
        cout << "\n---------------------------";
    }

    file.close();
}

void searchStudent()
{
    int roll;
    bool found = false;

    Student s;

    ifstream file("students.txt");

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    while(file >> s.rollNo >> s.name >> s.marks)
    {
        if(s.rollNo == roll)
        {
            cout << "\nStudent Found!\n";
            cout << "Roll No : " << s.rollNo << endl;
            cout << "Name    : " << s.name << endl;
            cout << "Marks   : " << s.marks << endl;

            found = true;
            break;
        }
    }

    if(!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

void updateStudent()
{
    int roll;
    bool found = false;

    Student s;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    while(file >> s.rollNo >> s.name >> s.marks)
    {
        if(s.rollNo == roll)
        {
            found = true;

            cout << "\nEnter New Name: ";
            cin >> s.name;

            cout << "Enter New Marks: ";
            cin >> s.marks;
        }

        temp << s.rollNo << " "
             << s.name << " "
             << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        cout << "\nRecord Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void deleteStudent()
{
    int roll;
    bool found = false;

    Student s;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    while(file >> s.rollNo >> s.name >> s.marks)
    {
        if(s.rollNo == roll)
        {
            found = true;
            continue;
        }

        temp << s.rollNo << " "
             << s.name << " "
             << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}