#include <set>
#include <string>
#include <unordered_map>

/**
 * Design a food rating system that can do the following:
 *
 * - Modify the rating of a food item listed in the system.
 *
 * - Return the highest-rated food item for a type of cuisine in the system.
 *
 * Implement the FoodRatings class:
 *
 * - FoodRatings(String[] foods, String[] cuisines, int[] ratings) Initializes the system. The food
 * items are described by foods, cuisines and ratings, all of which have a length of n.
 *
 *     - foods[i] is the name of the ith food,
 *
 *     - cuisines[i] is the type of cuisine of the ith food, and
 *
 *     - ratings[i] is the initial rating of the ith food.
 *
 * - void changeRating(String food, int newRating) Changes the rating of the food item with the name
 * food.
 *
 * - String highestRated(String cuisine) Returns the name of the food item that has the highest
 * rating for the given type of cuisine. If there is a tie, return the item with the
 * lexicographically smaller name.
 *
 * Note that a string x is lexicographically smaller than string y if x comes before y in dictionary
 * order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i],
 * then x[i] comes before y[i] in alphabetic order.
 *
 * ! 1 <= n <= 2 * 10^4
 * ! n == foods.length == cuisines.length == ratings.length
 * ! 1 <= foods[i].length, cuisines[i].length <= 10
 * ! foods[i], cuisines[i] consist of lowercase English letters.
 * ! 1 <= ratings[i] <= 10^8
 * ! All the strings in foods are distinct.
 * ! food will be the name of a food item in the system across all calls to changeRating.
 * ! cuisine will be a type of cuisine of at least one food item in the system across all calls to
 * ! highestRated.
 * ! At most 2 * 10^4 calls in total will be made to changeRating and highestRated.
 */

class FoodRatings {
public:
    FoodRatings(std::vector<std::string>& foods, std::vector<std::string>& cuisines, std::vector<int>& ratings)
    {
        const int n = foods.size();
        for (int i = 0; i < n; ++i) {
            info[foods[i]] = {foods[i], cuisines[i], ratings[i]};
            map[cuisines[i]].insert(info[foods[i]]);
        }
    }

    void changeRating(const std::string& food, int newRating)
    {
        if (!info.count(food))
            return;

        map[info[food].cuisine].erase(info[food]);
        info[food].rating = newRating;
        map[info[food].cuisine].insert(info[food]);
    }

    std::string highestRated(const std::string& cuisine)
    {
        if (!map.count(cuisine))
            return {};

        return map[cuisine].begin()->name;
    }

private:
    struct Food {
        std::string name;
        std::string cuisine;
        int rating{0};
    };

    struct FoodCompare {
        bool operator()(const Food& f1, const Food& f2) const
        {
            // sort ratings in descending order,
            // otherwise sort names in ascending order
            return f1.rating == f2.rating ? f1.name < f2.name : f1.rating > f2.rating;
        }
    };

    std::unordered_map<std::string, std::set<Food, FoodCompare>> map; // cuisine to sorted Foods
    std::unordered_map<std::string, Food> info;                       // food_name to Food
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */