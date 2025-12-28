//

#include <vector>

/**
 * Design an algorithm that accepts a stream of integers and retrieves the product of the last k
 * integers of the stream.
 *
 * Implement the ProductOfNumbers class:
 *
 * - ProductOfNumbers() Initializes the object with an empty stream.
 *
 * - void add(int num) Appends the integer num to the stream.
 *
 * - int getProduct(int k) Returns the product of the last k numbers in the current list. You can
 * assume that always the current list has at least k numbers.
 *
 * The test cases are generated so that, at any time, the product of any contiguous sequence of
 * numbers will fit into a single 32-bit integer without overflowing.
 *
 * ! 0 <= num <= 100
 * ! 1 <= k <= 4 * 10^4
 * ! At most 4 * 10^4 calls will be made to add and getProduct.
 * ! The product of the stream at any point in time will fit in a 32-bit integer.
 */

class ProductOfNumbers {
public:
    ProductOfNumbers() {}

    void add(int num)
    {
        if (num == 0) {
            prefix = {1};
            size = 0;
        } else {
            prefix.push_back(prefix.back() * num);
            size++;
        }
    }

    int getProduct(int k)
    {
        if (k > size)
            return 0;

        return prefix[size] / prefix[size - k];
    }

private:
    std::vector<int> prefix{1};
    int size{0};
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
