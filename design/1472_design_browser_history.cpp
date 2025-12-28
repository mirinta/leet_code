#include <list>
#include <queue>
#include <string>

/**
 * You have a browser of one tab where you start on the homepage and you can visit another url, get
 * back in the history number of steps or move forward in the history number of steps.
 *
 * Implement the BrowserHistory class:
 *
 * - BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
 *
 * - void visit(string url) Visits url from the current page. It clears up all the forward history.
 *
 * - string back(int steps) Move steps back in history. If you can only return x steps in the
 * history and steps > x, you will return only x steps. Return the current url after moving back in
 * history at most steps.
 *
 * - string forward(int steps) Move steps forward in history. If you can only forward x steps in the
 * history and steps > x, you will forward only x steps. Return the current url after forwarding in
 * history at most steps.
 *
 * ! 1 <= homepage.length <= 20
 * ! 1 <= url.length <= 20
 * ! 1 <= steps <= 100
 * ! homepage and url consist of  '.' or lower case English letters.
 * ! At most 5000 calls will be made to visit, back, and forward.
 */

class BrowserHistory {
public:
    explicit BrowserHistory(std::string homepage)
    {
        _deque.push_front(std::move(homepage));
    }

    void visit(std::string url)
    {
        while (_currentPos > 0 && !_deque.empty()) {
            _deque.pop_front();
            _currentPos--;
        }
        _deque.push_front(std::move(url));
        _currentPos = 0;
    }

    std::string back(int steps)
    {
        _currentPos = std::min<int>(_deque.size() - 1, _currentPos + steps);
        return _deque[_currentPos];
    }

    std::string forward(int steps)
    {
        _currentPos = std::max<int>(0, _currentPos - steps);
        return _deque[_currentPos];
    }

private:
    int _currentPos{0};
    std::deque<std::string> _deque;
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */

// class BrowserHistory {
// public:
//     BrowserHistory(string homepage) {
//         _list.push_front(std::move(homepage));
//         _current = _list.begin();
//     }

//     void visit(string url) {
//         while (!_list.empty() && _list.front() != *_current) {
//             _list.pop_front();
//         }
//         _list.push_front(std::move(url));
//         _current = _list.begin();
//     }

//     string back(int steps) {
//         for (int i = 0; i < steps; ++i) {
//             if (++_current == _list.end()) {
//                 --_current;
//                 break;
//             }
//         }
//         return *_current;
//     }

//     string forward(int steps) {
//         for (int i = 0; _current != _list.begin() && i < steps; ++i) {
//             --_current;
//         }
//         return *_current;
//     }

// private:
//     std::list<std::string> _list;
//     std::list<std::string>::iterator _current;
// };
