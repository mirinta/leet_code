#include <set>
#include <unordered_map>
#include <vector>

/**
 * You have a movie renting company consisting of n shops. You want to implement a renting system
 * that supports searching for, booking, and returning movies. The system should also support
 * generating a report of the currently rented movies.
 *
 * Each movie is given as a 2D integer array entries where entries[i] = [shopi, moviei, pricei]
 * indicates that there is a copy of movie moviei at shop shopi with a rental price of pricei. Each
 * shop carries at most one copy of a movie moviei.
 *
 * The system should support the following functions:
 *
 * - Search: Finds the cheapest 5 shops that have an unrented copy of a given movie. The shops
 * should be sorted by price in ascending order, and in case of a tie, the one with the smaller
 * shopi should appear first. If there are less than 5 matching shops, then all of them should be
 * returned. If no shop has an unrented copy, then an empty list should be returned.
 *
 * - Rent: Rents an unrented copy of a given movie from a given shop.
 *
 * - Drop: Drops off a previously rented copy of a given movie at a given shop.
 *
 * - Report: Returns the cheapest 5 rented movies (possibly of the same movie ID) as a 2D list res
 * where res[j] = [shopj, moviej] describes that the jth cheapest rented movie moviej was rented
 * from the shop shopj. The movies in res should be sorted by price in ascending order, and in case
 * of a tie, the one with the smaller shopj should appear first, and if there is still tie, the one
 * with the smaller moviej should appear first. If there are fewer than 5 rented movies, then all of
 * them should be returned. If no movies are currently being rented, then an empty list should be
 * returned.
 *
 * Implement the MovieRentingSystem class:
 *
 * - MovieRentingSystem(int n, int[][] entries) Initializes the MovieRentingSystem object with n
 * shops and the movies in entries.
 *
 * - List<Integer> search(int movie) Returns a list of shops that have an unrented copy of the given
 * movie as described above.
 *
 * - void rent(int shop, int movie) Rents the given movie from the given shop.
 *
 * - void drop(int shop, int movie) Drops off a previously rented movie at the given shop.
 *
 * - List<List<Integer>> report() Returns a list of cheapest rented movies as described above.
 *
 * Note: The test cases will be generated such that rent will only be called if the shop has an
 * unrented copy of the movie, and drop will only be called if the shop had previously rented out
 * the movie.
 *
 * ! 1 <= n <= 3 * 10^5
 * ! 1 <= entries.length <= 10^5
 * ! 0 <= shopi < n
 * ! 1 <= moviei, pricei <= 10^4
 * ! Each shop carries at most one copy of a movie moviei.
 * ! At most 105 calls in total will be made to search, rent, drop and report.
 */

class MovieRentingSystem
{
public:
    MovieRentingSystem(int n, std::vector<std::vector<int>>& entries) : info(n)
    {
        for (const auto& e : entries) {
            info[e[0]][e[1]] = e[2];
            map[e[1]].emplace(e[2], e[0]);
        }
    }

    std::vector<int> search(int movie)
    {
        if (!map.count(movie) || map[movie].empty())
            return {};

        std::vector<int> result;
        for (auto iter = map[movie].begin(); iter != map[movie].end() && result.size() < 5;
             ++iter) {
            result.push_back(iter->second);
        }
        return result;
    }

    void rent(int shop, int movie)
    {
        map[movie].erase({info[shop][movie], shop});
        set.emplace(info[shop][movie], shop, movie);
    }

    void drop(int shop, int movie)
    {
        map[movie].emplace(info[shop][movie], shop);
        set.erase({info[shop][movie], shop, movie});
    }

    std::vector<std::vector<int>> report()
    {
        if (set.empty())
            return {};

        std::vector<std::vector<int>> result;
        for (auto iter = set.begin(); iter != set.end() && result.size() < 5; ++iter) {
            result.push_back({std::get<1>(*iter), std::get<2>(*iter)});
        }
        return result;
    }

private:
    std::vector<std::unordered_map<int, int>> info; // info[shop][movie] = price

    using Pair = std::pair<int, int>; // <price, shop>
    std::unordered_map<int, std::set<Pair>> map;

    using Tuple = std::tuple<int, int, int>; // <price, shop, movie>
    std::set<Tuple> set;
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */