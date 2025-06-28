#include <iostream>
#include <string>

using namespace std;

// --- Global variables for the current time ---
unsigned int currentHour = 0;
unsigned int currentMinute = 0;
unsigned int currentSecond = 0;

// --- Helper function: returns a two-digit string for a number ---
string twoDigitString(unsigned int n) {
    if (n < 10) {
        return "0" + to_string(n);
    }
    else {
        return to_string(n);
    }
}

// --- Helper function: returns a string of 'n' copies of character 'c' ---
string nCharString(size_t n, char c) {
    return string(n, c);
}

// --- Format time as 24-hour string "HH:MM:SS" ---
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);
}

// --- Format time as 12-hour string "HH:MM:SS AM/PM" ---
string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
    string period = (h < 12) ? "AM" : "PM";
    unsigned int displayHour = h % 12;
    if (displayHour == 0) {
        displayHour = 12;
    }
    return twoDigitString(displayHour) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + " " + period;
}

// --- Display the two clocks side by side ---
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
    cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;

    cout << "*" << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << "*   "
        << "*" << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << "*" << endl << endl;

    cout << "*" << nCharString(6, ' ') << formatTime12(h, m, s) << nCharString(7, ' ') << "*   "
        << "*" << nCharString(8, ' ') << formatTime24(h, m, s) << nCharString(9, ' ') << "*" << endl;

    cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
}

// --- Print the user menu ---
void printMenu(char* strings[], unsigned int numStrings, unsigned char width) {
    cout << nCharString(width, '*') << endl;

    for (unsigned int i = 0; i < numStrings; ++i) {
        string itemNum = to_string(i + 1);
        string menuText = string(strings[i]);
        string lineContent = "* " + itemNum + " - " + menuText;

        size_t spacesToAdd = width - lineContent.length() - 1; // -1 for closing '*'
        lineContent += nCharString(spacesToAdd, ' ') + "*";

        cout << lineContent << endl;

        if (i < numStrings - 1) {
            cout << endl; // blank line between items except last
        }
    }

    cout << nCharString(width, '*') << endl;
}

// --- Get a valid menu choice from the user ---
unsigned int getMenuChoice(unsigned int maxChoice) {
    unsigned int choice;

    while (true) {
        cout << "Enter choice (1-" << maxChoice << "): ";
        cin >> choice;

        if (!cin.fail() && choice >= 1 && choice <= maxChoice) {
            cin.ignore(10000, '\n'); // clear input buffer
            return choice;
        }

        cout << "Invalid input. Try again." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// --- Getter and setter functions for time ---
unsigned int getHour() { return currentHour; }
void setHour(unsigned int h) { currentHour = h % 24; }

unsigned int getMinute() { return currentMinute; }
void setMinute(unsigned int m) { currentMinute = m % 60; }

unsigned int getSecond() { return currentSecond; }
void setSecond(unsigned int s) { currentSecond = s % 60; }

// --- Add one hour with wrap-around ---
void addOneHour() {
    unsigned int hr = getHour();
    setHour((hr < 23) ? hr + 1 : 0);
}

// --- Add one minute with wrap-around, increment hour if needed ---
void addOneMinute() {
    unsigned int min = getMinute();
    if (min < 59) {
        setMinute(min + 1);
    }
    else {
        setMinute(0);
        addOneHour();
    }
}

// --- Add one second with wrap-around, increment minute if needed ---
void addOneSecond() {
    unsigned int sec = getSecond();
    if (sec < 59) {
        setSecond(sec + 1);
    }
    else {
        setSecond(0);
        addOneMinute();
    }
}

// --- The main menu loop ---
void mainMenu() {
    char* menuOptions[] = {
        (char*)"Add One Hour",
        (char*)"Add One Minute",
        (char*)"Add One Second",
        (char*)"Exit Program"
    };
    unsigned int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    unsigned char menuWidth = 35;

    unsigned int choice;

    do {
        displayClocks(getHour(), getMinute(), getSecond());
        printMenu(menuOptions, numOptions, menuWidth);
        choice = getMenuChoice(numOptions);

        if (choice == 1) addOneHour();
        else if (choice == 2) addOneMinute();
        else if (choice == 3) addOneSecond();
        else if (choice == 4) cout << "Exiting program. Goodbye!" << endl;

        cout << endl;
    } while (choice != 4);
}

// --- Main program entry point ---
int main() {
    // Initialize the time to 00:00:00
    setHour(0);
    setMinute(0);
    setSecond(0);

    mainMenu();

    return 0;
}
