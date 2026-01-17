
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Transaction {
    string type;   // Income or Expense
    string name;
    double amount;
};

vector<Transaction> transactions;

// Save transactions to file
void saveToFile() {
    ofstream file("finance_data.txt");
    for (int i = 0; i < transactions.size(); i++) {
        file << transactions[i].type << " "
             << transactions[i].name << " "
             << transactions[i].amount << endl;
    }
    file.close();
}

// Load transactions from file
void loadFromFile() {
    ifstream file("finance_data.txt");
    Transaction t;
    transactions.clear();

    while (file >> t.type >> t.name >> t.amount) {
        transactions.push_back(t);
    }
    file.close();
}

// Add income or expense
void addTransaction(string type) {
    Transaction t;
    t.type = type;

    cout << "Enter name: ";
    cin >> t.name;

    cout << "Enter amount: ";
    while (!(cin >> t.amount) || t.amount <= 0) {
        cout << "Invalid amount. Try again: ";
        cin.clear();
        cin.ignore(1000, '\\n');
    }

    transactions.push_back(t);
    saveToFile();

    cout << type << " added successfully.\\n";
}

// Display summary
void viewSummary() {
    double income = 0, expenses = 0;

    for (int i = 0; i < transactions.size(); i++) {
        if (transactions[i].type == "Income")
            income += transactions[i].amount;
        else
            expenses += transactions[i].amount;
    }

    cout << "\\n--- Monthly Summary ---\\n";
    cout << "Total Income: $" << income << endl;
    cout << "Total Expenses: $" << expenses << endl;
    cout << "Savings: $" << (income - expenses) << endl;
}

int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\\n==== Personal Finance Analyzer ====\\n";
        cout << "1. Add Income\\n";
        cout << "2. Add Expense\\n";
        cout << "3. View Summary\\n";
        cout << "4. Exit\\n";
        cout << "Choose an option: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addTransaction("Income");
                break;
            case 2:
                addTransaction("Expense");
                break;
            case 3:
                viewSummary();
                break;
            case 4:
                cout << "Goodbye!\\n";
                break;
            default:
                cout << "Invalid option. Try again.\\n";
        }
    } while (choice != 4);

    return 0;
}
