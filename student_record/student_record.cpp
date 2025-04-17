#include<bits/stdc++.h> 


using namespace std;


// Student class
class Student {
private:
    string name; // Name of the student
    int rollNumber; // Roll number of the student

public:
    // Constructor
    Student(const string& _name, int _rollNumber) : name(_name), rollNumber(_rollNumber) {}

    // Getter for name
    const string& getName() const { return name; }

    // Getter for roll number
    int getRollNumber() const { return rollNumber; }

    // Display student details
    void display() const {
        cout << "Roll Number: " << rollNumber << "\tName: " << name << std::endl;
    }
};

// Student Record System class
class StudentRecordSystem {
private:
    std::vector<Student> students; // Vector to store student records
    const std::string filename; // File name for storing records

public:
    // Constructor
    StudentRecordSystem(const string& _filename) : filename(_filename) {}
    ~StudentRecordSystem(){
    	remove(filename.c_str());
    }

    // Add a student to the record system
    void addStudent(const Student& student) {
        students.push_back(student);
        sortRecords();
        saveToFile();
    }

    // Delete a student from the record system
    void deleteStudent(int rollNumber) {
        students.erase(std::remove_if(students.begin(), students.end(),
            DeleteStudentPredicate(rollNumber)), students.end());
        saveToFile();
    }

    // Modify a student's details in the record system
    void modifyStudent(int rollNumber, const std::string& newName) {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].getRollNumber() == rollNumber) {
                students[i] = Student(newName, rollNumber);
                sortRecords();
                saveToFile();
                return;
            }
        }
        std::cout << "Student with Roll Number " << rollNumber << " not found." << std::endl;
    }

    // Display all students in the record system
    void displayAllStudents() const {
        for (size_t i = 0; i < students.size(); ++i) {
            students[i].display();
        }
    }

    // Load student records from file
    void loadFromFile() {
        std::ifstream file(filename.c_str(), std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        students.clear();
        while (file.good() && !file.eof()) {
            Student student("", 0);
            file.read(reinterpret_cast<char*>(&student), sizeof(Student));
            if (file.eof()) {
                break;
            }
            students.push_back(student);
        }

        file.close();
        sortRecords();
    }

private:
    // Predicate for deleting a student
    struct DeleteStudentPredicate {
        int targetRollNumber;

        DeleteStudentPredicate(int rollNumber) : targetRollNumber(rollNumber) {}

        bool operator()(const Student& s) const {
            return s.getRollNumber() == targetRollNumber;
        }
    };

    // Sort student records
    void sortRecords() {
        std::sort(students.begin(), students.end(), CompareStudents());
    }

    // Comparator for sorting students
    struct CompareStudents {
        bool operator()(const Student& a, const Student& b) const {
            return a.getRollNumber() < b.getRollNumber();
        }
    };

    // Save student records to file
    void saveToFile() const {
        std::ofstream file(filename.c_str(), std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (size_t i = 0; i < students.size(); ++i) {
            file.write(reinterpret_cast<const char*>(&students[i]), sizeof(Student));
        }

        file.close();
    }
};

int main() {
    // Create a StudentRecordSystem object
    StudentRecordSystem recordSystem("student_records.dat");
    recordSystem.loadFromFile();
    unordered_set<int> exist_rollnumber;
    int userChoice; // User's choice in the menu
    do {
        std::cout << "\nStudent Record System Menu:" << std::endl;
        std::cout << "1. Add Student\n2. Delete Student\n3. Modify Student\n4. Display All Students\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;

        switch (userChoice) { // Switch based on the user's choice
	    case 1: { // Case 1: Add a student
		std::string studentName; // Name of the student
		int rollNumber; // Roll number of the student
		std::cout << "Enter Student Name: ";
		std::cin.ignore(); std::getline(std::cin, studentName); // Get the student's name
		std::cout << "Enter Roll Number: ";
		std::cin >> rollNumber; // Get the student's roll number
		while(exist_rollnumber.find(rollNumber)!=exist_rollnumber.end()){
			cout<<"Roll Number already exist, Choose another roll number"<<endl;
			cin>>rollNumber;
		}
		exist_rollnumber.insert(rollNumber);
		recordSystem.addStudent(Student(studentName, rollNumber)); // Add the student to the record system
		break;
	    }
	    case 2: { // Case 2: Delete a student
		int rollNumber; // Roll number of the student to delete
		std::cout << "Enter Roll Number to Delete: ";
		std::cin >> rollNumber; // Get the roll number
		recordSystem.deleteStudent(rollNumber); // Delete the student from the record system
		break;
	    }
	    case 3: { // Case 3: Modify a student
		int rollNumber; // Roll number of the student to modify
		std::string newName; // New name for the student
		std::cout << "Enter Roll Number to Modify: ";
		std::cin >> rollNumber; // Get the roll number
		std::cout << "Enter New Name: ";
		std::cin.ignore();
		std::getline(std::cin, newName); // Get the new name
		recordSystem.modifyStudent(rollNumber, newName); // Modify the student in the record system
		break;
	    }
	    case 4: // Case 4: Display all students
		recordSystem.displayAllStudents(); // Display all students in the record system
		break;
	    case 5: // Case 5: Exit the system
		std::cout << "Exiting Student Record System." << std::endl;
		break;
	    default: // Default case: Invalid choice
		std::cout << "Invalid choice. Please try again." << std::endl;
	    }

	} while (userChoice != 5); // Continue until the user chooses to exit
   return 0;  
}

