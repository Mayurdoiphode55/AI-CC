#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Function to display book recommendations
void recommendBooks(const string& domain) {
    map<string, vector<string>> bookDatabase = {
        {"Artificial Intelligence", {
            "Artificial Intelligence: A Modern Approach by Russell & Norvig",
            "Deep Learning by Ian Goodfellow",
            "Python Machine Learning by Sebastian Raschka"
        }},
        {"Web Development", {
            "Eloquent JavaScript by Marijn Haverbeke",
            "HTML & CSS by Jon Duckett",
            "Learning PHP, MySQL & JavaScript by Robin Nixon"
        }},
        {"Networking", {
            "Computer Networking: A Top-Down Approach by Kurose & Ross",
            "Network Warrior by Gary A. Donahue"
        }},
        {"Data Science", {
            "Hands-On Machine Learning with Scikit-Learn and TensorFlow by Aurélien Géron",
            "Data Science from Scratch by Joel Grus"
        }},
        {"Cyber Security", {
            "The Web Application Hacker's Handbook by Dafydd Stuttard",
            "Hacking: The Art of Exploitation by Jon Erickson"
        }}
    };

    if (bookDatabase.find(domain) != bookDatabase.end()) {
        cout << "\nRecommended books for " << domain << ":\n";
        for (const string& book : bookDatabase[domain]) {
            cout << " - " << book << endl;
        }
    } else {
        cout << "Sorry, no recommendations available for that domain.\n";
    }
}

int main() {
    cout << "===== Library Expert System for Book Recommendation =====\n";
    cout << "Please select your project domain from the following:\n";
    cout << "1. Artificial Intelligence\n";
    cout << "2. Web Development\n";
    cout << "3. Networking\n";
    cout << "4. Data Science\n";
    cout << "5. Cyber Security\n";

    int choice;
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    string domain;
    switch (choice) {
        case 1: domain = "Artificial Intelligence"; break;
        case 2: domain = "Web Development"; break;
        case 3: domain = "Networking"; break;
        case 4: domain = "Data Science"; break;
        case 5: domain = "Cyber Security"; break;
        default:
            cout << "Invalid choice.\n";
            return 0;
    }

    recommendBooks(domain);

    return 0;
}
