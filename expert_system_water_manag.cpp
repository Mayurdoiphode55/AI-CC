#include <iostream>
#include <string>
using namespace std;

// Expert System Class
class SocietyExpertSystem {
public:
    string day;
    bool tank_cleaning;
    bool electricity;
    string bulb_status;
    string switch_status;

    // Constructor
    SocietyExpertSystem(string d, bool tc, bool elec, string bulb, string sw)
        : day(d), tank_cleaning(tc), electricity(elec), bulb_status(bulb), switch_status(sw) {}

    void checkWaterSupply() {
        if (day == "Monday" && tank_cleaning) {
            cout << "Water supply was off on Monday due to scheduled tank cleaning.\n";
        } else {
            cout << "No known issue with water supply on " << day << ".\n";
        }
    }

    void checkPassageLight() {
        if (!electricity) {
            cout << "No lights in the common passage due to power outage.\n";
        } else if (bulb_status == "faulty") {
            cout << "No lights in the common passage due to a faulty bulb.\n";
        } else if (switch_status == "off") {
            cout << "No lights in the common passage because the switch is off.\n";
        } else {
            cout << "Common passage lights are working properly.\n";
        }
    }
};

// Main Function
int main() {
    // Example situation: Monday, cleaning true, electricity true, faulty bulb
    SocietyExpertSystem system("Monday", true, true, "faulty", "on");

    cout << "===== Society Maintenance Expert System =====\n";
    cout << "a) Why was there no water supply on Monday?\n";
    system.checkWaterSupply();

    cout << "\nb) Why were there no lights in common passage?\n";
    system.checkPassageLight();

    return 0;
}
