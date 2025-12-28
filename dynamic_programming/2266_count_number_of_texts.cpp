#include <array>
#include <string>
#include <vector>

/**
 * Alice is texting Bob using her phone. The mapping of digits to letters is shown in the figure
 * below.
 *
 * In order to add a letter, Alice has to press the key of the corresponding digit i times, where i
 * is the position of the letter in the key.
 *
 * - For example, to add the letter 's', Alice has to press '7' four times. Similarly, to add the
 * letter 'k', Alice has to press '5' twice.
 *
 * - Note that the digits '0' and '1' do not map to any letters, so Alice does not use them.
 *
 * However, due to an error in transmission, Bob did not receive Alice's text message but received a
 * string of pressed keys instead.
 *
 * - For example, when Alice sent the message "bob", Bob received the string "2266622".
 *
 * Given a string pressedKeys representing the string received by Bob, return the total number of
 * possible text messages Alice could have sent.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= pressedKeys.length <= 10^5
 * ! pressedKeys only consists of digits from '2' - '9'.
 */

class Solution {
public:
    int countTexts(std::string pressedKeys)
    {
        constexpr int kMod = 1e9 + 7;
        std::array<int, 10> candidates{};
        std::fill(candidates.begin(), candidates.end(), 3);
        candidates[0] = 0;
        candidates[1] = 0;
        candidates[7] = 4;
        candidates[9] = 4;
        const int n = pressedKeys.size();
        std::vector<int> count(n);
        for (int i = 0; i < n; ++i) {
            count[i] = 1;
            if (i > 0 && pressedKeys[i] == pressedKeys[i - 1]) {
                count[i] += count[i - 1];
            }
        }
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            const int limit = std::min(count[i - 1], candidates[pressedKeys[i - 1] - '0']);
            for (int j = 1; j <= std::min({i, limit}); ++j) {
                dp[i] = (dp[i] + dp[i - j]) % kMod;
            }
        }
        return dp[n];
    }
};