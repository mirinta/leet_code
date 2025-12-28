#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G',
 * and 'T'.
 *
 * Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene
 * where one mutation is defined as one single character changed in the gene string.
 *
 * - For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
 *
 * There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank
 * to make it a valid gene string.
 *
 * Given the two gene strings startGene and endGene and the gene bank bank, return the minimum
 * number of mutations needed to mutate from startGene to endGene. If there is no such a mutation,
 * return -1.
 *
 * Note that the starting point is assumed to be valid, so it might not be included in the bank.
 *
 * ! 0 <= bank.length <= 10
 * ! startGene.length == endGene.length == bank[i].length == 8
 * ! startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
 */

class Solution {
public:
    int minMutation(std::string startGene, std::string endGene, std::vector<std::string>& bank)
    {
        const std::string kChoices{"ACGT"};
        std::unordered_set<std::string> geneBank(bank.begin(), bank.end());
        if (!geneBank.count(endGene))
            return -1;

        if (startGene == endGene)
            return 0;

        std::queue<std::string> queue;
        queue.push(startGene);
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto current = queue.front();
                queue.pop();
                if (current == endGene)
                    return steps;

                for (int i = 0; i < current.size(); ++i) {
                    for (const auto& c : kChoices) {
                        if (c == current[i])
                            continue;

                        std::string mutation(current);
                        mutation[i] = c;
                        if (!geneBank.count(mutation))
                            continue;

                        geneBank.erase(mutation);
                        queue.push(std::move(mutation));
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
