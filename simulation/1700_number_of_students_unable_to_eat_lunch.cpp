#include <array>
#include <vector>

/**
 * The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers
 * 0 and 1 respectively. All students stand in a queue. Each student either prefers square or
 * circular sandwiches.
 *
 * The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are
 * placed in a stack. At each step:
 *
 * If the student at the front of the queue prefers the sandwich on the top of the stack, they will
 * take it and leave the queue. Otherwise, they will leave it and go to the queue's end. This
 * continues until none of the queue students want to take the top sandwich and are thus unable to
 * eat.
 *
 * You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the
 * i​​​​​​th sandwich in the stack (i = 0 is the top of the stack) and students[j] is
 * the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of
 * the queue). Return the number of students that are unable to eat.
 *
 * ! 1 <= students.length, sandwiches.length <= 100
 * ! students.length == sandwiches.length
 * ! sandwiches[i] is 0 or 1.
 * ! students[i] is 0 or 1.
 */

class Solution
{
public:
    int countStudents(std::vector<int>& students, std::vector<int>& sandwiches)
    {
        std::array<int, 2> demand{};
        for (const auto& val : students) {
            demand[val]++;
        }
        int remaining = students.size();
        for (const auto& val : sandwiches) {
            if (demand[val] == 0)
                break;

            remaining--;
            demand[val]--;
        }
        return remaining;
    }
};