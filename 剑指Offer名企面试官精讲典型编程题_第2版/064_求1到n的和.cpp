
/**
 * 求 1+2+...+n。
 *
 * 要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
 *
 * ! 1 <= n <= 10000
 */

class Solver {
public:
    explicit Solver()
    {
        count++;
        sum += count;
    }

    static int getSum()
    {
        return sum;
    }

    static void reset()
    {
        count = 0;
        sum = 0;
    }

private:
    static int count;
    static int sum;
};

int Solver::count = 0;
int Solver::sum = 0;

class Solution {
public:
    int sumNums(int n)
    {
        Solver::reset();
        auto* array = new Solver[n];
        delete[] array;
        return Solver::getSum();
    }
};