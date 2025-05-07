#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Convert input to lowercase
string toLowerCase(string input) {
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

// Chatbot response engine
void chatbotResponse(string userInput) {
    string input = toLowerCase(userInput);

    if (input.find("order") != string::npos || input == "1") {
        cout << "🤖 Chatbot: You can track or cancel your order from the 'My Orders' section.\n";
    } else if (input.find("return") != string::npos || input.find("refund") != string::npos || input == "2") {
        cout << "🤖 Chatbot: Returns are accepted within 7 days. Refunds are processed in 5 business days.\n";
    } else if (input.find("payment") != string::npos || input.find("bill") != string::npos || input == "3") {
        cout << "🤖 Chatbot: We accept UPI, Cards, and Net Banking. Check your order invoice in 'Billing'.\n";
    } else if (input.find("delivery") != string::npos || input.find("shipping") != string::npos || input == "4") {
        cout << "🤖 Chatbot: Standard delivery is 3–5 days. Delays possible due to weather or holidays.\n";
    } else if (input.find("account") != string::npos || input == "5") {
        cout << "🤖 Chatbot: You can update your address, phone, or password in 'Account Settings'.\n";
    } else if (input.find("product") != string::npos || input == "6") {
        cout << "🤖 Chatbot: Please mention the product name to get details like price, stock, or warranty.\n";
    } else if (input.find("offer") != string::npos || input.find("discount") != string::npos || input == "7") {
        cout << "🤖 Chatbot: Today's offer: Get 10% OFF on orders above ₹999 using code SAVE10.\n";
    } else if (input.find("complaint") != string::npos || input == "8") {
        cout << "🤖 Chatbot: We're sorry! Please email support@smartshop.com or call 1800-123-456.\n";
    } else if (input.find("exit") != string::npos || input.find("bye") != string::npos || input == "9") {
        cout << "🤖 Chatbot: Thank you for contacting SmartShop. Have a nice day! 🙏\n";
    } else {
        cout << "🤖 Chatbot: Sorry, I didn’t understand. Please choose a menu option or type a related word.\n";
    }
}

// Menu display
void showMenu() {
    cout << "\n======= SmartShop Help Menu =======\n";
    cout << "1. Order-related queries\n";
    cout << "2. Return/Refund policy\n";
    cout << "3. Payment and Billing\n";
    cout << "4. Delivery Information\n";
    cout << "5. Account Management\n";
    cout << "6. Product Information\n";
    cout << "7. Offers and Discounts\n";
    cout << "8. Complaints\n";
    cout << "9. Exit\n";
    cout << "===================================\n";
}

int main() {
    string userInput;

    cout << "🛒 Welcome to SmartShop Customer Support Chatbot!\n";
    cout << "Type your query or choose from the menu below.\n";

    while (true) {
        showMenu();
        cout << "\nYou: ";
        getline(cin, userInput);

        if (toLowerCase(userInput) == "9" || toLowerCase(userInput).find("exit") != string::npos)
            break;

        chatbotResponse(userInput);
    }

    return 0;
}
