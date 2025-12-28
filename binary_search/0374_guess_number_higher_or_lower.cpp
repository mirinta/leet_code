/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 */
int guess(int num);

/**
 * We are playing the Guess Game. The game is as follows:
 *
 * I pick a number from 1 to n. You have to guess which number I picked.
 *
 * Every time you guess wrong, I will tell you whether the number I picked is higher or lower than
 * your guess.
 *
 * You call a pre-defined API int guess(int num), which returns three possible results:
 *
 * - -1: Your guess is higher than the number I picked (i.e. num > pick).
 *
 * - 1: Your guess is lower than the number I picked (i.e. num < pick).
 *
 * - 0: your guess is equal to the number I picked (i.e. num == pick).
 *
 * Return the number that I picked.
 *
 * ! 1 <= n <= 2^31 - 1
 * 1 <= pick <= n
 */

class Solution {
public:
    int guessNumber(int n)
    {
        int lo = 1;
        int hi = n;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int state = guess(mid);
            if (state == 0)
                return mid;

            if (state == -1) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};
