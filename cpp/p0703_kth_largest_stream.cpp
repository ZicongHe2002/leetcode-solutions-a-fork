#include <deque>
#include <functional>
#include <queue>
#include <vector>

class KthLargest {
    int rank;
    std::priority_queue<int, std::deque<int>, std::greater<int>> largest;

    void retain(int value) {
        largest.push(value);
        if (static_cast<int>(largest.size()) > rank) largest.pop();
    }

public:
    KthLargest(int k, std::vector<int>& nums) : rank(k) {
        for (int value : nums) retain(value);
    }

    int add(int value) {
        retain(value);
        return largest.top();
    }
};
