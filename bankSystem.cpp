#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;

class about {
public:
    about() {
        cout << endl;
        cout << "=============WELCOME SAEEN================\n";
        cout << "           WELCOME TO OUR BANK        \n";
        cout << "           WASEEM ABBAS KANHIO         \n";
        cout << "=====================================\n";
        cout << "-------------------------------------\n";
        cout << "=====================================\n";
        cout << "25SW031 FROM SECTION-1\n";
        cout << "PROJECT : BANK MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

    }
};

class Bank {
private:
    string name, cnic, income, address;
    int pin;
    double balance;

public:
    void createAccount() {
    	sleep(2);
        system("cls");
        cout << "-------------------------------------\n";
        cout << "      ACCOUNT REGISTRATION PORTAL    \n";
        cout << "-------------------------------------\n";

        cin.ignore();
        cout << "Enter Full Name: ";
        getline(cin, name);
        cout << "Enter CNIC: ";
        getline(cin, cnic);
        cout << "Enter Source of Income: ";
        getline(cin, income);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Create 4-digit PIN: ";
        cin >> pin;
        cout << "Deposit minimum 500 PKR: ";
        cin >> balance;

        if (balance < 500) {
            cout << "SORRY! Minimum deposit is 500 PKR.\n";
            return;
        }

        ofstream fout("Accounts.txt", ios::app);
        fout << name << "," << cnic << "," << income << "," << address << "," << pin << "," << balance << endl;
        fout.close();

        cout << "\nAccount successfully created!\n";
        sleep(2);
        system("cls");
    }
};

class Transaction {
private:
    string name, cnic, income, address;
    int pin;
    double balance;

    bool loadAccount(int enteredPin) {
        ifstream fin("Accounts.txt");
        string line;
        bool found = false;
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, cnic, ',');
            getline(ss, income, ',');
            getline(ss, address, ',');
            ss >> pin;
            ss.ignore();
            ss >> balance;
            if (enteredPin == pin) {
                found = true;
                break;
            }
        }
        fin.close();
        return found;
    }

    void saveAccount() {
        // rewrite file with updated balance
        ifstream fin("Accounts.txt");
        ofstream temp("Temp.txt");
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string n, c, i, a;
            int p;
            double b;
            getline(ss, n, ',');
            getline(ss, c, ',');
            getline(ss, i, ',');
            getline(ss, a, ',');
            ss >> p;
            ss.ignore();
            ss >> b;
            if (p == pin)
                temp << name << "," << cnic << "," << income << "," << address << "," << pin << "," << balance << endl;
            else
                temp << n << "," << c << "," << i << "," << a << "," << p << "," << b << endl;
        }
        fin.close();
        temp.close();
        remove("Accounts.txt");
        rename("Temp.txt", "Accounts.txt");
    }

public:
    void login() {
        int enteredPin;
        cout << "Enter your PIN to login: ";
        cin >> enteredPin;
        if (!loadAccount(enteredPin)) {
            cout << "Invalid PIN or account not found!\n";
            return;
        }
        system("cls");
        sleep(2);

        cout << "\nWelcome, " << name << "!\n";
        menu();
    }

    void menu() {
        int choice;
        do {
            cout << "\n=====================================\n";
            cout << "           ACCOUNT MENU              \n";
            cout << "=====================================\n";

            cout << "1. Check Balance\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Transfer Money\n";
            cout << "5. Account Info\n";
            cout << "6. Exit\n";
            cout << "==============================\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Your current balance is: " << balance << " PKR\n";
                    break;
                case 2: {
                    double amt;
                    cout << "Enter amount to deposit: ";
                    cin >> amt;
                    if (amt > 0) {
                        balance += amt;
                        saveAccount();
                        cout << amt << " PKR deposited successfully!\n";
                    }
                    break;
                }
                case 3: {
                    double amt;
                    cout << "Enter amount to withdraw: ";
                    cin >> amt;
                    if (amt <= balance - 100) {
                        balance -= amt;
                        saveAccount();
                        cout << "Withdrawal successful. Remaining balance: " << balance << endl;
                    } else {
                        cout << "Insufficient funds (must keep at least 100 PKR).\n";
                    }
                    break;
                }
                case 4: {
                    int targetPin;
                    double amt;
                    string namme;
                    cout << "Enter recipient PIN: ";
                    cin >> targetPin;
                    cout << "Enter amount to transfer: ";
                    cin >> amt;
                    if (amt <= balance - 100) {
                        ifstream fin("Accounts.txt");
                        ofstream temp("Temp.txt");
                        string line;
                        bool found = false;
                        while (getline(fin, line)) {
                            stringstream ss(line);
                            string n, c, i, a;
                            int p;
                            double b;
                            getline(ss, n, ',');
                            getline(ss, c, ',');
                            getline(ss, i, ',');
                            getline(ss, a, ',');
                            ss >> p;
                            ss.ignore();
                            ss >> b;
                            if (p == pin) {
                                balance -= amt;
                                temp << name << "," << cnic << "," << income << "," << address << "," << pin << "," << balance << endl;
                            } else if (p == targetPin) {
                                b += amt;
                                found = true;
                                temp << n << "," << c << "," << i << "," << a << "," << p << "," << b << endl;
                                 namme = n;
                            } else {
                                temp << n << "," << c << "," << i << "," << a << "," << p << "," << b << endl;
                               
                            }
                        }
                        fin.close();
                        temp.close();
                        remove("Accounts.txt");
                        rename("Temp.txt", "Accounts.txt");
                        if (found)
                            
                            cout <<__DATE__ << "\n" << __TIME__  <<  "\nTransferred " << amt << " PKR successfully sent to " << namme << "!\n";
                        else
                            cout << "Recipient account not found. Transfer failed.\n";
                    } else
                        cout << "Insufficient balance for transfer.\n";
                    break;
                }
                case 5:
                    cout << "\n========== ACCOUNT DETAILS ==========\n";
                    cout << "Name     : " << name << "\n";
                    cout << "CNIC     : " << cnic << "\n";
                    cout << "Income   : " << income << "\n";
                    cout << "Address  : " << address << "\n";
                    cout << "Balance  : " << balance << "\n";
                    cout << "=====================================\n";


                    break;
                case 6:
                    cout << "Thank you for using our service.\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
            sleep(2);
        } while (choice != 6);
    }
};

int main() {
    about intro;
    int choice;
    do {
        cout << "\n==============================\n";
        cout << "1. Create New Account\n";
        cout << "2. Login Existing Account\n";
        cout << "3. Exit\n";
        cout << "==============================\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            Bank b;
            b.createAccount();
        } else if (choice == 2) {
            Transaction t;
            t.login();
        } else if (choice == 3) {
            cout << "Allah Hafiz, Mola Salamath Rakhe!\n";
            sleep(2);
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);
    return 0;
}
