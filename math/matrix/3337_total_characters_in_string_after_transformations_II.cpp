#include <array>
#include <string>
#include <vector>

/**
 * You are given a string s consisting of lowercase English letters, an integer t representing the
 * number of transformations to perform, and an array nums of size 26. In one transformation, every
 * character in s is replaced according to the following rules:
 *
 * - Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in the alphabet. For
 * example, if s[i] = 'a' and nums[0] = 3, the character 'a' transforms into the next 3 consecutive
 * characters ahead of it, which results in "bcd".
 *
 * - The transformation wraps around the alphabet if it exceeds 'z'. For example, if s[i] = 'y' and
 * nums[24] = 3, the character 'y' transforms into the next 3 consecutive characters ahead of it,
 * which results in "zab". Return the length of the resulting string after exactly t
 * transformations.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of lowercase English letters.
 * ! 1 <= t <= 10^9
 * ! nums.length == 26
 * ! 1 <= nums[i] <= 25
 */

template <size_t M, size_t N, std::enable_if_t<(M > 0 && N > 0), bool> = true>
class Mat
{
public:
    explicit Mat() = default;
    virtual ~Mat() = default;

    long long& operator()(size_t i, size_t j) { return data[i][j]; }
    const long long& operator()(size_t i, size_t j) const { return data[i][j]; }

    template <size_t D>
    Mat<M, D> operator*(const Mat<N, D>& mat) const
    {
        Mat<M, D> result;
        for (size_t i = 0; i < M; ++i) {
            for (size_t k = 0; k < N; ++k) {
                if ((*this)(i, k) == 0)
                    continue;

                for (size_t j = 0; j < D; ++j) {
                    if (mat(k, j) == 0)
                        continue;

                    result(i, j) = (result(i, j) + (*this)(i, k) * mat(k, j) % kMod) % kMod;
                }
            }
        }
        return result;
    }

private:
    static constexpr long long kMod = 1e9 + 7;
    std::array<std::array<long long, N>, M> data{};
};

template <size_t M>
class Identity : public Mat<M, M>
{
public:
    explicit Identity()
    {
        for (size_t i = 0; i < M; ++i) {
            (*this)(i, i) = 1;
        }
    }
};

template <size_t M>
Mat<M, M> fastPow(const Mat<M, M>& mat, long long n)
{
    Mat<M, M> result = Identity<M>();
    Mat<M, M> base = mat;
    while (n > 0) {
        if (n & 1) {
            result = result * base;
        }
        base = base * base;
        n >>= 1;
    }
    return result;
}

class Solution
{
public:
    int lengthAfterTransformations(std::string s, int t, std::vector<int>& nums)
    {
        // let f(i, c) = num of character c after i transformations
        // f(i, c) = sum of f(i-1, cj) * T(c, cj) for cj = a to z
        // where T(c, cj) = whether cj can be transformed into c
        //
        // [ f(i, a) ]   [ T(a, a) T(a, b) T(a, c) ... T(a, z) ]   [ f(i-1, a) ]
        // | f(i, b) | = | T(b, a) T(b, b) T(b, c) ... T(b, z) | * | f(i-1, b) |
        // | ...     |   | ...                                 |   | ...       |
        // [ f(i, z) ]   [ T(z, a) T(z, b) T(z, c) ... T(z, z) ]   | f(i-1, z) |
        static constexpr long long kMod = 1e9 + 7;
        Mat<26, 26> T{};
        for (int i = 0; i < 26; ++i) {
            for (int j = i + 1; j <= i + nums[i]; ++j) {
                T(j % 26, i) = 1;
            }
        }
        Mat<26, 1> f{};
        for (const auto& c : s) {
            f(c - 'a', 0)++;
        }
        f = fastPow(T, t) * f;
        long long result = 0;
        for (int i = 0; i < 26; ++i) {
            result = (result + f(i, 0)) % kMod;
        }
        return result;
    }
};