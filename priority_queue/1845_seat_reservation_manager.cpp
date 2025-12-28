#include <queue>

/**
 * Design a system that manages the reservation state of n seats that are numbered from 1 to n.
 *
 * Implement the SeatManager class:
 *
 * - SeatManager(int n) Initializes a SeatManager object that will manage n seats numbered from 1 to
 * n. All seats are initially available.
 *
 * - int reserve() Fetches the smallest-numbered unreserved seat, reserves it, and returns its
 * number.
 *
 * - void unreserve(int seatNumber) Unreserves the seat with the given seatNumber.
 *
 * ! 1 <= n <= 10^5
 * ! 1 <= seatNumber <= n
 * ! For each call to reserve, it is guaranteed that there will be at least one unreserved seat.
 * ! For each call to unreserve, it is guaranteed that seatNumber will be reserved.
 * ! At most 10^5 calls in total will be made to reserve and unreserve.
 */

class SeatManager {
public:
    SeatManager(int n)
    {
        for (int i = 1; i <= n; ++i) {
            pq.push(i);
        }
    }

    int reserve()
    {
        int result = -1;
        if (!pq.empty()) {
            result = pq.top();
            pq.pop();
        }
        return result;
    }

    void unreserve(int seatNumber)
    {
        pq.push(seatNumber);
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<>> pq; // min heap
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
