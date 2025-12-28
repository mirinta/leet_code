#include <vector>

/**
 * Given two vectors of integers v1 and v2, implement an iterator to return their elements
 * alternately.
 *
 * Implement the ZigzagIterator class:
 *
 * - ZigzagIterator(List<int> v1, List<int> v2) initializes the object with the two vectors v1 and
 * v2.
 *
 * - boolean hasNext() returns true if the iterator still has elements, and false otherwise.
 *
 * - int next() returns the current element of the iterator and moves the iterator to the next
 * element.
 *
 * ! 0 <= v1.length, v2.length <= 1000
 * ! 1 <= v1.length + v2.length <= 2000
 * ! -2^31 <= v1[i], v2[i] <= 2^31 - 1
 */

class ZigzagIterator {
public:
    ZigzagIterator(std::vector<int>& v1, std::vector<int>& v2) : data(v1.size() + v2.size())
    {
        int i = 0;
        int j = 0;
        int k = 0;
        bool change = false;
        while (i < v1.size() || j < v2.size()) {
            if (i == v1.size()) {
                data[k++] = v2[j++];
                continue;
            }
            if (j == v2.size()) {
                data[k++] = v1[i++];
                continue;
            }
            data[k++] = change ? v2[j++] : v1[i++];
            change = !change;
        }
    }

    int next()
    {
        return data[index++];
    }

    bool hasNext()
    {
        return index < data.size();
    }

private:
    int index{0};
    std::vector<int> data;
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */