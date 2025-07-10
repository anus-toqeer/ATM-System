#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

double totalcash = 500000;
double balance = 50000;
double totalcashwithdraw = 0;
double maxdeposit = 0;
int currentpin = 1234;

void loadPin() {
    ifstream pinFile("pin.txt");
    if (pinFile.is_open()) {
        pinFile >> currentpin;
        pinFile.close();
    } else {
        currentpin = 1234;
    }
}

void savepin() {
    ofstream pinFile("pin.txt");
    if (pinFile.is_open()) {
        pinFile << currentpin;
        pinFile.close();
    } else {
        cout << "Error saving PIN!" << endl;
    }
}

void loadBalance() {
    ifstream balanceFile("balance.txt");
    if (balanceFile.is_open()) {
        balanceFile >> balance;
        balanceFile.close();
    } else {
        balance = 80000;
    }
}

void saveBalance() {
    ofstream balanceFile("balance.txt");
    if (balanceFile.is_open()) {
        balanceFile << balance;
        balanceFile.close();
    } else {
        cout << "Error saving balance!" << endl;
    }
}

int validatepin() {
    int inputpin;
    for (int attempt = 1; attempt <= 3; attempt++) {
        cout << "\n\n Please Enter your pin: ";
        cin >> inputpin;
        if (currentpin == inputpin) {
            cout << "\nPin Validated successfully";
            return 1;
        } else {
            cout << "Incorrect Pin!";
        }
        if (attempt == 3) {
            cout << "You have entered wrong pin multiple times";
            cout << "\nTry again later";
            exit(0);
        }
    }
    return 0;
}

int cardselection() {
    int cardtype;
    cout << "\n\nSelect your card type";
    cout << "\n1.Silver";
    cout << "\n2.Gold";
    cout << "\n3.Platinum";
    do {
        cout << "\nEnter the type: ";
        cin >> cardtype;
        switch (cardtype) {
        case 1:
            totalcashwithdraw = 50000;
            maxdeposit = 50000;
            break;
        case 2:
            totalcashwithdraw = 100000;
            maxdeposit = 100000;
            break;
        case 3:
            totalcashwithdraw = 200000;
            maxdeposit = 200000;
            break;
        default:
            cout << "Invalid!";
        }
    } while (cardtype != 1 && cardtype != 2 && cardtype != 3);
    return totalcashwithdraw;
}

void displaymenu() {
    cout<<char(218);
    for(int i=0;i<38;i++) cout<<(char)196;
    cout<<char(191);
    cout<<endl;
    cout<<char(179);
    cout<<"     ==== Welcome To ATM Menu ====    ";
    cout<<char(179);
    cout<<endl;
    cout<<char(192);
    
    for(int i=0;i<38;i++) cout<<(char)196;
    cout<<char(217);
    cout<<endl;

    cout << "\n\n1. Balance Inquiry |" << "\t" << "2. Cash           |";
    cout << "\n\n3. Deposit Money   |" << "\t" << "4. Transfer Money |";
    cout << "\n\n5. Change Pin      |" << "\t" << "6. Exit           |";
}

void balanceinquiry() {
    cout << "\nYour Current Balance is: " << balance;
}

void cashwithdraw() {
    double amountwithdraw;
    cout << "\nEnter amount for withdrawl (Max:" << totalcashwithdraw << "): ";
    cin >> amountwithdraw;
    string choice;

    if (totalcash == 0) {
        cout << "ATM is out of cash!";
        exit(0);
    }

    while (amountwithdraw > totalcashwithdraw || amountwithdraw > balance || amountwithdraw < 0) {
        if (amountwithdraw > balance) {
            cout << "Insufficient Balance" << endl;
        }
        if (amountwithdraw > totalcashwithdraw) {
            cout << "Amount should be below " << totalcashwithdraw;
        }
        if (amountwithdraw < 0) {
            cout << "Cannot be negative";
        }
        cout << "\nDo you want to enter again (yes/no): ";
        cin >> choice;
        if (choice == "yes" || choice == "Yes") {
            cout << "Enter amount again(Max:" << totalcashwithdraw << "): ";
            cin >> amountwithdraw;
        } else {
            cout << "Thank you for choosing this ATM";
            exit(0);
        }
    }
    if (amountwithdraw <= balance && amountwithdraw <= totalcashwithdraw) {
        balance = balance - amountwithdraw;
        totalcash = totalcash - amountwithdraw;
        cout << amountwithdraw << " is being withdrawn";
        cout << "\nYour new balance is: " << balance;
        saveBalance();
    }
}

