#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

// Function prototypes for organization and readability
void printMenu();
void findItemFrequency(const map<string, int>& items);
void printAllItems(const map<string, int>& items);
void printHistogram(const map<string, int>& items);
map<string, int> loadItemsFromFile(const string& filename);
void createBackupDataFile(const map<string, int>& items, const string& filename);

int main() {
    // Load items from the input file and then create a backup data file
    map<string, int> itemFrequencies = loadItemsFromFile("CS210_Project_Three_Input_File.txt");
    createBackupDataFile(itemFrequencies, "frequency.dat");

    int choice;
    // Infinite loop to display the menu until the user decides to exit
    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore(); // To consume the newline character left by cin

        // Switch to execute user's choice
        switch (choice) {
        case 1:
            findItemFrequency(itemFrequencies);
            break;
        case 2:
            printAllItems(itemFrequencies);
            break;
        case 3:
            printHistogram(itemFrequencies);
            break;
        case 4:
            cout << "Exiting program." << endl;
            return 0; // Exit the program
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

// Display menu options to the user
void printMenu() {
    cout << "\nMenu Options:\n"
        << "1. Find item frequency\n"
        << "2. Print all items and frequencies\n"
        << "3. Print histogram of item frequencies\n"
        << "4. Exit\n"
        << "Enter your choice: ";
}

// Find and display the frequency of a specified item
void findItemFrequency(const map<string, int>& items) {
    string item;
    cout << "Enter item name: ";
    getline(cin, item); // Read the full line for item names that may contain spaces

    auto it = items.find(item); // Search for the item in the map
    if (it != items.end()) {
        cout << item << " appears " << it->second << " times." << endl;
    }
    else {
        cout << item << " not found." << endl;
    }
}

// Print all items and their frequencies
void printAllItems(const map<string, int>& items) {
    for (const auto& pair : items) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Print a histogram showing item frequencies
void printHistogram(const map<string, int>& items) {
    for (const auto& pair : items) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*"; // Use '*' to visually represent frequency
        }
        cout << endl;
    }
}

// Load item frequencies from a file
map<string, int> loadItemsFromFile(const string& filename) {
    map<string, int> items;
    ifstream inputFile(filename); // Open the file for reading
    string item;

    if (!inputFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return items; // Return an empty map if file opening fails
    }

    while (getline(inputFile, item)) {
        items[item]++; // Increment the frequency for each item read
    }

    inputFile.close(); // Close the file when done
    return items; // Return the map of items and their frequencies
}

// Create a backup data file from the items map
void createBackupDataFile(const map<string, int>& items, const string& filename) {
    ofstream outputFile(filename); // Open the file for writing
    if (!outputFile.is_open()) {
        cerr << "Failed to create backup file: " << filename << endl;
        return;
    }

    for (const auto& pair : items) {
        outputFile << pair.first << " " << pair.second << endl; // Write each item and its frequency
    }

    outputFile.close(); // Close the file when done
    cout << "Backup data has been saved to " << filename << "." << endl;
}
