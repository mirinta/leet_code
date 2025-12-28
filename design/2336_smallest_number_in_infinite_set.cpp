#include <queue>
#include <set>

/**
 * You have a set which contains all positive integers [1, 2, 3, 4, 5, ...].
 *
 * Implement the SmallestInfiniteSet class:
 *
 * - SmallestInfiniteSet() Initializes the SmallestInfiniteSet object to contain all positive
 * integers.
 *
 * - int popSmallest() Removes and returns the smallest integer contained in the infinite set.
 *
 * - void addBack(int num) Adds a positive integer num back into the infinite set, if it is not
 * already in the infinite set.
 *
 * ! 1 <= num <= 1000
 * ! At most 1000 calls will be made in total to popSmallest and addBack.
 */

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() = default;

    int popSmallest()
    {
        if (!set.empty()) {
            const int val = *set.begin();
            set.erase(val);
            return val;
        }
        return current++;
    }

    void addBack(int num)
    {
        if (num < current && !set.count(num)) {
            set.insert(num);
        }
    }

private:
    std::set<int> set;
    int current{1};
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
