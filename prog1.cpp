#include<iostream>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string number, string name, double bal) 
    {
        accountNumber = number;
        accountHolderName = name;
        balance = bal;
    }

    virtual ~BankAccount() {}

    virtual void deposit(double amount) 
    {
        balance += amount;
        cout<<"Deposited: "<<amount<<endl;
    }

    virtual void withdraw(double amount) 
    {
        if (amount <= balance) {
            balance -= amount;
            cout<<"Withdrawn: "<<amount<<endl;
        } else {
            cout<<"Insufficient balance!"<<endl;
        }
    }

    double getBalance()  
    {
        return balance;
    }

    void displayAccountInfo()  
    {
        cout<<endl<<"--- Account Info ---"<<endl;
        cout<<"Account Number: "<<accountNumber<< endl;
        cout<<"Holder Name: " <<accountHolderName<< endl;
        cout<<"Balance: "<<balance<<endl;
    }

    virtual void calculateInterest() {}
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string number, string name, double bal, double rate)
        : BankAccount(number, name, bal), interestRate(rate) {}

    void calculateInterest() override 
    {
        double interest = getBalance() * interestRate / 100;
        cout << "Savings Interest: " << interest << endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string number, string name, double bal, double limit)
        : BankAccount(number, name, bal), overdraftLimit(limit) {}

    void withdraw(double amount) 
    {
        if (amount <= getBalance() + overdraftLimit) {
            BankAccount::withdraw(amount);
        } 
        else 
        {
            cout<<"Overdraft limit exceeded!"<<endl;
        }
    }

    void checkOverdraft(double amount) 
    {
        if (amount > getBalance() + overdraftLimit) {
            cout<<"Withdrawal exceeds overdraft limit!"<<endl;
        } 
        else 
        {
            cout<<"Withdrawal within overdraft limit."<<endl;
        }
    }
};

class FixedDepositAccount : public BankAccount {
private:
    int term; 

public:
    FixedDepositAccount(string number, string name, double bal, int t)
        : BankAccount(number, name, bal), term(t) {}

    void calculateInterest()
    {
        double rate = 8.0; 
        double interest = getBalance() * rate * term / (12 * 100);
        cout<<"Fixed Deposit Interest: "<<interest<<endl;
    }
};

void accountMenu(BankAccount* account)
{
    int choice;
    double amount;

    do {
        cout<<"--- Menu ---"<<endl;
        cout<<"1. Deposit"<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. Show Info"<<endl;
        cout<<"4. Calculate Interest"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Choose: "<<endl;
        cin >> choice;

        switch (choice) {
            case 1:
                cout<<"Enter amount to deposit: ";
                cin>>amount;
                account->deposit(amount);
                break;
            case 2:
                cout<<"Enter amount to withdraw: ";
                cin>>amount;
                account->withdraw(amount);
                break;
            case 3:
                account->displayAccountInfo();
                break;
            case 4:
                account->calculateInterest();
                break;
            case 5:
                cout<<"Exiting account..."<<endl;
                break;
            default:
                cout<<"Invalid option!"<<endl;
        }
    } while (choice != 5);
}

int main() {
    int type;
    string accNo, accName;
    double balance;

    cout<<"Select Account Type: "<<endl;
    cout<<"1. Savings Account"<<endl;
    cout<<"2. Checking Account"<<endl;
    cout<<"3. Fixed Deposit Account"<<endl;
    cout<<"Enter choice: "<<endl;
    cin >> type;

    cout<<"Enter Account Number: ";
    cin>>accNo;
    cout<<"Enter Account Holder Name: ";
    cin>>accName;
    cout<<"Enter Initial Balance: ";
    cin>>balance;

    BankAccount* account = nullptr;

    if(type == 1)
    {
        double rate;
        cout << "Enter Interest Rate (%): ";
        cin >> rate;
        account = new SavingsAccount(accNo, accName, balance, rate);
    } 
    else if(type == 2) 
    {
        double limit;
        cout<<"Enter Overdraft Limit: ";
        cin>>limit;
        account = new CheckingAccount(accNo, accName, balance, limit);
    } 
    else if(type == 3) 
    {
        int term;
        cout<<"Enter Term (in months): ";
        cin>>term;
        account = new FixedDepositAccount(accNo, accName, balance, term);
    } 
    else 
    {
        cout<<"Invalid account type selected!"<<endl;
        return 1;
    }

    accountMenu(account);

    delete account;
    return 0;
}