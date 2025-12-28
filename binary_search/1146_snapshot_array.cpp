#include <algorithm>
#include <vector>

/**
 * Implement a SnapshotArray that supports the following interface:
 *
 * - SnapshotArray(int length) initializes an array-like data structure with the given length.
 * Initially, each element equals 0.
 *
 * - void set(index, val) sets the element at the given index to be equal to val.
 *
 * - int snap() takes a snapshot of the array and returns the snap_id: the total number of times we
 * called snap() minus 1.
 *
 * - int get(index, snap_id) returns the value at the given index, at the time we took the snapshot
 * with the given snap_id
 *
 * ! 1 <= length <= 5 * 10^4
 * ! 0 <= index < length
 * ! 0 <= val <= 10^9
 * ! 0 <= snap_id < (the total number of times we call snap())
 * ! At most 5 * 10^4 calls will be made to set, snap, and get.
 */

class SnapshotArray {
public:
    explicit SnapshotArray(int length) : data(length)
    {
        for (int i = 0; i < length; ++i) {
            data[i].emplace_back(0, 0);
        }
    }

    void set(int index, int val)
    {
        data[index].emplace_back(snapID, val);
    }

    int snap()
    {
        return snapID++;
    }

    int get(int index, int snap_id)
    {
        int lo = 0;
        int hi = data[index].size() - 1;
        // find the last element that has the given snap_id
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (data[index][mid].first > snap_id) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return data[index][hi].second;
    }

private:
    int snapID{0}; // current snap_id
    // data[i] = [<snap_id, value>, ...]
    std::vector<std::vector<std::pair<int, int>>> data;
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
