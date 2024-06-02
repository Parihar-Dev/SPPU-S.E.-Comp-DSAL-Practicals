/*
Department maintains a student information. The file contains roll number,name,division and address. Allow user to
add,delete,display informations.If record of student does not exist an appropriate message is displayed.
use sequential file to maintain the data.
*/

#include <iostream>
#include <fstream>
using namespace std;

class Student
{
private:
    char name[50];
    int roll;
    char div[50];
    char add[50];

public:
    void get_data()
    {
        cout << "\nEnter Student Roll No.:- ";
        cin >> roll;
        cout << "Enter Student Name:- ";
        cin >> name;
        cout << "Enter Student Division:- ";
        cin >> div;
        cout << "Enter Student Address:- ";
        cin >> add;
        cout << endl;
    }
    void display_data()
    {
        cout << "\nStudent Roll:- " << roll << endl;
        cout << "Student Name:- " << name << endl;
        cout << "Student Division:- " << div << endl;
        cout << "Student Address:- " << add << endl;
        cout << endl;
    }
    int get_roll()
    {
        return roll;
    }
};
void write_file()
{
    Student s;
    ofstream file;
    s.get_data();
    file.open("Student.txt", ios::binary | ios::app);
    file.write((char *)&s, sizeof(s));
    file.close();
}
void read_file()
{
    ifstream file;
    file.open("Student.txt", ios::binary);
    Student s;
    while (file.read((char *)&s, sizeof(s)))
    {
        s.display_data();
    }
    file.close();
}
void search(int roll)
{
    ifstream file;
    file.open("Student.txt", ios::binary);
    Student s;
    while (file.read((char *)&s, sizeof(s)))
    {
        if (s.get_roll() == roll)
        {
            cout << "\nRecord found---->" << endl;
            s.display_data();
            file.close();
            return;
        }
    }
    cout << "\nRecord Not present in File..." << endl;
    file.close();
}
void delete_data(int roll)
{
    ifstream file1;
    ofstream file2;
    Student s;
    file1.open("Student.txt", ios::binary);
    file2.open("Temp.txt", ios::app | ios::binary);
    while (file1.read((char *)&s, sizeof(s)))
    {
        if (s.get_roll() != roll)
        {
            file2.write((char *)&s, sizeof(s));
        }
    }
    file1.close();
    file2.close();
    remove("Student.txt");
    rename("Temp.txt", "Student.txt");
}
int main()
{
    int ch;
    int r;
    cout << "1.Add record." << endl;
    cout << "2.Display all record." << endl;
    cout << "3.Search Record." << endl;
    cout << "4.Delete Record." << endl;
    cout << "5.Exit." << endl;
    while (true)
    {
        cout << "\nEnter Choice:- ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            write_file();
            break;
        case 2:
            read_file();
            break;
        case 3:
            cout << "\nEnter Roll No.:- ";
            cin >> r;
            search(r);
            break;
        case 4:
            cout << "\nEnter Roll No.:- ";
            cin >> r;
            delete_data(r);
            cout << "Successfully Deleted " << r << " Data." << endl;
            break;
        case 5:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}