void cashdeposit() {
    string depositchoice;
    double cashdeposit;
    cout << "Enter amount you want to deposit(Max:" << maxdeposit << "):";
    cin >> cashdeposit;

    while (cashdeposit > maxdeposit || cashdeposit < 0) {
        if (cashdeposit > maxdeposit) {
            cout << "Amount should be below " << maxdeposit;
        }
        if (cashdeposit < 0) {
            cout << "Cannot be negative";
        }
        cout << "\nDo you want to enter again (yes/no): ";
        cin >> depositchoice;
        if (depositchoice == "yes" || depositchoice == "Yes") {
            cout << "Enter amount again(Max:" << maxdeposit << "): ";
            cin >> cashdeposit;
        } else {
            cout << "Thank you for choosing this ATM";
            exit(0);
        }
    }
    if (cashdeposit <= maxdeposit) {
        balance = balance + cashdeposit;
        totalcash = totalcash + cashdeposit;
        cout << cashdeposit << " is being deposited";
        cout << "\nYour new balance is: " << balance;
        saveBalance();
    }
}

void fundstransfer() {
    int accnum, transferamount;
    cout << "\nEnter the Account number for transfer: ";
    cin >> accnum;
    while (accnum < 0) {
        cout << "Can not be negative!";
        cout << "\nEnter the Account number again for transfer: ";
        cin >> accnum;
    }
    cout << "\nEnter the Amount for transfer: ";
    cin >> transferamount;
    while (transferamount < 0 || transferamount > balance) {
        cout << "Invalid Amount!";
        cout << "\nEnter the Amount again for transfer: ";
        cin >> transferamount;
    }
    if (transferamount <= balance) {
        balance = balance - transferamount;
        totalcash = totalcash - transferamount;
        cout << "Transferring Rs= " << transferamount << " \nto Account Number: " << accnum;
        cout << "\nTransferred...";
        cout << "\nYour new balance is: " << balance;
        saveBalance();
    } else {
        cout << "Invalid data";
    }
}

void changepin() {
    int oldpin, newpin, confirmpin;

    cout << "\nEnter your old PIN: ";
    cin >> oldpin;

    while (oldpin != currentpin) {
        cout << "Incorrect old PIN. Please try again.\n";
        cout << "\nEnter your old PIN again: ";
        cin >> oldpin;
    }
    cout << "Enter your new PIN: ";
    cin >> newpin;

    cout << "Confirm your new PIN: ";
    cin >> confirmpin;
    while (newpin != confirmpin) {
        cout << "\nDoes not match";
        cout << "\nConfirm your new PIN again: ";
        cin >> confirmpin;
    }
    currentpin = newpin;
    savepin();
    cout << "Your PIN has been successfully changed.\n";
}

int main() {
    int choice;
    string selection;
    cout<<char(218);
    for(int i=0;i<38;i++) cout<<(char)196;
    cout<<char(191);
    cout<<endl;
    cout<<char(179);
    cout<<"      ~~~~ Welcome To The ATM ~~~~    ";
    cout<<char(179);
    cout<<endl;
    cout<<char(192);
    
    for(int i=0;i<38;i++) cout<<(char)196;
    cout<<char(217);
    cout<<endl;

    loadPin();
    validatepin();
    loadBalance();
    cardselection();
    do {
        displaymenu();
        cout << "\n\n Enter Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            balanceinquiry();
            break;
        case 2:
            cashwithdraw();
            break;
        case 3:
            cashdeposit();
            break;
        case 4:
            fundstransfer();
            break;
        case 5:
            changepin();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid data";
            break;
        }
        cout << "\nDo You want to make another transaction(Yes/No): ";
        cin >> selection;
    } while (selection != "No" && selection != "no");
    return 0;
}
