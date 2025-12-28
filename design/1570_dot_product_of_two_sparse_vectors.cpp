#include <unordered_map>
#include <vector>

/**
 * Given two sparse vectors, compute their dot product.
 *
 * Implement class SparseVector:
 *
 * - SparseVector(nums) Initializes the object with the vector nums
 *
 * - dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
 *
 * A sparse vector is a vector that has mostly zero values, you should store the sparse vector
 * efficiently and compute the dot product between two SparseVector.
 *
 * Follow up: What if only one of the vectors is sparse?
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums1[i], nums2[i] <= 100
 */

class SparseVector {
public:
    SparseVector(std::vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                map[i] = nums[i];
            }
        }
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec)
    {
        int result = 0;
        for (const auto& [idx, val] : vec.data()) {
            if (map.count(idx)) {
                result += val * map[idx];
            }
        }
        return result;
    }

    const std::unordered_map<int, int>& data()
    {
        return map;
    }

private:
    std::unordered_map<int, int> map; // index to non-zero value
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
