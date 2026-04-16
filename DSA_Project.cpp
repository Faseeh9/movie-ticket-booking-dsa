#include <iostream>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

const int ROWS = 5;
const int COLS = 6;

struct Seat {
    string name = "";
    string category = "Regular"; 
    bool isBooked = false;
};

struct ShowNode {
    string showName;
    Seat seats[ROWS][COLS];
    queue<string> waitlist;
    ShowNode* next = NULL;
};

ShowNode* createGraph() {
    ShowNode* afternoon = new ShowNode{"Afternoon"};
    ShowNode* evening = new ShowNode{"Evening"};

    afternoon->next = evening;
    return afternoon;
}

void displaySeats(ShowNode* show) {
    cout << "\n========== Seat Layout for " << show->showName << " Show ==========" << endl;
    cout << "       ";
    for (int j = 0; j < COLS; ++j)
        cout << setw(5) << j + 1;
    cout << endl;

    for (int i = 0; i < ROWS; ++i) {
        cout << "Row " << setw(2) << i + 1 << " ";
        for (int j = 0; j < COLS; ++j) {
            Seat& s = show->seats[i][j];
            if (s.isBooked) {
                cout << setw(5) << "[X]";
            } else {
                cout << setw(5) << (i < 1 ? "[V]" : "[R]"); 
            }
        }
        cout << endl;
    }
    cout << "[V]: VIP Seat | [R]: Regular Seat | [X]: Booked\n";
}

ShowNode* selectShow(ShowNode* head) {
    int choice;
    ShowNode* temp = head;
    cout << "\nSelect a Show:\n";
    int index = 1;
    while (temp != nullptr) {
        cout << index++ << ". " << temp->showName << endl;
        temp = temp->next;
    }
    cout << "Enter choice: ";
    cin >> choice;

    temp = head;
    for (int i = 1; i < choice && temp != nullptr; ++i)
        temp = temp->next;

    return temp;
}

void bookSeat(ShowNode* show) {
    string name;
    int row, col;

    cout << "\nEnter your name: ";
    cin >> name;

    displaySeats(show);
    cout << "Enter row (1-" << ROWS << "): ";
    cin >> row;
    cout << "Enter column (1-" << COLS << "): ";
    cin >> col;

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        cout << "Invalid seat selection.\n";
        return;
    }

    Seat& s = show->seats[row - 1][col - 1];

    if (s.isBooked) {
        cout << "Seat already booked. Adding to waitlist...\n";
        show->waitlist.push(name);
    } else {
        s.isBooked = true;
        s.name = name;
        s.category = (row == 1) ? "VIP" : "Regular";
        cout << "Seat booked successfully as " << s.category << " seat!\n";
    }
}

void cancelSeat(ShowNode* show) {
    int row, col;
    displaySeats(show);
    cout << "Enter row to cancel (1-" << ROWS << "): ";
    cin >> row;
    cout << "Enter column to cancel (1-" << COLS << "): ";
    cin >> col;

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        cout << "Invalid seat selection.\n";
        return;
    }

    Seat& s = show->seats[row - 1][col - 1];
    if (!s.isBooked) {
        cout << "Seat is not booked.\n";
        return;
    }

    cout << "Cancelled booking for: " << s.name << " (" << s.category << ")\n";
    s.isBooked = false;
    s.name = "";
    s.category = "Regular";

    if (!show->waitlist.empty()) {
        string nextPerson = show->waitlist.front();
        show->waitlist.pop();
        s.isBooked = true;
        s.name = nextPerson;
        s.category = (row == 1) ? "VIP" : "Regular";
        cout << "Seat reassigned to waitlisted user: " << nextPerson << "\n";
    }
}

void showReport(ShowNode* head) {
    ShowNode* temp = head;
    cout << "\n========== Booking Report ==========" << endl;
    while (temp != nullptr) {
        int vip = 0, regular = 0;
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                if (temp->seats[i][j].isBooked)
                    (temp->seats[i][j].category == "VIP") ? vip++ : regular++;

        cout << "\nShow: " << temp->showName << endl;
        cout << "  VIP Seats Booked: " << vip << endl;
        cout << "  Regular Seats Booked: " << regular << endl;
        cout << "  Waitlist Size: " << temp->waitlist.size() << endl;
        temp = temp->next;
    }
}

int main() {
    ShowNode* showGraph = createGraph();
    int choice;
    while (true) {
        cout << "\n===============================\n";
        cout << "?? Movie Ticket Booking System ??\n";
        cout << "===============================\n";
        cout << "1. Display Seats\n";
        cout << "2. Book Seat\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Show Report\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        ShowNode* selectedShow = nullptr;

        switch (choice) {
            case 1:
                selectedShow = selectShow(showGraph);
                if (selectedShow) displaySeats(selectedShow);
                break;
            case 2:
                selectedShow = selectShow(showGraph);
                if (selectedShow) bookSeat(selectedShow);
                break;
            case 3:
                selectedShow = selectShow(showGraph);
                if (selectedShow) cancelSeat(selectedShow);
                break;
            case 4:
                showReport(showGraph);
                break;
            case 5:
                cout << "Thank you for using the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

