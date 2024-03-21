#include <iostream>

class SavingsAccount {
private:
    static double annualInterestRate;
    double savingsBalance;

public:
    SavingsAccount(double balance = 0.0) : savingsBalance(balance) {}

    void calculateMonthlyInterest() {
        double monthlyInterest = (savingsBalance * annualInterestRate) / 12.0;
        savingsBalance += monthlyInterest;
    }

    static void modifyInterestRate(double newRate) {
        annualInterestRate = newRate;
    }

    double getBalance() const {
        return savingsBalance;
    }
};

// Initializing static member outside the class definition
double SavingsAccount::annualInterestRate = 0.03; // 3% initially

int main() {
    // Instantiate saver1 and saver2 with initial balances
    SavingsAccount saver1(2000.0);
    SavingsAccount saver2(3000.0);

    // Set annual interest rate to 3% and calculate monthly interest
    SavingsAccount::modifyInterestRate(0.03);
    saver1.calculateMonthlyInterest();
    saver2.calculateMonthlyInterest();

    // Print balances after first month's interest
    std::cout << "Balances after one month at 3% interest rate:\n";
    std::cout << "Saver1 balance: $" << saver1.getBalance() << std::endl;
    std::cout << "Saver2 balance: $" << saver2.getBalance() << std::endl;

    // Set annual interest rate to 4% and calculate next month's interest
    SavingsAccount::modifyInterestRate(0.04);
    saver1.calculateMonthlyInterest();
    saver2.calculateMonthlyInterest();

    // Print balances after second month's interest
    std::cout << "\nBalances after one more month at 4% interest rate:\n";
    std::cout << "Saver1 balance: $" << saver1.getBalance() << std::endl;
    std::cout << "Saver2 balance: $" << saver2.getBalance() << std::endl;

    return 0;
}
