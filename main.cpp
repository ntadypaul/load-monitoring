#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Appliance {
    string name;
    double power;
    double hours;
};

Appliance appliances[100];
int applianceCount = 0;


// LOAD appliances from file
void loadAppliances() {

    ifstream file("appliances.txt");

    if (!file) return;

    while (file >> appliances[applianceCount].name
                >> appliances[applianceCount].power
                >> appliances[applianceCount].hours) {

        applianceCount++;

        if (applianceCount >= 100) break;
    }

    file.close();
}


// SAVE appliances to file
void saveAppliances() {

    ofstream file("appliances.txt");

    for (int i = 0; i < applianceCount; i++) {

        file << appliances[i].name << " "
             << appliances[i].power << " "
             << appliances[i].hours << endl;
    }

    file.close();
}


// REGISTER appliance
void registerAppliance() {

    if (applianceCount >= 100) {
        cout << "Maximum appliance limit reached.\n";
        return;
    }

    cout << "Enter appliance name: ";
    cin.ignore();
    getline(cin, appliances[applianceCount].name);

    cout << "Enter power rating (W): ";
    cin >> appliances[applianceCount].power;

    cout << "Enter daily usage hours: ";
    cin >> appliances[applianceCount].hours;

    applianceCount++;

    cout << "Appliance registered successfully.\n";
}


// VIEW appliances
void viewAppliances() {

    if (applianceCount == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    for (int i = 0; i < applianceCount; i++) {

        cout << "\nAppliance " << i + 1 << endl;
        cout << "Name: " << appliances[i].name << endl;
        cout << "Power: " << appliances[i].power << " W\n";
        cout << "Usage: " << appliances[i].hours << " hours/day\n";
    }
}


// SEARCH appliance
void searchAppliance() {

    string searchName;
    bool found = false;

    cin.ignore();
    cout << "Enter appliance name to search: ";
    getline(cin, searchName);

    for (int i = 0; i < applianceCount; i++) {

        if (appliances[i].name == searchName) {

            cout << "\nAppliance Found:\n";
            cout << "Name: " << appliances[i].name << endl;
            cout << "Power: " << appliances[i].power << " W\n";
            cout << "Usage: " << appliances[i].hours << " hours/day\n";

            found = true;
        }
    }

    if (!found) cout << "Appliance not found.\n";
}


// REMOVE appliance
void removeAppliance() {

    string name;
    bool found = false;

    cin.ignore();
    cout << "Enter appliance name to remove: ";
    getline(cin, name);

    for (int i = 0; i < applianceCount; i++) {

        if (appliances[i].name == name) {

            for (int j = i; j < applianceCount - 1; j++) {
                appliances[j] = appliances[j + 1];
            }

            applianceCount--;

            cout << "Appliance removed.\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "Appliance not found.\n";
}


// ENERGY calculation
void calculateEnergy() {

    double totalEnergy = 0;

    if (applianceCount == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    for (int i = 0; i < applianceCount; i++) {

        double energy = (appliances[i].power * appliances[i].hours) / 1000;

        cout << "\nAppliance: " << appliances[i].name << endl;
        cout << "Energy Used: " << energy << " kWh\n";

        totalEnergy += energy;
    }

    cout << "\nTotal Energy Consumption: " << totalEnergy << " kWh\n";
}


// BILLING summary
void billingSummary() {

    double tariff;
    double totalEnergy = 0;

    cout << "Enter electricity tariff (per kWh): ";
    cin >> tariff;

    for (int i = 0; i < applianceCount; i++) {

        totalEnergy += (appliances[i].power * appliances[i].hours) / 1000;
    }

    double totalCost = totalEnergy * tariff;

    cout << "\nTotal Energy: " << totalEnergy << " kWh\n";
    cout << "Total Electricity Cost: " << totalCost << endl;
}



int main() {

    int choice;

    loadAppliances();

    do {

        cout << "\nElectrical Load Monitoring System\n";
        cout << "1. Register Appliance\n";
        cout << "2. View All Appliances\n";
        cout << "3. Search Appliance\n";
        cout << "4. Remove Appliance\n";
        cout << "5. Calculate Energy Consumption\n";
        cout << "6. Billing Summary\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            registerAppliance();
            break;

        case 2:
            viewAppliances();
            break;

        case 3:
            searchAppliance();
            break;

        case 4:
            removeAppliance();
            break;

        case 5:
            calculateEnergy();
            break;

        case 6:
            billingSummary();
            break;

        case 7:
            saveAppliances();
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}