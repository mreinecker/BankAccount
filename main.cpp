// Exercise 2 for Written Assignment 4
// --------------------------------------
// Create an inheritance hierarchy that a bank might use to represent customers’ bank accounts. All customers at this bank can deposit (i.e., credit)
// money into their accounts and withdraw (i.e., debit) money from their accounts. More specific types of accounts also exist. Savings accounts,
// for instance, earn interest on the money they hold. Checking accounts, on the other hand, charge a fee per transaction (i.e., credit or debit).
//
// Create an inheritance hierarchy containing base-class Bank-Account and derived classes Savings and Checking that inherit from class Bank-Account.
// Base-class Bank-Account should include one data member of type double to represent the bank account’s balance. The class should provide a
// constructor that receives an initial balance and uses it to initialize the data member. The constructor should validate the initial balance
// to ensure that it’s greater than or equal to 0.0. If not, the balance should be set to 0.0 and the constructor should display an error message,
// indicating that the initial balance was invalid. The class should provide three member functions. Member function credit should add an amount
// to the current balance. Member function debit should withdraw money from the Bank-Account and ensure that the debit amount does not exceed
// the Bank-Account’s balance. If it does, the balance should be left unchanged and the function should print the message “The balance is less
// than the debit amount.” Member function getBalance should return the current balance.
//
// Derived class Savings should inherit the functionality of a Bank-Account, but also include a data member of type double indicating the interest
// rate (percentage) assigned to the Bank-Account. Savings’ constructor should receive the initial balance, as well as an initial value for the
// Savings’ interest rate. Savings should provide a public member function calculateInterest that returns a double indicating the amount of interest
// earned by an account. Member function calculateInterest should determine this amount by multiplying the interest rate by the bank account balance.
// [Note: Savings should inherit member functions credit and debit as is without redefining them.]
//
// Derived-class Checking should inherit from base-class Bank-Account and include an additional data member of type double that represents the fee
// charged per transaction. Checking’s constructor should receive the initial balance, as well as a parameter indicating a fee amount. Class Checking
// should redefine member functions credit and debit so that they subtract the fee from the account balance whenever either transaction is performed
// successfully. Checking’s version of these functions should invoke the base-class Bank-Account to perform the updates to an account balance.
// Checking’s debit function should charge a fee only if money is actually withdrawn (i.e., the debit amount does not exceed the account balance).
// [Hint: Define Bank-Account’s debit function so that it returns a bool indicating whether money was withdrawn. Then use the return value to determine
// whether a fee should be charged.]
//
// After defining the classes in this hierarchy, write a program that:
//
// Creates an object of Bank-Account, Savings, and Checking class. Each of the three objects should have an initial balance.
// The Savings object should also have an interest rate and the Checking object should also have a transaction fee.
// Prints out the balance of all the three objects.
// Debits a certain amount from all the three objects.
// Prints out the balance of all the three objects (after the debits) in the previous step.
// Credits a certain amount to all the three objects. Prints out the balance of all the three objects (after the credits) in the previous step.
// Computes the interest for the Savings object and adds it to its balance, then prints out the new balance.
	#include <iostream>
	#include <vector>

	// class for bank account
	class BankAccount {          //balance as double protected member so child classes can access
	protected:
		double balance = 0;
		std::string account_name = "???";
	public:
		BankAccount() {};

		~BankAccount() {};

		BankAccount(double userBalance, std::string name) {
			if (userBalance >= 0) {                         // constructor to receive initial balance and use it to initialize the balance
				balance = userBalance;
			} else {
				balance = 0;                                //verify balance is greater than or equal to 0, else display error and set balance to 0
				std::cout << "\nError, balance set to 0\n";
			}
			account_name=name;
		}

		const std::string &getAccount_name() const {
			return account_name;
		}

		void setAccount_name(const std::string &account_name) {
			BankAccount::account_name = account_name;
		};

		virtual void
		credit(double amount) {                            //	Member function credit should add an amount to the current balance.
			balance += amount;
		}

		virtual void
		debit(double amount) {                             //  Member function debit should withdraw money from the Bank-Account and ensure that the debit amount does not exceed
			if (amount >
			    balance) {                               //  the Bank-Account’s balance. If it does, the balance should be left unchanged and the function should print the message
				std::cout << "The balance is less than the debit amount.\n";     //  “The balance is less than the debit amount.”
			} else {
				balance -= amount;
			}
		}

		virtual double getBalance() {                      // Member function getBalance should return the current balance.
			return balance;
		};
//		std::string getName()const {
//			return this->account_name;
//		}

		bool operator ==(const BankAccount& compare) const{
			return this->account_name == compare.account_name;
		}
	};


	class SavingsAccount : public BankAccount {               // inherit bank account class to create savings account
		double interestRate = 0;

	public:                                                   // constructor to get initial balance and interest rate
		SavingsAccount(double userBalance, const std::string &name, double user_rate) : BankAccount(userBalance, name),
		                                                                              interestRate(user_rate) {
//			interestRate = user_rate;
		}

		double
		calculateInterest() {               // calculateInterest that returns a double indicating the amount of interest earned by an account
								            // this amount is calc by multiplying the interest rate by the bank account balance
			return balance * interestRate;
		}
		void credit(double amount) {
			balance += amount +
			         calculateInterest();                            //	Member function credit should add an amount to the current balance.
		}
	};

	class CheckingAccount : public BankAccount {
		double transactionFee;
	public:
		CheckingAccount(double userBalance, const std::string &name, double transfee_input) : BankAccount(userBalance, name),
		                                                                                 transactionFee(
				                                                                                 transfee_input) {
//			transactionFee=transfee_input;
		}

		void credit(double amount) {
			balance += amount + transactionFee;    //	Member function credit should add an amount to the current balance.
		}

		void debit(double amount) {                                         //  Member function debit should withdraw money from the Bank-Account and ensure that the debit amount does not exceed
			if (amount >
			    getBalance()) {                                    //  the Bank-Account’s balance. If it does, the balance should be left unchanged and the function should print the message
				std::cout << "The balance is less than the debit amount.\n";     //  “The balance is less than the debit amount.”
			} else {
				balance -= amount + transactionFee;
			}
		}
	};



