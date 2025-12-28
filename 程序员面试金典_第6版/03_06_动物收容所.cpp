#include <array>
#include <queue>
#include <vector>

/**
 * 动物收容所。有家动物收容所只收容狗与猫，且严格遵守“先进先出”的原则。
 * 在收养该收容所的动物时，收养人只能收养所有动物中“最老”（由其进入收容所的时间长短而定）的动物，或者可以挑选猫或狗（同时必须收养此类动物中“最老”的）。
 * 换言之，收养人不能自由挑选想收养的对象。请创建适用于这个系统的数据结构，实现各种操作方法，比如enqueue、dequeueAny、dequeueDog和dequeueCat。
 * 允许使用Java内置的LinkedList数据结构。
 *
 * enqueue方法有一个animal参数，animal[0]代表动物编号，animal[1]代表动物种类，其中 0 代表猫，1
 * 代表狗。
 *
 * dequeue*方法返回一个列表[动物编号, 动物种类]，若没有可以收养的动物，则返回[-1,-1]。
 *
 * ! 收纳所的最大容量为20000
 */

class AnimalShelf {
public:
    AnimalShelf() {}

    void enqueue(std::vector<int> animal)
    {
        data[animal[1]].push(animal[0]);
    }

    std::vector<int> dequeueAny()
    {
        if (data[0].empty() || data[1].empty())
            return data[0].empty() ? dequeueDog() : dequeueCat();

        if (data[0].front() < data[1].front())
            return dequeueCat();

        return dequeueDog();
    }

    std::vector<int> dequeueDog()
    {
        if (data[1].empty())
            return {-1, -1};

        const auto dog = data[1].front();
        data[1].pop();
        return {dog, 1};
    }

    std::vector<int> dequeueCat()
    {
        if (data[0].empty())
            return {-1, -1};

        const auto cat = data[0].front();
        data[0].pop();
        return {cat, 0};
    }

private:
    std::array<std::queue<int>, 2> data;
};

/**
 * Your AnimalShelf object will be instantiated and called as such:
 * AnimalShelf* obj = new AnimalShelf();
 * obj->enqueue(animal);
 * vector<int> param_2 = obj->dequeueAny();
 * vector<int> param_3 = obj->dequeueDog();
 * vector<int> param_4 = obj->dequeueCat();
 */