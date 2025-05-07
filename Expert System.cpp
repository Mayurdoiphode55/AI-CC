#include <iostream>
#include <string>
using namespace std;

// Structure to store employee data
struct Employee {
    string name;
    int punctuality;
    int taskCompletion;
    int teamwork;
    int leadership;
};

// Function to input employee data
void inputData(Employee &e) {
    cout << "\nEnter Employee Name: ";
    getline(cin, e.name);

    cout << "Rate the following from 1 (Poor) to 10 (Excellent):\n";

    cout << "Punctuality: ";
    cin >> e.punctuality;

    cout << "Task Completion: ";
    cin >> e.taskCompletion;

    cout << "Teamwork: ";
    cin >> e.teamwork;

    cout << "Leadership: ";
    cin >> e.leadership;

    cin.ignore(); // clear newline from input buffer
}

// Rule-based inference engine
string evaluatePerformance(const Employee &e) {
    int totalScore = e.punctuality + e.taskCompletion + e.teamwork + e.leadership;

    // Explain the reasoning
    cout << "\n--- Evaluation Breakdown ---\n";
    cout << "Total Score: " << totalScore << "/40\n";

    if (totalScore >= 36) {
        cout << "Reason: Excellent in all key areas.\n";
        return "Excellent";
    } else if (totalScore >= 28) {
        cout << "Reason: Good performance with minor improvement areas.\n";
        return "Good";
    } else if (totalScore >= 20) {
        cout << "Reason: Average performance. Needs improvement in some skills.\n";
        return "Average";
    } else {
        cout << "Reason: Below expectations in most areas.\n";
        return "Needs Improvement";
    }
}

// Display result
void displayResult(const Employee &e, string evaluation) {
    cout << "\n=== Performance Report ===\n";
    cout << "Employee: " << e.name << endl;
    cout << "Performance Level: " << evaluation << endl;
    cout << "==========================\n";
}

int main() {
    Employee emp;
    char choice;

    do {
        inputData(emp);
        string result = evaluatePerformance(emp);
        displayResult(emp, result);

        cout << "\nDo you want to evaluate another employee? (y/n): ";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y' || choice == 'Y');

    cout << "\nThank you for using the Expert System!\n";
    return 0;
}
