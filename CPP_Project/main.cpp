#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Transaction {
    int id;
    string date;
    string type;
    string category;
    float amount;
};

vector<Transaction> transactions;
int nextId = 1;

void loadData() {
    ifstream file("transactions.txt");
    if (!file) return;

    Transaction t;
    while (file >> t.id >> t.date >> t.type >> t.category >> t.amount) {
        transactions.push_back(t);
        nextId = t.id + 1;
    }
    file.close();
}

void saveData() {
    ofstream file("transactions.txt");
    for (auto &t : transactions) {
        file << t.id << " " << t.date << " " << t.type << " "
             << t.category << " " << t.amount << endl;
    }
    file.close();
}

void addTransaction() {
    Transaction t;
    t.id = nextId++;

    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> t.date;

    cout << "Type (Income/Expense): ";
    cin >> t.type;

    cout << "Category (Food/Transport/Rent/Shopping/Bills/Others): ";
    cin >> t.category;

    cout << "Amount: ";
    cin >> t.amount;

    transactions.push_back(t);
    saveData();
    cout << "Transaction added successfully!\n";
}

void viewTransactions() {
    cout << "\nID  Date        Type     Category     Amount\n";
    cout << "---------------------------------------------\n";
    for (auto &t : transactions) {
        cout << setw(3) << t.id << " "
             << setw(10) << t.date << " "
             << setw(8) << t.type << " "
             << setw(10) << t.category << " "
             << t.amount << endl;
    }
}

void filterByCategory() {
    string cat;
    cout << "Enter category: ";
    cin >> cat;

    for (auto &t : transactions) {
        if (t.category == cat) {
            cout << t.id << " " << t.date << " " << t.type
                 << " " << t.amount << endl;
        }
    }
}

void filterByDate() {
    string date;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    for (auto &t : transactions) {
        if (t.date == date) {
            cout << t.id << " " << t.category << " "
                 << t.type << " " << t.amount << endl;
        }
    }
}

void editTransaction() {
    int id;
    cout << "Enter Transaction ID to edit: ";
    cin >> id;

    for (auto &t : transactions) {
        if (t.id == id) {
            cout << "New Date: ";
            cin >> t.date;
            cout << "New Type: ";
            cin >> t.type;
            cout << "New Category: ";
            cin >> t.category;
            cout << "New Amount: ";
            cin >> t.amount;

            saveData();
            cout << "Transaction updated.\n";
            return;
        }
    }
    cout << "Transaction not found.\n";
}

void deleteTransaction() {
    int id;
    cout << "Enter Transaction ID to delete: ";
    cin >> id;

    for (int i = 0; i < transactions.size(); i++) {
        if (transactions[i].id == id) {
            transactions.erase(transactions.begin() + i);
            saveData();
            cout << "Transaction deleted.\n";
            return;
        }
    }
    cout << "Transaction not found.\n";
}

void showSummary() {
    float income = 0, expense = 0;

    for (auto &t : transactions) {
        if (t.type == "Income")
            income += t.amount;
        else
            expense += t.amount;
    }

    cout << "\nTotal Income: " << income;
    cout << "\nTotal Expenses: " << expense;
    cout << "\nSavings: " << income - expense << endl;
}

void exportSummary() {
    ofstream file("summary.txt");

    float income = 0, expense = 0;
    for (auto &t : transactions) {
        if (t.type == "Income")
            income += t.amount;
        else
            expense += t.amount;
    }

    file << "Monthly Finance Summary\n";
    file << "------------------------\n";
    file << "Total Income: " << income << endl;
    file << "Total Expenses: " << expense << endl;
    file << "Savings: " << income - expense << endl;

    file.close();
    cout << "Summary exported to summary.txt\n";
}

int main() {
    loadData();
    int choice;

    do {
        cout << "\n--- Personal Finance Manager ---\n";
        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. Filter by Category\n";
        cout << "4. Filter by Date\n";
        cout << "5. Edit Transaction\n";
        cout << "6. Delete Transaction\n";
        cout << "7. Show Summary\n";
        cout << "8. Export Summary\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: viewTransactions(); break;
            case 3: filterByCategory(); break;
            case 4: filterByDate(); break;
            case 5: editTransaction(); break;
            case 6: deleteTransaction(); break;
            case 7: showSummary(); break;
            case 8: exportSummary(); break;
        }
    } while (choice != 0);

    return 0;
}