class HasIdentifier  // to identify account name in each account when searching vector for iterator
{
public:
	HasIdentifier(std::string id) :
			m_id(std::move(id)) 	{}

	bool operator()(std::shared_ptr<BankAccount> const& c)const
	{
		return (c->getAccount_name() == m_id);
	}
private:
	std::string m_id;
};

bool yesNo(char g){  //function to handle a yes/no question and return a bool
	bool accessAccounts;

	if (g == 'y' || g == 'Y') {
		accessAccounts = true;
	}
	else if (g == 'n' || g == 'N') {
		accessAccounts = false;
	}
	else {
		accessAccounts = false;
		std::cout << "Invalid response." << std::endl;
	}
	return accessAccounts;
}


	int main() {
		double balanceInput{0};                        //variables for getting balance/interest inputs/outputs
		double interestRate_input{0};
		double fee_input{0};
		char answer = 'y';
		std::string name_input = "???";

		std::vector<std::shared_ptr<BankAccount>>account_list;        //storage vector of pointers for accounts

		while(yesNo(answer)) {      //enter loop to allow multiple inputs of accounts
			std::cout << "\nWhat type of account would you like to input? "
			          << "\nSavings (1)"
			          << "\nChecking (2)"
			          << "\nEnter your choice:\t"
			          << std::endl;
			int choice{0};
			std::cin >> choice;
			switch (choice) {
				case 1: {                                                      //savings input
					std::cout << "\nEnter a unique name for this savings account: \t";
					std::cin >> name_input;
					std::cout << "\nPlease save the name as it is a unique identifier and you will need it to access your account." << std::endl;
					std::cout << "\nEnter your initial balance: \t" << std::endl;
					std::cin >> balanceInput;
					std::cout << "\nEnter your interest rate: \t" << std::endl;
					std::cin >> interestRate_input;
					account_list.emplace_back(new SavingsAccount(balanceInput, name_input,
					                                             interestRate_input));  //create savings account object
					std::cout << "\nAccount created successfully" << std::endl;
					break;
				}
				case 2: {
					std::cout << "\nEnter a unique name for this checking account: \t";
					std::cin >> name_input;
					std::cout << "\nEnter your initial balance: \t" << std::endl;             //checking account input
					std::cin >> balanceInput;
					std::cout << "\nEnter the transaction fee: \t" << std::endl;
					std::cin >> fee_input;
					account_list.emplace_back(
							new CheckingAccount(balanceInput, name_input, fee_input)); //create checking account object
					std::cout << "\nAccount created successfully" << std::endl;
					break;
				}
				default: {
					std::cout << "\nInvalid entry" << std::endl;
					break;
				}
			}
			std::cout << "\nWould you like to initialize another account? (y/n)" << std::endl;
			std::cin >> answer;
			yesNo(answer);
		}
		std::cout << "\nCurrent stored accounts:" << std::endl;  // list current stored accounts incase user forgot the name of one
		for (int i = 0; i < account_list.size(); ++i) {
			std::cout << "\n" << account_list[i]->getAccount_name();
		}
		std::cout << "\n\nWould you like to enter a transaction for an account? (y/n)" << std::endl;
		char answer2{0};
		std::cin >> answer2;
		while(yesNo(answer2)) {
			std::cout << "\nTo enter a transaction for your account,"
			          << "\nplease enter the account name: \t";
			std::string account_choice = "???";
			std::cin >> account_choice;         // find the unique identifier for an account in the vector
			std::vector<std::shared_ptr<BankAccount>>::iterator
					itElem = std::find_if(account_list.begin(), account_list.end(), HasIdentifier(account_choice));

			std::cout << "\nWould you like to process a (d)ebit or (c)redit to the account?" << std::endl;
			char a = 0;
			std::tolower(a);
			std::cin >> a;
			double amount{0};
			switch (a) {
				case 'd': //debit the account
					std::cout << "\nEnter the amount to debit: \t" << std::endl;
					std::cin >> amount;
					(**itElem).debit(amount);
					std::cout << "\nYour new balance is: \t"
					          << "\n" << (**itElem).getBalance();
					break;
				case 'c':  //credit the account
					std::cout << "\nEnter the amount to credit: \t" << std::endl;
					std::cin >> amount;
					(**itElem).credit(amount);
					std::cout << "\nYour new balance is: \t"
					          << "\n" << (**itElem).getBalance();
					break;
				default:
					std::cout << "\nInvalid entry" << std::endl;
			}
			std::cout << "\nWould you like to enter another transaction for an account?" << std::endl;
			std::cin >> answer2;
			yesNo(answer2);
		}
		return 0;
	}