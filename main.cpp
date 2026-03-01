#include <iostream>
#include <vector>
using namespace std;

class Student {
private:
    int id;
    string name;
    float marks;

public:
    Student(int i, string n, float m) {
        id = i;
        name = n;
        marks = m;
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Marks: " << marks << endl;
        cout << "----------------------" << endl;
    }

    int getId() {
        return id;
    }
};

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\n1. Add Student\n2. Display Students\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            float marks;

            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Marks: ";
            cin >> marks;

            students.push_back(Student(id, name, marks));
            cout << "Student Added Successfully!\n";
        }
        else if (choice == 2) {
            for (auto &s : students) {
                s.display();
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
