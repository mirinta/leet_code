#include <set>
#include <unordered_map>

/**
 * Design a number container system that can do the following:
 *
 * - Insert or Replace a number at the given index in the system.
 *
 * - Return the smallest index for the given number in the system.
 *
 * Implement the NumberContainers class:
 *
 * - NumberContainers() Initializes the number container system.
 *
 * - void change(int index, int number) Fills the container at index with the number. If there is
 * already a number at that index, replace it.
 *
 * - int find(int number) Returns the smallest index for the given number, or -1 if there is no
 * index that is filled by number in the system.
 *
 * ! 1 <= index, number <= 10^9
 * ! At most 10^5 calls will be made in total to change and find.
 */

class NumberContainers {
public:
    NumberContainers() {}

    void change(int index, int number)
    {
        if (indexToNumber.count(index)) {
            const int prev = indexToNumber[index];
            numberToIndices[prev].erase(index);
            if (numberToIndices[prev].empty()) {
                numberToIndices.erase(prev);
            }
        }
        indexToNumber[index] = number;
        numberToIndices[number].insert(index);
    }

    int find(int number)
    {
        if (!numberToIndices.count(number))
            return -1;

        return *numberToIndices[number].begin();
    }

private:
    std::unordered_map<int, int> indexToNumber;
    std::unordered_map<int, std::set<int>> numberToIndices;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
