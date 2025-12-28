#include <queue>
#include <tuple>
#include <vector>

/**
 * There is a school that has classes of students and each class will be having a final exam. You
 * are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand
 * that in the ith class, there are totali total students, but only passi number of students will
 * pass the exam.
 *
 * You are also given an integer extraStudents. There are another extraStudents brilliant students
 * that are guaranteed to pass the exam of any class they are assigned to. You want to assign each
 * of the extraStudents students to a class in a way that maximizes the average pass ratio across
 * all the classes.
 *
 * The pass ratio of a class is equal to the number of students of the class that will pass the exam
 * divided by the total number of students of the class. The average pass ratio is the sum of pass
 * ratios of all the classes divided by the number of the classes.
 *
 * Return the maximum possible average pass ratio after assigning the extraStudents students.
 * Answers within 10^-5 of the actual answer will be accepted.
 *
 * ! 1 <= classes.length <= 10^5
 * ! classes[i].length == 2
 * ! 1 <= passi <= totali <= 10^5
 * ! 1 <= extraStudents <= 10^5
 */

class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents)
    {
        std::priority_queue<Tuple, std::vector<Tuple>, Compare> pq;
        double sum = 0;
        for (const auto& info : classes) {
            pq.emplace(info[0], info[1], gain(info[0], info[1]));
            sum += 1.0 * info[0] / info[1];
        }
        for (int i = 0; i < extraStudents; ++i) {
            const auto [pass, total, delta] = pq.top();
            pq.pop();
            sum += delta;
            pq.emplace(pass + 1, total + 1, gain(pass + 1, total + 1));
        }
        return sum / classes.size();
    }

private:
    using Tuple = std::tuple<double, double, double>;

    struct Compare {
        double operator()(const Tuple& t1, const Tuple& t2) const
        {
            return std::get<2>(t1) < std::get<2>(t2);
        }
    };

    double gain(double a, double b)
    {
        // (a+1)/(b+1) - a/b = (b-a)/b(b+1)
        return (b - a) / b / (b + 1);
    }
};
