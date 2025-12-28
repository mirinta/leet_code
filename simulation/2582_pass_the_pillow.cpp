
/**
 * There are n people standing in a line labeled from 1 to n. The first person in the line is
 * holding a pillow initially. Every second, the person holding the pillow passes it to the next
 * person standing in the line. Once the pillow reaches the end of the line, the direction changes,
 * and people continue passing the pillow in the opposite direction.
 *
 * - For example, once the pillow reaches the nth person they pass it to the n - 1th person, then to
 * the n - 2th person and so on.
 *
 * Given the two positive integers n and time, return the index of the person holding the pillow
 * after time seconds.
 *
 * ! 2 <= n <= 1000
 * ! 1 <= time <= 1000
 */

class Solution {
public:
    int passThePillow(int n, int time)
    {
        return approach2(n, time);
    }

private:
    int approach2(int n, int time)
    {
        const int round = time / (n - 1);
        const int extra = time % (n - 1);
        if (round % 2)
            return n - extra;

        return 1 + extra;
    }

    int approach1(int n, int time)
    {
        int direction = 1;
        int index = 1;
        while (time--) {
            index += direction;
            if (index == n || index == 1) {
                direction *= -1;
            }
        }
        return index;
    }
};