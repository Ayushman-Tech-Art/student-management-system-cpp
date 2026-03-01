#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Student {
private:
    int id;
    string name;
    float marks;

public:
    Student(int i = 0, string n = "", float m = 0.0) 
        : id(i), name(n), marks(m) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    float getMarks() const { return marks; }

    // Setters
    void setName(string n) { name = n; }
    void setMarks(float m) { marks = m; }

    void display() const {
        cout << "ID: " << id 
             << " | Name: " << name 
             << " | Marks: " << fixed << setprecision(2) << marks << endl;
    }

    // Save to file
    string toFile() const {
        return to_string(id) + "," + name + "," + to_string(marks);
    }

    // Load from file
    static Student fromString(const string& line) {
        stringstream ss(line);
        string idStr, name, marksStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, marksStr, ',');
        return Student(stoi(idStr), name, stof(marksStr));
    }
};

class StudentManager {
private:
    vector<Student> students;
    string filename = "students.txt";

public:
    StudentManager() {
        loadFromFile();
    }

    // Check if ID exists
    bool idExists(int id) const {
        for (const auto& s : students) {
            if (s.getId() == id) return true;
        }
        return false;
    }

    // Input validation
    int getValidId() const {
        int id;
        while (true) {
            if (cin >> id && id > 0) return id;
            cout << "Invalid! Enter positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    float getValidMarks() const {
        float marks;
        while (true) {
            if (cin >> marks && marks >= 0 && marks <= 100) return marks;
            cout << "Invalid! Enter 0-100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void addStudent() {
        cout << "\n--- Add Student ---\n";
        int id;
        cout << "Enter ID: ";
        id = getValidId();

        if (idExists(id)) {
            cout << "❌ ID already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        string name;
        cin >> name;

        cout << "Enter Marks (0-100): ";
        float marks = getValidMarks();

        students.push_back(Student(id, name, marks));
        saveToFile();
        cout << "✅ Student added!\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "No students found!\n";
            return;
        }
        cout << "\n--- All Students ---\n";
        for (const auto& s : students) {
            s.display();
        }
    }

    void searchStudent() const {
        cout << "Enter ID to search: ";
        int id = getValidId();

        for (const auto& s : students) {
            if (s.getId() == id) {
                cout << "\n--- Student Found ---\n";
                s.display();
                return;
            }
        }
        cout << "❌ Student not found!\n";
    }

    void deleteStudent() {
        cout << "Enter ID to delete: ";
        int id = getValidId();

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getId() == id) {
                students.erase(it);
                saveToFile();
                cout << "✅ Student deleted!\n";
                return;
            }
        }
        cout << "❌ Student not found!\n";
    }

    void saveToFile() const {
        ofstream file(filename);
        for (const auto& s : students) {
            file << s.toFile() << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        string line;
        while (getline(file, line)) {
            students.push_back(Student::fromString(line));
        }
        file.close();
    }
};

int main() {
    StudentManager sm;
    int choice;

    while (true) {
        cout << "\n========== MENU ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "==========================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sm.addStudent(); break;
            case 2: sm.displayAll(); break;
            case 3: sm.searchStudent(); break;
            case 4: sm.deleteStudent(); break;
            case 5: 
                cout << "Goodbye!\n";
                return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
}
