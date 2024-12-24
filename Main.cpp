#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <windows.h>

using namespace std;

struct Theme {
    string foregroundColor;
    string backgroundColor;
};

void applyTheme(const Theme& theme) {
    cout << "\033[1;" << theme.foregroundColor << ";48;5;" << theme.backgroundColor << "m";
}

void resetColor() {
    cout << "\033[0m";  // Reset terminal color
}

void playAlarmSound(int beeps, int interval) {
    for (int i = 0; i < beeps; ++i) {
        Beep(200, 6000); // Beep at 130 Hz for 8 second
        this_thread::sleep_for(chrono::seconds(interval)); // Wait for the specified interval
    }
}

void displayClock(int alarmHour, int alarmMinute, const Theme& theme) {
    while (true) {
        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        auto localTime = *localtime(&time);

        applyTheme(theme);
        cout << "\r" << put_time(&localTime, "%H:%M:%S") << flush;
        resetColor();

        if (localTime.tm_hour == alarmHour && localTime.tm_min == alarmMinute) {
            cout << "\nAlarm ringing..." << endl;
            playAlarmSound(4, 1); // Play beep 3 times with 1-second intervals
            break; // Exit the loop
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    int alarmHour, alarmMinute;
    Theme theme = {"36", "44"}; // Customizable theme colors

    cout << "\"Time's an Illusion\"\nA Mesmerizing Concept.\nBut we still use dates in such boring ways...\n"
    "Weeks, Months and Years. Even \"A Day\" is Manipulatuve;\nThinking that we get to build a"
    " good day tomorrow, is an illusion of a second chance.\nWho gets a \"second\" chance?\nUs Shameless"
    " People. Asking for nth chance.\nAnd we're given that! Don't we forget again?\nDon't You..?"
    "\nEvery Moment is Magical and Unique.\nand you're still busy working on distractions."
    "\ngo ahead and set your alarm...\nEnter alarm time (HH MM): ";
    cin >> alarmHour >> alarmMinute;

    cout << "Digital Clock with Alarm - Press Ctrl+C to stop\n";
    displayClock(alarmHour, alarmMinute, theme);
    
    return 0;
}
