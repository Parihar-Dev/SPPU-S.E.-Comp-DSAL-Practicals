/*
Company maintains a employee information. The file contains employee id,name,designation and salary. Allow user to
add,delete,display informations.If record of student does not exist an appropriate message is displayed.
use index sequential file to maintain the data.
*/

#include <iostream>
#include <fstream>
using namespace std;
class Employee
{
private:
    int id;
    int salary;
    char name[20];
    char designation[20];

public:
    void setdata()
    {
        cout << "\nEnter Employee ID :- ";
        cin >> id;
        cout << "Enter Employee Name :- ";
        cin >> name;
        cout << "Enter Employee Designation :- ";
        cin >> designation;
        cout << "Enter Employee Salary :- ";
        cin >> salary;
    }
    void display()
    {
        cout << "\nEmployee ID :- " << id << endl;
        cout << "Employee Name :- " << name << endl;
        cout << "Employee Designation :- " << designation << endl;
        cout << "Employee Salary :- " << salary << endl;
    }
    int get_id()
    {
        return id;
    }
};
void write_file()
{
    Employee e;
    ofstream file1, file2;
    int num;
    e.setdata();
    file1.open("index_file.txt", ios::binary | ios::app);
    file2.open("Employee.txt", ios::binary | ios::app);
    num = e.get_id();
    file1.write((char *)&num, sizeof(num));
    file2.write((char *)&e, sizeof(e));
    file1.close();
    file2.close();
}
void read_file()
{
    ifstream file1, file2;
    int num;
    file1.open("Employee.txt", ios::binary);
    file2.open("index_file.txt", ios::binary);
    Employee e;
    cout << "\n\nEmployee file---->" << endl;
    while (file1.read((char *)&e, sizeof(e)))
    {
        e.display();
    }
    cout << "\n\nIndex file ---->" << endl;
    while (file2.read((char *)&num, sizeof(num)))
    {
        cout << num << endl;
    }
    cout << endl
         << endl;
    file1.close();
    file2.close();
}
void search(int num, int record)
{
    ifstream file1, file2;
    int count = 0;
    int id;
    bool found = false;
    Employee e;
    file1.open("index_file.txt", ios::binary);
    file2.open("Employee.txt", ios::binary);
    while (file1.read((char *)&id, sizeof(id)))
    {
        if (id == num)
        {
            found = true;
            break;
        }
        else
        {
            count++;
        }
    }
    if (found)
    {
        file2.seekg((count) * sizeof(e));
        file2.read((char *)&e, sizeof(e));
        e.display();
    }
    else
    {
        cout << "Employee not present in file..." << endl;
    }
    file1.close();
    file2.close();
}
void delete_record(int num)
{
    ifstream file1, file2;
    ofstream file3, file4;
    int id;
    Employee e;
    file1.open("index_file.txt", ios::binary);
    file2.open("Employee.txt", ios::binary);
    file3.open("temp_index_file.txt", ios::binary | ios::app);
    file4.open("temp_Employee.txt", ios::binary | ios::app);
    while (file1.read((char *)&id, sizeof(id)))
    {
        if (id != num)
        {
            file3.write((char *)&id, sizeof(id));
        }
    }
    while (file2.read((char *)&e, sizeof(e)))
    {
        if (e.get_id() != num)
        {
            file4.write((char *)&e, sizeof(e));
        }
    }
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    remove("index_file.txt");
    remove("Employee.txt");
    rename("temp_index_file.txt", "index_file.txt");
    rename("temp_Employee.txt", "Employee.txt");
}
int main()
{
    int ch;
    int i;
    int rec = 0;
    cout << "1.Add Employee." << endl;
    cout << "2.Display all Employee." << endl;
    cout << "3.Search Employee." << endl;
    cout << "4.Delete Employee." << endl;
    cout << "5.Exit." << endl;
    while (true)
    {
        cout << "\nEnter Choice:- ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            rec++;
            write_file();
            break;
        case 2:
            read_file();
            break;
        case 3:
            cout << "\nEnter ID No.:- ";
            cin >> i;
            search(i, rec);
            break;
        case 4:
            cout << "\nEnter ID No. for Deletion :- ";
            cin >> i;
            delete_record(i);
            break;
        case 5:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}
