#include <queue>
#include <vector>

/**
 * Consider a matrix M with dimensions width * height, such that every cell has value 0 or 1, and
 * any square sub-matrix of M of size sideLength * sideLength has at most maxOnes ones.
 *
 * Return the maximum possible number of ones that the matrix M can have.
 *
 * ! 1 <= width, height <= 100
 * ! 1 <= sideLength <= width, height
 * ! 0 <= maxOnes <= sideLength * sideLength
 */

class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes)
    {
        std::vector<std::vector<int>> freq(height, std::vector<int>(height, 0));
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                freq[i % sideLength][j % sideLength]++;
            }
        }
        std::priority_queue<int, std::vector<int>, std::greater<>> pq; // min heap
        for (int i = 0; i < sideLength; ++i) {
            for (int j = 0; j < sideLength; ++j) {
                pq.push(freq[i][j]);
                if (pq.size() > maxOnes) {
                    pq.pop();
                }
            }
        }
        int result = 0;
        while (!pq.empty()) {
            result += pq.top();
            pq.pop();
        }
        return result;
    }
};