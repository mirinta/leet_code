#include <unordered_map>
#include <vector>

static constexpr long long kMod = 1e9 + 7;

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<long long>& nums)
        : n(nums.size()), data(4 * n, 0), lazy(4 * n, 0)
    {
        build(0, n - 1, 1, nums);
    }

    // query sum of nums[L:R], L and R are 0-indexed
    long long query(int L, int R) { return query(L, R, 0, n - 1, 1); }

    // add each element of nums[L:R] by delta, L and R are 0-indexed
    void add(int L, int R, long long delta) { add(L, R, delta, 0, n - 1, 1); }

private:
    void build(int lo, int hi, int id, const std::vector<long long>& nums)
    {
        if (lo == hi) {
            data[id] = nums[lo];
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        build(lo, mid, 2 * id, nums);
        build(mid + 1, hi, 2 * id + 1, nums);
        data[id] = (data[2 * id] + data[2 * id + 1]) % kMod;
    }

    long long query(int L, int R, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R)
            return data[id];

        const int mid = lo + (hi - lo) / 2;
        if (lazy[id] != 0) {
            data[2 * id] = (data[2 * id] + lazy[id] * (mid - lo + 1) % kMod) % kMod;
            data[2 * id + 1] = (data[2 * id + 1] + lazy[id] * (hi - mid) % kMod) % kMod;
            lazy[2 * id] = (lazy[2 * id] + lazy[id]) % kMod;
            lazy[2 * id + 1] = (lazy[2 * id + 1] + lazy[id]) % kMod;
            lazy[id] = 0;
        }
        long long result = 0;
        if (mid >= L) {
            result = (result + query(L, R, lo, mid, 2 * id)) % kMod;
        }
        if (R > mid) {
            result = (result + query(L, R, mid + 1, hi, 2 * id + 1)) % kMod;
        }
        return result;
    }

    void add(int L, int R, long long delta, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R) {
            data[id] = (data[id] + delta * (hi - lo + 1) % kMod) % kMod;
            lazy[id] = (lazy[id] + delta) % kMod;
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        if (lazy[id] != 0) {
            data[2 * id] = (data[2 * id] + lazy[id] * (mid - lo + 1) % kMod) % kMod;
            data[2 * id + 1] = (data[2 * id + 1] + lazy[id] * (hi - mid) % kMod) % kMod;
            lazy[2 * id] = (lazy[2 * id] + lazy[id]) % kMod;
            lazy[2 * id + 1] = (lazy[2 * id + 1] + lazy[id]) % kMod;
            lazy[id] = 0;
        }
        if (mid >= L) {
            add(L, R, delta, lo, mid, 2 * id);
        }
        if (R > mid) {
            add(L, R, delta, mid + 1, hi, 2 * id + 1);
        }
        data[id] = (data[2 * id] + data[2 * id + 1]) % kMod;
    }

private:
    const int n;
    std::vector<long long> data; // 1-indexed
    std::vector<long long> lazy; // 1-indexed
};

class Solution
{
public:
    int sumCounts(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        map[nums[0]] = 0;
        SegmentTree tree(std::vector<long long>(n, 0LL));
        tree.add(0, 0, 1);
        long long dp = 1;
        long long result = 1;
        for (int i = 1; i < n; ++i) {
            const int j = map.count(nums[i]) ? map[nums[i]] : -1;
            dp = (dp + 2 * tree.query(j + 1, i - 1) % kMod + (i - j) % kMod) % kMod;
            result = (result + dp) % kMod;
            map[nums[i]] = i;
            tree.add(j + 1, i, 1);
        }
        return result;
    }
};

// dp[i] = sum of the squares of distinct counts of all subarrays of nums[0:i] ending at nums[i]
// answer = dp[0] + ... + dp[n-1]
//
// let f(i,j) = num of distinct values in nums[i:j]
//
// case 1:
// - nums[i] is not appeared in nums[0:i-1]
// - subarrays ending at nums[i] are:
//   nums[i:i], f(i,i) = 1
//   nums[i-1:i], f(i-1,i) = f(i-1,i-1) + 1
//   nums[i-2:i], f(i-2,i) = f(i-2,i-1) + 1
//   ...
//   nums[0:i], f(0,i) = f(0,i-1) + 1
// - dp[i] = f(i,i)^2 + f(i-1,i)^2 + ... + f(0,i)^2
//         = f(i-1,i-1)^2 + f(i-2,i-1)^2 + ... + f(0,i-1)^2 +
//           2x(f(i-1,i-1) + f(i-2,i-1) + ... + f(0,i-1)) +
//           i + 1
//         = dp[i-1] + 2x(f(i-1,i-1) + f(i-2,i-1) + ... + f(0,i-1)) + i + 1
//
// case 2:
// - let j be the largest index such that j < i and nums[j] = nums[i]
// - subarrays ending at nums[i] are:
//   nums[i:i], f(i,i) = 1
//   nums[i-1:i], f(i-1,i) = f(i-1,i-1) + 1
//   nums[i-2:i], f(i-2,i) = f(i-2,i-1) + 1
//   ...
//   nums[j+1:i], f(j+1,i) = f(j+1,i-1) + 1
//   nums[j:i], f(j,i) = f(j,i-1)
//   ...
//   nums[0:i], f(0,i) = f(0,i-1)
// - dp[i] = f(i,i)^2 + f(i-1,i)^2 + ... + f(0,i)^2
//         = f(i-1,i-1)^2 + f(i-2,i-1)^2 + ... + f(0,i-1)^2 +
//           2x(f(i-1,i-1) + f(i-2,i-1) + ... + f(j+1,i-1)) +
//           i - j
//         = dp[i-1] + 2x(f(i-1,i-1) + f(i-2,i-1) + ... + f(j+1,i-1)) + i - j
//
// combine case 1 and case 2:
// - dp[i] = dp[i-1] + 2x(f(i-1,i-1) + f(i-2,i-1) + ... + f(j+1,i-1)) + i - j
// - j is the last occurrence of nums[i] in nums[0:i-1]
// - if j does not exist, let j = -1
