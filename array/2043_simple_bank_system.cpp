#include <vector>

/**
 * You have been tasked with writing a program for a popular bank that will automate all its
 * incoming transactions (transfer, deposit, and withdraw). The bank has n accounts numbered from 1
 * to n. The initial balance of each account is stored in a 0-indexed integer array balance, with
 * the (i + 1)th account having an initial balance of balance[i].
 *
 * Execute all the valid transactions. A transaction is valid if:
 *
 * - The given account number(s) are between 1 and n, and
 *
 * - The amount of money withdrawn or transferred from is less than or equal to the balance of the
 * account.
 *
 * Implement the Bank class:
 *
 * - Bank(long[] balance) Initializes the object with the 0-indexed integer array balance.
 *
 * - boolean transfer(int account1, int account2, long money) Transfers money dollars from the
 * account numbered account1 to the account numbered account2. Return true if the transaction was
 * successful, false otherwise.
 *
 * - boolean deposit(int account, long money) Deposit money dollars into the account numbered
 * account. Return true if the transaction was successful, false otherwise.
 *
 * - boolean withdraw(int account, long money) Withdraw money dollars from the account numbered
 * account. Return true if the transaction was successful, false otherwise.
 *
 * ! n == balance.length
 * ! 1 <= n, account, account1, account2 <= 10^5
 * ! 0 <= balance[i], money <= 10^12
 * ! At most 10^4 calls will be made to each function transfer, deposit, withdraw.
 */

class Bank
{
public:
    Bank(std::vector<long long>& balance) : balance(std::move(balance)) {}

    bool transfer(int account1, int account2, long long money)
    {
        if (!validateIndex(--account1) || !validateIndex(--account2))
            return false;

        if (balance[account1] < money)
            return false;

        balance[account1] -= money;
        balance[account2] += money;
        return true;
    }

    bool deposit(int account, long long money)
    {
        if (!validateIndex(--account))
            return false;

        balance[account] += money;
        return true;
    }

    bool withdraw(int account, long long money)
    {
        if (!validateIndex(--account))
            return false;

        if (balance[account] < money)
            return false;

        balance[account] -= money;
        return true;
    }

private:
    bool validateIndex(int i) { return i >= 0 && i < balance.size(); }

private:
    std::vector<long long> balance;
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
