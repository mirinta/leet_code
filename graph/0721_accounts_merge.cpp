#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a list of accounts where each element accounts[i] is a list of strings, where the first
 * element accounts[i][0] is a name, and the rest of the elements are emails representing emails of
 * the account.
 *
 * Now, we would like to merge these accounts. Two accounts definitely belong to the same person if
 * there is some common email to both accounts. Note that even if two accounts have the same name,
 * they may belong to different people as people could have the same name. A person can have any
 * number of accounts initially, but all of their accounts definitely have the same name.
 *
 * After merging the accounts, return the accounts in the following format: the first element of
 * each account is the name, and the rest of the elements are emails in sorted order. The accounts
 * themselves can be returned in any order.
 *
 * ! 1 <= accounts.length <= 1000
 * ! 2 <= accounts[i].length <= 10
 * ! 1 <= accounts[i][j].length <= 30
 * ! accounts[i][0] consists of English letters.
 * ! accounts[i][j] (for j > 0) is a valid email.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), rank(n)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] > rank[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < rank[rootQ]) {
            root[rootP] = rootQ;
        } else {
            root[rootQ] = rootP;
            rank[rootP]++;
        }
    }

private:
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    // N is the number of accounts, and K = max(accounts[i].size())
    // time complexity: O(NKa(N) + NKlog(NK))
    // space complexity: O(N + NK + space complexity of std::sort)
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>>& accounts)
    {
        const int n = accounts.size();
        UnionFind uf(n);
        std::unordered_map<std::string, int> emailToPersonIdx;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < accounts[i].size(); ++j) {
                const auto& email = accounts[i][j];
                if (!emailToPersonIdx.count(email)) {
                    emailToPersonIdx[email] = i;
                } else {
                    uf.connect(i, emailToPersonIdx[email]);
                }
            }
        }
        std::unordered_map<int, std::vector<std::string>> personIdxToMergedEmails;
        for (const auto& [email, personID] : emailToPersonIdx) {
            personIdxToMergedEmails[uf.find(personID)].push_back(email);
        }
        std::vector<std::vector<std::string>> result;
        for (auto& [personID, emails] : personIdxToMergedEmails) {
            std::sort(emails.begin(), emails.end());
            emails.insert(emails.begin(), accounts[personID][0]);
            result.push_back(std::move(emails));
        }
        return result;
    }
};