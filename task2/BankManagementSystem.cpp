
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

class Account {
private:
    int accNo;
    char name[50];
    double balance;

public:
    Account() {
        accNo = 0;
        strcpy(name, "");
        balance = 0;
    }

    void createAccount(int newAccNo) {
        accNo = newAccNo;

        cin.ignore();
        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        if(balance < 0) balance = 0;
    }

    void showAccount() const {
        cout << "\nAccount Number : " << accNo;
        cout << "\nName           : " << name;
        cout << "\nBalance        : " << balance << endl;
    }

    int getAccNo() const { return accNo; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if(amount > balance) return false;
        balance -= amount;
        return true;
    }
};

int generateAccountNumber() {
    Account a;
    ifstream file("accounts.dat", ios::binary);

    int last = 1000;

    while(file.read((char*)&a, sizeof(a)))
        last = a.getAccNo();

    file.close();
    return last + 1;
}

bool accountExists(int accNo) {
    Account a;
    ifstream file("accounts.dat", ios::binary);

    while(file.read((char*)&a, sizeof(a))) {
        if(a.getAccNo() == accNo) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void logTransaction(int accNo, const char* type, double amount) {
    ofstream log("transactions.txt", ios::app);
    log << "Account: " << accNo
        << " | " << type
        << " | Amount: " << amount << endl;
    log.close();
}

void createAccount() {
    Account a;

    int accNo = generateAccountNumber();

    cout << "\nGenerated Account Number: " << accNo << endl;

    a.createAccount(accNo);

    ofstream file("accounts.dat", ios::binary | ios::app);
    file.write((char*)&a, sizeof(a));
    file.close();

    cout << "\nAccount Created Successfully.\n";
}

void displayAllAccounts() {
    Account a;
    ifstream file("accounts.dat", ios::binary);

    cout << "\n===== ALL ACCOUNTS =====\n";

    while(file.read((char*)&a, sizeof(a))) {
        a.showAccount();
        cout << "------------------------\n";
    }

    file.close();
}

void searchAccount() {
    int accNo;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account a;
    ifstream file("accounts.dat", ios::binary);

    while(file.read((char*)&a, sizeof(a))) {
        if(a.getAccNo() == accNo) {
            cout << "\nAccount Found\n";
            a.showAccount();
            file.close();
            return;
        }
    }

    cout << "\nAccount Not Found\n";
    file.close();
}

void depositMoney() {
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    Account a;

    ifstream file("accounts.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    bool found = false;

    while(file.read((char*)&a, sizeof(a))) {
        if(a.getAccNo() == accNo) {
            a.deposit(amount);
            found = true;
        }
        temp.write((char*)&a, sizeof(a));
    }

    file.close();
    temp.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if(found) {
        logTransaction(accNo, "DEPOSIT", amount);
        cout << "\nDeposit Successful\n";
    } else {
        cout << "\nAccount Not Found\n";
    }
}

void withdrawMoney() {
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Withdraw Amount: ";
    cin >> amount;

    Account a;

    ifstream file("accounts.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    bool found = false;
    bool success = false;

    while(file.read((char*)&a, sizeof(a))) {
        if(a.getAccNo() == accNo) {
            found = true;
            success = a.withdraw(amount);
        }

        temp.write((char*)&a, sizeof(a));
    }

    file.close();
    temp.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if(!found)
        cout << "\nAccount Not Found\n";
    else if(!success)
        cout << "\nInsufficient Balance\n";
    else {
        logTransaction(accNo, "WITHDRAW", amount);
        cout << "\nWithdrawal Successful\n";
    }
}

void checkBalance() {
    int accNo;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account a;
    ifstream file("accounts.dat", ios::binary);

    while(file.read((char*)&a, sizeof(a))) {
        if(a.getAccNo() == accNo) {
            cout << "\nCurrent Balance: " << a.getBalance() << endl;
            file.close();
            return;
        }
    }

    cout << "\nAccount Not Found\n";
    file.close();
}

void deleteAccount() {
    int accNo;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account a;

    ifstream file("accounts.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    bool found = false;

    while(file.read((char*)&a, sizeof(a))) {
        if(a.getAccNo() == accNo) {
            found = true;
            continue;
        }

        temp.write((char*)&a, sizeof(a));
    }

    file.close();
    temp.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if(found)
        cout << "\nAccount Deleted Successfully\n";
    else
        cout << "\nAccount Not Found\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Check Balance\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: createAccount(); break;
            case 2: displayAllAccounts(); break;
            case 3: searchAccount(); break;
            case 4: depositMoney(); break;
            case 5: withdrawMoney(); break;
            case 6: checkBalance(); break;
            case 7: deleteAccount(); break;
            case 8: cout << "\nThank You!\n"; break;
            default: cout << "\nInvalid Choice\n";
        }

    } while(choice != 8);

    return 0;
}
