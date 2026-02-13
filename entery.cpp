#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 50;
const int DAYS = 7;
const int SUBJECTS = 4;
const int NAME_WIDTH = 25;
const int REG_WIDTH  = 18;

// Function Prototypes
void inputStudent(string names[], string regNos[],
                  char attendance[][DAYS],
                  int marks[][SUBJECTS],
                  int &count,
                  string subjects[]);

void displayAll(const string names[], const string regNos[],
                const char attendance[][DAYS],
                const int marks[][SUBJECTS],
                int count,
                string subjects[]);

string trimForDisplay(const string &text, int width);

// Main Function
int main() {
    string names[MAX];
    string regNos[MAX];
    char attendance[MAX][DAYS];
    int marks[MAX][SUBJECTS];

    string subjects[SUBJECTS] = {"English", "Math", "Urdu", "Science"};

    int count = 0;
    char choice;

    cout << "===== STUDENT RECORD ENTRY SYSTEM =====\n";

    do {
        if (count >= MAX) {
            cout << "\nMaximum student limit reached.\n";
            break;
        }

        inputStudent(names, regNos, attendance, marks, count, subjects);

        cout << "\nDo you want to enter another student? (y/n): ";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y' || choice == 'Y');

    displayAll(names, regNos, attendance, marks, count, subjects);
    return 0;
}

// Function Definitions

void inputStudent(string names[], string regNos[],
                  char attendance[][DAYS],
                  int marks[][SUBJECTS],
                  int &count,
                  string subjects[]) {

    cout << "\nEnter student full name: ";
    getline(cin, names[count]);

    cout << "Enter registration number: ";
    getline(cin, regNos[count]);

    // Weekly Attendance
    cout << "\nEnter attendance for 7 days (P/A):\n";
    for (int d = 0; d < DAYS; d++) {
        do {
            cout << "Day " << d + 1 << ": ";
            cin >> attendance[count][d];
            attendance[count][d] = toupper(attendance[count][d]);
        } while (attendance[count][d] != 'P' && attendance[count][d] != 'A');
    }

    // Marks with subject names
    cout << "\nEnter marks of subjects:\n";
    for (int s = 0; s < SUBJECTS; s++) {
        do {
            cout << subjects[s] << " marks (0-100): ";
            cin >> marks[count][s];
        } while (marks[count][s] < 0 || marks[count][s] > 100);
    }

    cin.ignore();
    count++;

    cout << "\nStudent record saved successfully.\n";
}

void displayAll(const string names[], const string regNos[],
                const char attendance[][DAYS],
                const int marks[][SUBJECTS],
                int count,
                string subjects[]) {

    if (count == 0) {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\n=========== ALL STUDENT RECORDS ===========\n";

    cout << left
         << setw(NAME_WIDTH) << "Name"
         << setw(REG_WIDTH)  << "Reg No"
         << setw(16)         << "Attendance"
         << setw(30)         << "Marks (English Math Urdu Science)"
         << endl;

    cout << string(95, '-') << endl;

    for (int i = 0; i < count; i++) {
        cout << left
             << setw(NAME_WIDTH) << trimForDisplay(names[i], NAME_WIDTH - 1)
             << setw(REG_WIDTH)  << trimForDisplay(regNos[i], REG_WIDTH - 1);

        // Attendance
        for (int d = 0; d < DAYS; d++) {
            cout << attendance[i][d] << " ";
        }

        cout << "   ";

        // Marks
        for (int s = 0; s < SUBJECTS; s++) {
            cout << marks[i][s] << " ";
        }

        cout << endl;
    }
}

// Trims long text so table layout remains intact
string trimForDisplay(const string &text, int width) {
    if (text.length() <= width)
        return text;
    return text.substr(0, width - 3) + "...";
}