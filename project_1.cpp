#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
using namespace std;

class Student {
private:
    int id;
    char name[50];
    int age;
    char course[50];

public:
    void input() {
        cout << "Enter ID: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Enter again: ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Age: ";
        while (!(cin >> age) || age <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Age. Enter again: ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Course: ";
        cin.getline(course, 50);
    }

    void display() const {
        cout << "\n------------------------";
        cout << "\nID     : " << id;
        cout << "\nName   : " << name;
        cout << "\nAge    : " << age;
        cout << "\nCourse : " << course;
        cout << "\n------------------------\n";
    }

    int getID() const {
        return id;
    }
};

// 🔍 Check duplicate ID
bool isDuplicate(int id) {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// ➕ Add Student
void addStudent() {
    Student s;

    cout << "\nEnter student details:\n";
    s.input();

    if (isDuplicate(s.getID())) {
        cout << "❌ Error: Student ID already exists!\n";
        return;
    }

    ofstream file("students.dat", ios::binary | ios::app);
    if (!file) {
        cout << "❌ Error opening file!\n";
        return;
    }

    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "✅ Student added successfully!\n";
}

// 📋 Display All
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "⚠ No records found.\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// 🔎 Search Student
void searchStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "❌ Student not found.\n";
}

// ✏ Update Student
void updateStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "❌ File not found!\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "✅ Record updated!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "❌ Student not found.\n";
}

// ❌ Delete Student
void deleteStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    if (!file || !temp) {
        cout << "❌ File error!\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "✅ Student deleted successfully!\n";
    else
        cout << "❌ Student not found.\n";
}

// 📊 Count Students
void countStudents() {
    Student s;
    int count = 0;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        count++;
    }

    file.close();
    cout << "📊 Total Students: " << count << endl;
}

// 🧭 Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== 🎓 Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Count Students\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: countStudents(); break;
            case 7: cout << "👋 Exiting...\n"; break;
            default: cout << "❌ Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}
