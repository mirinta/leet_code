#include <deque>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * Design a Snake game that is played on a device with screen size height x width. Play the game
 * online if you are not familiar with the game.
 *
 * The snake is initially positioned at the top left corner (0, 0) with a length of 1 unit.
 *
 * You are given an array food where food[i] = (ri, ci) is the row and column position of a piece of
 * food that the snake can eat. When a snake eats a piece of food, its length and the game's score
 * both increase by 1.
 *
 * Each piece of food appears one by one on the screen, meaning the second piece of food will not
 * appear until the snake eats the first piece of food.
 *
 * When a piece of food appears on the screen, it is guaranteed that it will not appear on a block
 * occupied by the snake.
 *
 * The game is over if the snake goes out of bounds (hits a wall) or if its head occupies a space
 * that its body occupies after moving (i.e. a snake of length 4 cannot run into itself).
 *
 * Implement the SnakeGame class:
 *
 * - SnakeGame(int width, int height, int[][] food) Initializes the object with a screen of size
 * height x width and the positions of the food.
 *
 * - int move(String direction) Returns the score of the game after applying one direction move by
 * the snake. If the game is over, return -1.
 *
 * ! 1 <= width, height <= 10^4
 * ! 1 <= food.length <= 50
 * ! food[i].length == 2
 * ! 0 <= ri < height
 * ! 0 <= ci < width
 * ! direction.length == 1
 * ! direction is 'U', 'D', 'L', or 'R'.
 * ! At most 10^4 calls will be made to move.
 */

class SnakeGame {
public:
    SnakeGame(int width, int height, std::vector<std::vector<int>>& food) : width(width), height(height), food(food)
    {
        snake.emplace_front(0, 0);
        body.insert(0);
    }

    int move(const std::string& direction)
    {
        if (score == -1)
            return -1;

        auto [headX, headY] = snake.front();
        switch (direction[0]) {
            case 'U':
                headX--;
                break;
            case 'D':
                headX++;
                break;
            case 'L':
                headY--;
                break;
            case 'R':
                headY++;
                break;
            default:
                return score = -1;
        }
        if (headX < 0 || headX >= height || headY < 0 || headY >= width)
            return score = -1;

        const auto [tailX, tailY] = snake.back();
        snake.pop_back();
        body.erase(encode(tailX, tailY));
        if (body.count(encode(headX, headY)))
            return score = -1;

        if (foodIndex < food.size() && food[foodIndex][0] == headX && food[foodIndex][1] == headY) {
            foodIndex++;
            score++;
            snake.emplace_back(tailX, tailY);
            body.insert(encode(tailX, tailY));
        }
        snake.emplace_front(headX, headY);
        body.insert(encode(headX, headY));
        return score;
    }

private:
    int encode(int x, int y) const
    {
        return x * width + y;
    }

private:
    const int width;
    const int height;
    const std::vector<std::vector<int>> food;

    int foodIndex{0};
    int score{0};
    std::deque<std::pair<int, int>> snake;
    std::unordered_set<int> body;
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */
